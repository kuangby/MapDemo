#include "data/cache/WorldMapCacheManager.h"

#include "data/BlockColor.h"
#include "data/shadowRender/ShadowRenderChunkData.h"
#include "mod/MapDemo.h"

#include <mc/client/game/ClientInstance.h>
#include <mc/client/player/LocalPlayer.h>
#include <mc/network/GameConnectionInfo.h>
#include <mc/world/level/Level.h>

#include <chrono>
#include <cstring>
#include <utility>


namespace map_demo {

WorldMapCacheManager& WorldMapCacheManager::getInstance() {
    static WorldMapCacheManager instance;
    return instance;
}

WorldMapCacheManager::~WorldMapCacheManager() { shutdown(); }

std::string WorldMapCacheManager::makeKey(const RegionPos& pos) {
    return "wmap_" + std::to_string(pos.dimId) + "_" + std::to_string(pos.x) + "_" + std::to_string(pos.z);
}

std::string WorldMapCacheManager::sanitizePathComponent(std::string s) {
    for (char& c : s) {
        switch (c) {
        case '\\':
        case '/':
        case ':':
        case '*':
        case '?':
        case '"':
        case '<':
        case '>':
        case '|':
            c = '_';
            break;
        default:
            break;
        }
    }
    return s;
}

std::shared_ptr<WorldMapRegionData> WorldMapCacheManager::getOrCreateRegion(const RegionPos& pos) {
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto                                it = regions_.find(pos);
        if (it != regions_.end() && it->second) return it->second;
    }
    std::unique_lock<std::shared_mutex> lock(mutex_);
    auto&                               region = regions_[pos];
    // 若正处于"排队加载中"（nullptr），直接覆盖为新数据：bake 结果比磁盘旧数据更新
    if (!region) region = std::make_shared<WorldMapRegionData>();
    return region;
}

void WorldMapCacheManager::updateFromRegionBake(
    const RegionPos&                                                              pos,
    const std::array<std::array<std::shared_ptr<ShadowRenderChunkData>, 16>, 16>& baked
) {
    auto region = getOrCreateRegion(pos);
    {
        std::unique_lock<std::shared_mutex> lock(region->mutex_);
        for (int rcz = 0; rcz < 16; ++rcz) {
            for (int rcx = 0; rcx < 16; ++rcx) {
                auto& chunk = baked[rcz][rcx];
                if (!chunk) continue;
                for (int z = 0; z < 16; ++z) {
                    std::size_t rowBase = (static_cast<std::size_t>(rcz * 16 + z) * WorldMapRegionData::kSize
                                           + static_cast<std::size_t>(rcx * 16))
                                        * 4;
                    for (int x = 0; x < 16; ++x) {
                        const BlockColor& c   = chunk->blocksData[z][x].color;
                        std::size_t       idx = rowBase + static_cast<std::size_t>(x) * 4;
                        region->colors[idx + 0]     = c.r;
                        region->colors[idx + 1]     = c.g;
                        region->colors[idx + 2]     = c.b;
                        region->colors[idx + 3]     = c.a;
                    }
                }
            }
        }
    }
    region->everFilled   = true;
    region->diskDirty    = true;
    region->textureDirty = true;
}

void WorldMapCacheManager::updateFromChunkBake(const ChunkPosWithDim& chunkPos, const ShadowRenderChunkData& baked) {
    RegionPos regionPos(chunkPos);
    int       localChunkX = chunkPos.x - regionPos.x * 16;
    int       localChunkZ = chunkPos.z - regionPos.z * 16;

    auto region = getOrCreateRegion(regionPos);
    {
        std::unique_lock<std::shared_mutex> lock(region->mutex_);
        for (int z = 0; z < 16; ++z) {
            std::size_t rowBase = (static_cast<std::size_t>(localChunkZ * 16 + z) * WorldMapRegionData::kSize
                                   + static_cast<std::size_t>(localChunkX * 16))
                                * 4;
            for (int x = 0; x < 16; ++x) {
                const BlockColor& c   = baked.blocksData[z][x].color;
                std::size_t       idx = rowBase + static_cast<std::size_t>(x) * 4;
                region->colors[idx + 0]     = c.r;
                region->colors[idx + 1]     = c.g;
                region->colors[idx + 2]     = c.b;
                region->colors[idx + 3]     = c.a;
            }
        }
    }
    region->everFilled   = true;
    region->diskDirty    = true;
    region->textureDirty = true;
}

WorldMapCacheManager::FetchResult WorldMapCacheManager::fetchForRender(
    const RegionPos&                                          pos,
    std::array<std::uint8_t, WorldMapRegionData::kDataSize>&  out
) {
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        auto                                it = regions_.find(pos);
        if (it != regions_.end()) {
            auto& region = it->second;
            if (!region || !region->everFilled) return FetchResult::NotLoaded;
            if (!region->textureDirty.exchange(false)) return FetchResult::NoChange;
            region->copyColors(out);
            return FetchResult::Updated;
        }
    }
    // 未加载：占位 nullptr 并入队，由 IO 线程从磁盘读取
    {
        std::lock_guard<std::mutex> dbLock(dbMutex_);
        std::unique_lock<std::shared_mutex> lock(mutex_);
        auto [it, inserted] = regions_.try_emplace(pos, nullptr);
        if (inserted && db_) loadQueue_.push_back(pos);
    }
    return FetchResult::NotLoaded;
}

bool WorldMapCacheManager::hasData(const RegionPos& pos) {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto                                it = regions_.find(pos);
    return it != regions_.end() && it->second && it->second->everFilled;
}

void WorldMapCacheManager::onEnterWorld(ClientInstance* clientInstance, LocalPlayer* player) {
    auto& self = MapDemo::getInstance().getSelf();

    std::filesystem::path root;
    if (auto worldDir = self.getWorldDataDir(); worldDir.has_value()) {
        // 本地存档：跟随存档目录
        root = *worldDir / "worldmap_cache";
    } else {
        // 远程服务器：按 ip+port+种子 区分，保存在 mod 数据目录下
        std::string serverId;
        if (clientInstance) {
            if (auto info = clientInstance->getGameConnectionInfo(); info.has_value()) {
                serverId = sanitizePathComponent(info->mHostIpAddress) + "_" + std::to_string(info->mPort);
            }
        }
        unsigned int seed = 0;
        if (player) seed = player->getLevel().getSeed();
        serverId += "_S" + std::to_string(seed);
        if (serverId.empty()) serverId = "unknown";
        root = self.getDataDir() / "servers" / serverId / "worldmap_cache";
    }

    {
        std::lock_guard<std::mutex> dbLock(dbMutex_);
        std::error_code             ec;
        std::filesystem::create_directories(root, ec);
        storageDir_ = root;
        db_         = std::make_unique<ll::data::KeyValueDB>(root);
        self.getLogger().debug("WorldMap disk cache opened at: {}", root.string());
    }
    {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        regions_.clear();
        loadQueue_.clear();
    }

    if (!ioThread_.joinable()) {
        ioStop_   = false;
        ioThread_ = std::thread(&WorldMapCacheManager::ioWorker, this);
    }
}

void WorldMapCacheManager::onLeaveWorld() {
    if (ioThread_.joinable()) {
        ioStop_ = true;
        ioThread_.join();
    }
    flushDirty();
    {
        std::lock_guard<std::mutex> dbLock(dbMutex_);
        db_.reset();
        storageDir_.clear();
    }
    std::unique_lock<std::shared_mutex> lock(mutex_);
    regions_.clear();
    loadQueue_.clear();
}

void WorldMapCacheManager::shutdown() { onLeaveWorld(); }

void WorldMapCacheManager::flushDirty() {
    struct Item {
        std::string key;
        std::string blob;
    };
    std::vector<Item> items;
    {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        for (auto& [pos, region] : regions_) {
            if (!region || !region->diskDirty.exchange(false)) continue;
            std::string blob(WorldMapRegionData::kDataSize, '\0');
            {
                std::shared_lock<std::shared_mutex> rlock(region->mutex_);
                std::memcpy(blob.data(), region->colors.data(), WorldMapRegionData::kDataSize);
            }
            items.push_back({makeKey(pos), std::move(blob)});
        }
    }
    if (items.empty()) return;

    std::lock_guard<std::mutex> dbLock(dbMutex_);
    if (!db_) return;
    ll::data::KeyValueDB::WriteBatch batch;
    for (auto& item : items) batch.set(item.key, item.blob);
    db_->write(batch);
}

void WorldMapCacheManager::ioWorker() {
    using namespace std::chrono;
    auto lastFlush = steady_clock::now();

    while (!ioStop_) {
        // 通道 1：处理加载队列（锁内取队列，锁外读盘，锁内插入）
        std::vector<RegionPos> pendingLoads;
        {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            pendingLoads.swap(loadQueue_);
        }
        for (auto& pos : pendingLoads) {
            std::optional<std::string> blob;
            {
                std::lock_guard<std::mutex> dbLock(dbMutex_);
                if (!db_) break;
                blob = db_->get(makeKey(pos));
            }
            auto data = std::make_shared<WorldMapRegionData>();
            if (blob && blob->size() == WorldMapRegionData::kDataSize) {
                data->loadColors(blob->data(), blob->size());
            }
            std::unique_lock<std::shared_mutex> lock(mutex_);
            auto                                it = regions_.find(pos);
            // 仅当仍是"排队中"占位时才插入；若已被 bake 结果覆盖则丢弃磁盘旧数据
            if (it != regions_.end() && !it->second) it->second = std::move(data);
        }

        // 通道 2：每 ~2 秒批量写回 dirty region
        if (steady_clock::now() - lastFlush >= 2s) {
            flushDirty();
            lastFlush = steady_clock::now();
        }

        std::this_thread::sleep_for(20ms);
    }
}

} // namespace map_demo
