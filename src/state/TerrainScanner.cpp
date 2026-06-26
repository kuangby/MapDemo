#include "state/TerrainScanner.h"

#include "config/Config.h"
#include "mod/MapDemo.h"
#include "state/BlockColorManager.h"

#include <mc/world/level/BlockSource.h>
#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/ChunkLocalHeight.h>
#include <mc/world/level/biome/Biome.h>
#include <mc/world/level/block/Block.h>

#include <algorithm>
#include <cmath>
#include <sstream>

namespace map_demo {

namespace {

inline int floorDiv(int a, int b) {
    if (b <= 0) return 0;
    if (a >= 0) return a / b;
    return (a + 1) / b - 1;
}

// 判断方块是否不透明（特判优化）
bool isBlockOpaque(const std::string& name, int dim) {
    // 特判优化：常见方块直接返回，避免频繁查表
    if (dim == 0) { // 主世界
        if (name == "minecraft:stone" || name == "minecraft:deepslate" || name == "minecraft:grass_block"
            || name == "minecraft:dirt" || name == "minecraft:bedrock") {
            return true;
        }
    } else if (dim == 1) { // 地狱
        if (name == "minecraft:netherrack" || name == "minecraft:bedrock" || name == "minecraft:soul_sand"
            || name == "minecraft:soul_soil") {
            return true;
        }
    } else if (dim == 2) { // 末地
        if (name == "minecraft:end_stone" || name == "minecraft:bedrock") {
            return true;
        }
    }

    // 通用判断：使用 block_color.json 的 alpha 通道
    auto color = BlockColorManager::getInstance().getBlockColor(name);
    return color.a == 255;
}

// 处理水的特殊效果（透明水）
BlockColor processWater(
    LevelChunk* chunk,
    int         cx,
    int         cz,
    int         waterSurfaceY,
    int         minY,
    const std::string& /*biomeName*/,
    const std::function<BlockColor(const std::string&)>& getBlockColorWithBiome
) {
    BlockColor waterColor = getBlockColorWithBiome("minecraft:water");
    int        solidY     = waterSurfaceY;
    bool       foundSolid = false;

    // 向下查找水下的固体方块
    while (solidY > minY) {
        solidY--;
        ChunkBlockPos solidPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(solidY - minY)},
            static_cast<uchar>(cz)
        );
        Block const& solidBlock = chunk->getBlock(solidPos);
        std::string  solidName  = solidBlock.getTypeName();
        if (solidName != "minecraft:water" && solidName != "minecraft:air" && solidName != "air") {
            foundSolid = true;
            break;
        }
    }

    if (foundSolid) {
        ChunkBlockPos solidPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(solidY - minY)},
            static_cast<uchar>(cz)
        );
        Block const& solidBlock = chunk->getBlock(solidPos);
        BlockColor   solidColor = getBlockColorWithBiome(solidBlock.getTypeName());

        // 计算水深和透明度（与 BedrockMap 相同的线性混合公式）
        int   waterDepth   = waterSurfaceY - solidY;
        float waterOpacity = std::min(0.1f * waterDepth, 0.7f);

        // 线性混合：(1 - opacity) * solid + opacity * water
        BlockColor finalColor;
        finalColor.r = static_cast<std::uint8_t>((1.0f - waterOpacity) * solidColor.r + waterOpacity * waterColor.r);
        finalColor.g = static_cast<std::uint8_t>((1.0f - waterOpacity) * solidColor.g + waterOpacity * waterColor.g);
        finalColor.b = static_cast<std::uint8_t>((1.0f - waterOpacity) * solidColor.b + waterOpacity * waterColor.b);
        finalColor.a = 255;

        return finalColor;
    }

    return waterColor;
}

// 获取 biome fallback 颜色
BlockColor getBiomeFallbackColor(const std::string& biomeName) {
    if (!biomeName.empty()) {
        auto biomeColor = BlockColorManager::getInstance().getBiomeColor(biomeName);
        return biomeColor.rgb;
    }
    return BlockColor{0, 0, 0, 0};
}

// 获取带生物群系混合的方块颜色
BlockColor getBlockColorWithBiome(const std::string& name, const std::string& biomeName) {
    auto color = BlockColorManager::getInstance().getBlockColor(name);
    if (color.a == 0) {
        return BlockColor{173, 8, 172, 255}; // 未知方块：品红色
    }
    if (!biomeName.empty()) {
        color = BlockColorManager::getInstance().blendWithBiome(name, color, biomeName);
    }
    return color;
}

// 基于 cameraHeight 的方块颜色获取（新逻辑）
BlockColor
getBlockColorAtCameraHeight(LevelChunk* chunk, int cx, int cz, int cameraHeight, int minY, int maxY, int dim) {
    std::string biomeName;
    try {
        auto const& biome = chunk->getBiome(ChunkBlockPos::from2D(static_cast<uchar>(cx), static_cast<uchar>(cz)));
        biomeName         = biome.mHash.get().getString();
    } catch (...) {}
    auto getColor = [&](const std::string& name) -> BlockColor { return getBlockColorWithBiome(name, biomeName); };

    // 检查 cameraHeight 是否在有效范围内
    if (cameraHeight < minY) {
        return getBiomeFallbackColor(biomeName);
    }

    // 如果 cameraHeight 高于维度最高高度，使用原有表面查找逻辑（显示地表最高方块）
    if (cameraHeight > maxY) {
        // mHeightmap 记录的是该列第一个非空气类方块的坐标（固体方块）
        // 注意：mHeightmap 会忽略草、脚手架等半透明/非固体方块，因此需要向上遍历
        int height = (*chunk->mHeightmap)[16 * cz + cx].mVal + minY;
        MapDemo::getInstance().getSelf().getLogger().error("a{}", height);
        if (height < minY || height > maxY) height = maxY;

        // 向上遍历找到最顶部的非空气方块（处理 mHeightmap 忽略的草、脚手架等）
        for (int y = height; y <= maxY; ++y) {
            ChunkBlockPos localPos(
                static_cast<uchar>(cx),
                ChunkLocalHeight{static_cast<short>(y - minY)},
                static_cast<uchar>(cz)
            );
            Block const& block = chunk->getBlock(localPos);
            std::string  name  = block.getTypeName();

            if (name == "minecraft:air" || name == "air") {
                if (y > minY) {
                    ChunkBlockPos below(
                        static_cast<uchar>(cx),
                        ChunkLocalHeight{static_cast<short>(y - 1 - minY)},
                        static_cast<uchar>(cz)
                    );
                    Block const& surfaceBlock = chunk->getBlock(below);
                    std::string  surfaceName  = surfaceBlock.getTypeName();
                    MapDemo::getInstance().getSelf().getLogger().error(surfaceName);

                    // 透明水效果
                    if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                        return processWater(chunk, cx, cz, y - 1, minY, biomeName, getColor);
                    }

                    return getColor(surfaceName);
                }
                MapDemo::getInstance().getSelf().getLogger().error("c {}", biomeName);
                return getBiomeFallbackColor(biomeName);
            }
        }
        MapDemo::getInstance().getSelf().getLogger().error("b");

        // 到达 maxY 仍未找到空气
        ChunkBlockPos localPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(maxY - minY)},
            static_cast<uchar>(cz)
        );
        Block const& block = chunk->getBlock(localPos);
        std::string  name  = block.getTypeName();

        if (name == "minecraft:air" || name == "air") {
            return getBiomeFallbackColor(biomeName);
        }

        return getColor(name);
    }

    // 获取 cameraHeight 处的方块
    ChunkBlockPos cameraPos(
        static_cast<uchar>(cx),
        ChunkLocalHeight{static_cast<short>(cameraHeight - minY)},
        static_cast<uchar>(cz)
    );
    Block const& cameraBlock = chunk->getBlock(cameraPos);
    std::string  cameraName  = cameraBlock.getTypeName();

    // 情况 1: cameraHeight 处是空气
    if (cameraName == "minecraft:air" || cameraName == "air") {
        int height = (*chunk->mHeightmap)[16 * cz + cx].mVal + minY;

        if (height < cameraHeight) {
            // mHeightmap 在 cameraHeight 下方，说明上方是空气
            // 使用原有逻辑：向上遍历找到最顶部的非空气方块
            for (int y = height; y <= maxY; ++y) {
                ChunkBlockPos localPos(
                    static_cast<uchar>(cx),
                    ChunkLocalHeight{static_cast<short>(y - minY)},
                    static_cast<uchar>(cz)
                );
                Block const& block = chunk->getBlock(localPos);
                std::string  name  = block.getTypeName();

                if (name == "minecraft:air" || name == "air") {
                    if (y > minY) {
                        ChunkBlockPos below(
                            static_cast<uchar>(cx),
                            ChunkLocalHeight{static_cast<short>(y - 1 - minY)},
                            static_cast<uchar>(cz)
                        );
                        Block const& surfaceBlock = chunk->getBlock(below);
                        std::string  surfaceName  = surfaceBlock.getTypeName();

                        // 透明水效果
                        if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                            return processWater(chunk, cx, cz, y - 1, minY, biomeName, getColor);
                        }

                        return getColor(surfaceName);
                    }
                    return getBiomeFallbackColor(biomeName);
                }
            }

            // 到达 maxY 仍未找到空气
            ChunkBlockPos localPos(
                static_cast<uchar>(cx),
                ChunkLocalHeight{static_cast<short>(maxY - minY)},
                static_cast<uchar>(cz)
            );
            Block const& block = chunk->getBlock(localPos);
            std::string  name  = block.getTypeName();

            if (name == "minecraft:air" || name == "air") {
                return getBiomeFallbackColor(biomeName);
            }

            return getColor(name);
        } else {
            // mHeightmap >= cameraHeight，说明在地下或地表
            // 从 cameraHeight 向下遍历找到第一个非空气方块
            for (int y = cameraHeight; y >= minY; --y) {
                ChunkBlockPos localPos(
                    static_cast<uchar>(cx),
                    ChunkLocalHeight{static_cast<short>(y - minY)},
                    static_cast<uchar>(cz)
                );
                Block const& block = chunk->getBlock(localPos);
                std::string  name  = block.getTypeName();

                if (name != "minecraft:air" && name != "air") {
                    // 找到非空气方块
                    if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                        return processWater(chunk, cx, cz, y, minY, biomeName, getColor);
                    }
                    return getColor(name);
                }
            }
            return getBiomeFallbackColor(biomeName);
        }
    }

    // 情况 2: cameraHeight 处不是空气，判断透明度
    bool isOpaque = isBlockOpaque(cameraName, dim);

    // DEBUG: 记录关键信息
    static int s_debugCounter = 0;
    bool       shouldDebug    = (++s_debugCounter % 100 == 0);
    if (shouldDebug) {
        MapDemo::getInstance().getSelf().getLogger().debug(
            "[DEBUG] cameraHeight={}, dim={}, cameraName={}, isOpaque={}, biomeName='{}'",
            cameraHeight,
            dim,
            cameraName,
            isOpaque,
            biomeName
        );
    }

    if (isOpaque) {
        // 不透明：跳过第一段连续的不透明方块，找到第一个半透明方块
        // 或者找到空气后，在空气下方找到第一个方块
        for (int y = cameraHeight; y >= minY; --y) {
            ChunkBlockPos localPos(
                static_cast<uchar>(cx),
                ChunkLocalHeight{static_cast<short>(y - minY)},
                static_cast<uchar>(cz)
            );
            Block const& block = chunk->getBlock(localPos);
            std::string  name  = block.getTypeName();

            if (name == "minecraft:air" || name == "air") {
                // 找到空气，在空气下方找到第一个非空气方块
                if (shouldDebug) {
                    MapDemo::getInstance().getSelf().getLogger().debug(
                        "[DEBUG] Found air at y={}, searching below...",
                        y
                    );
                }
                for (int y2 = y - 1; y2 >= minY; --y2) {
                    ChunkBlockPos airBelowPos(
                        static_cast<uchar>(cx),
                        ChunkLocalHeight{static_cast<short>(y2 - minY)},
                        static_cast<uchar>(cz)
                    );
                    Block const& airBelowBlock = chunk->getBlock(airBelowPos);
                    std::string  airBelowName  = airBelowBlock.getTypeName();

                    if (airBelowName != "minecraft:air" && airBelowName != "air") {
                        // 找到空气下方的第一个方块
                        if (shouldDebug) {
                            MapDemo::getInstance().getSelf().getLogger().debug(
                                "[DEBUG] Found block below air: y={}, name='{}'",
                                y2,
                                airBelowName
                            );
                        }
                        if (config::getConfig().terrain.enableTransparentWater && airBelowName == "minecraft:water") {
                            return processWater(chunk, cx, cz, y2, minY, biomeName, getColor);
                        }
                        return getColor(airBelowName);
                    }
                }
                if (shouldDebug) {
                    MapDemo::getInstance().getSelf().getLogger().debug(
                        "[DEBUG] No block found below air, returning biome fallback"
                    );
                }
                return getBiomeFallbackColor(biomeName);
            }

            bool currentOpaque = isBlockOpaque(name, dim);
            if (!currentOpaque) {
                // 找到半透明方块，直接显示
                if (shouldDebug) {
                    MapDemo::getInstance().getSelf().getLogger().debug(
                        "[DEBUG] Found semi-transparent block at y={}, name='{}'",
                        y,
                        name
                    );
                }
                if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                    return processWater(chunk, cx, cz, y, minY, biomeName, getColor);
                }
                return getColor(name);
            }
            // 不透明方块，继续向下（跳过第一段连续的不透明方块）
            if (shouldDebug && y == minY) {
                MapDemo::getInstance().getSelf().getLogger().debug(
                    "[DEBUG] Reached minY={}, last block='{}', returning biome fallback",
                    minY,
                    name
                );
            }
        }
        if (shouldDebug) {
            MapDemo::getInstance().getSelf().getLogger().debug(
                "[DEBUG] Loop ended, returning biome fallback for biome='{}'",
                biomeName
            );
        }
        return getBiomeFallbackColor(biomeName);
    } else {
        // 半透明：直接显示这个方块
        if (config::getConfig().terrain.enableTransparentWater && cameraName == "minecraft:water") {
            return processWater(chunk, cx, cz, cameraHeight, minY, biomeName, getColor);
        }
        return getColor(cameraName);
    }
}

// 保留原有函数用于兼容
BlockColor getSurfaceBlockColor(LevelChunk* chunk, int cx, int cz, int minY, int maxY) {
    // 使用默认 cameraHeight（从配置获取对应维度的值）
    // 这里简化处理，直接调用新函数
    // 实际维度需要从外部传入
    int dim          = 0; // 默认主世界
    int cameraHeight = config::getConfig().terrain.cameraHeight.overworld;
    return getBlockColorAtCameraHeight(chunk, cx, cz, cameraHeight, minY, maxY, dim);
}

} // namespace

TerrainScanner& TerrainScanner::getInstance() {
    static TerrainScanner instance;
    return instance;
}

bool TerrainScanner::initializeDiskCache(const std::filesystem::path& path) {
    try {
        diskCache_        = std::make_unique<ll::data::KeyValueDB>(path);
        diskCacheEnabled_ = true;
        return true;
    } catch (const std::exception& e) {
        MapDemo::getInstance().getSelf().getLogger().error("TerrainScanner: failed to init disk cache: {}", e.what());
        diskCache_        = nullptr;
        diskCacheEnabled_ = false;
        return false;
    }
}

void TerrainScanner::shutdown() {
    clearState();
    diskCache_.reset();
    diskCacheEnabled_ = false;
}

void TerrainScanner::clearState() {
    scanQueue_.clear();
    scanMap_.clear();
    lastSeenFrame_.clear();
    totalFrames_      = 0;
    scanRadiusChunks_ = 0;
    spiralOffsets_.clear();
}

std::vector<std::pair<int, int>> TerrainScanner::buildSpiralOffsets(int radiusChunks) {
    std::vector<std::pair<int, int>> offsets;
    offsets.reserve(static_cast<size_t>((radiusChunks * 2 + 1) * (radiusChunks * 2 + 1)));

    for (int dx = -radiusChunks; dx <= radiusChunks; ++dx) {
        for (int dz = -radiusChunks; dz <= radiusChunks; ++dz) {
            offsets.emplace_back(dx, dz);
        }
    }

    std::stable_sort(offsets.begin(), offsets.end(), [](const auto& a, const auto& b) {
        int da = std::max(std::abs(a.first), std::abs(a.second));
        int db = std::max(std::abs(b.first), std::abs(b.second));
        if (da != db) return da < db;
        int ma = std::abs(a.first) + std::abs(a.second);
        int mb = std::abs(b.first) + std::abs(b.second);
        if (ma != mb) return ma < mb;
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    return offsets;
}

void TerrainScanner::updateVisibleSet(int centerChunkX, int centerChunkZ, int dim, int scanRadiusChunks) {
    if (spiralOffsets_.empty() || scanRadiusChunks_ != scanRadiusChunks) {
        spiralOffsets_    = buildSpiralOffsets(scanRadiusChunks);
        scanRadiusChunks_ = scanRadiusChunks;
    }

    for (auto [dx, dz] : spiralOffsets_) {
        ScanChunkKey key{centerChunkX + dx, centerChunkZ + dz, dim};
        lastSeenFrame_[key] = totalFrames_;

        auto it = scanMap_.find(key);
        if (it != scanMap_.end()) {
            // 已在队列中：移到队首（立即扫描）
            scanQueue_.erase(it->second);
            ScanEntry entry{totalFrames_, key};
            auto [newIt, inserted] = scanQueue_.insert(entry);
            if (inserted) {
                it->second = newIt;
            }
            continue;
        }

        // 新进入视野：立即入队
        ScanEntry entry{totalFrames_, key};
        auto [newIt, inserted] = scanQueue_.insert(entry);
        if (inserted) {
            scanMap_[key] = newIt;
        }
    }
}

void TerrainScanner::scanChunk(BlockSource* region, const ScanChunkKey& key, int minY, int maxY) {
    LevelChunk* chunk = region->getChunk(key.chunkX, key.chunkZ);
    if (!isChunkLoaded(chunk)) return;

    int baseWorldX = key.chunkX * 16;
    int baseWorldZ = key.chunkZ * 16;

    // 根据维度获取 cameraHeight
    int cameraHeight;
    switch (key.dim) {
    case 0:
        cameraHeight = config::getConfig().terrain.cameraHeight.overworld;
        break;
    case 1:
        cameraHeight = config::getConfig().terrain.cameraHeight.nether;
        break;
    case 2:
        cameraHeight = config::getConfig().terrain.cameraHeight.end;
        break;
    default:
        cameraHeight = config::getConfig().terrain.cameraHeight.overworld;
        break;
    }

    for (int localZ = 0; localZ < 16; ++localZ) {
        for (int localX = 0; localX < 16; ++localX) {
            int worldX = baseWorldX + localX;
            int worldZ = baseWorldZ + localZ;

            auto color = getBlockColorAtCameraHeight(chunk, localX, localZ, cameraHeight, minY, maxY, key.dim);
            MapCacheManager::getInstance().updateBlock(worldX, worldZ, key.dim, color);
        }
    }

    // 更新 chunk 时间戳并写入磁盘缓存
    auto* data =
        MapCacheManager::getInstance().getRegion(MapCacheManager::worldToRegion(baseWorldX, baseWorldZ, key.dim));
    if (data) {
        int localChunkX = key.chunkX - floorDiv(key.chunkX, 16) * 16;
        int localChunkZ = key.chunkZ - floorDiv(key.chunkZ, 16) * 16;
        if (localChunkX >= 0 && localChunkX < 16 && localChunkZ >= 0 && localChunkZ < 16) {
            data->setChunkLastScanFrame(localChunkX, localChunkZ, totalFrames_);
            saveChunkToDisk(key, data, localChunkX, localChunkZ);
        }
    }
}

void TerrainScanner::saveChunkToDisk(
    const ScanChunkKey& key,
    const RegionData*   data,
    int                 localChunkX,
    int                 localChunkZ
) {
    if (!diskCacheEnabled_ || !diskCache_) return;
    try {
        auto blob = serializeChunk(data, localChunkX, localChunkZ);
        diskCache_->set(makeDiskKey(key), blob);
    } catch (const std::exception& e) {
        MapDemo::getInstance().getSelf().getLogger().error("TerrainScanner: save chunk to disk failed: {}", e.what());
    }
}

bool TerrainScanner::loadChunkFromDisk(const ScanChunkKey& key, RegionData* data, int localChunkX, int localChunkZ) {
    if (!diskCacheEnabled_ || !diskCache_) return false;
    try {
        auto blob = diskCache_->get(makeDiskKey(key));
        if (!blob) return false;
        deserializeChunk(data, localChunkX, localChunkZ, *blob);
        data->setChunkLastScanFrame(localChunkX, localChunkZ, totalFrames_);
        return true;
    } catch (const std::exception& e) {
        MapDemo::getInstance().getSelf().getLogger().error("TerrainScanner: load chunk from disk failed: {}", e.what());
        return false;
    }
}

std::string TerrainScanner::serializeChunk(const RegionData* data, int chunkLocalX, int chunkLocalZ) {
    std::string blob;
    blob.reserve(16 * 16 * 4);
    int startX = chunkLocalX * 16;
    int startZ = chunkLocalZ * 16;
    for (int z = 0; z < 16; ++z) {
        for (int x = 0; x < 16; ++x) {
            auto c = data->getPixel(startX + x, startZ + z);
            blob.push_back(static_cast<char>(c.r));
            blob.push_back(static_cast<char>(c.g));
            blob.push_back(static_cast<char>(c.b));
            blob.push_back(static_cast<char>(c.a));
        }
    }
    return blob;
}

void TerrainScanner::deserializeChunk(RegionData* data, int chunkLocalX, int chunkLocalZ, const std::string& blob) {
    if (blob.size() < 16 * 16 * 4) return;
    int    startX = chunkLocalX * 16;
    int    startZ = chunkLocalZ * 16;
    size_t idx    = 0;
    for (int z = 0; z < 16; ++z) {
        for (int x = 0; x < 16; ++x) {
            BlockColor c{
                static_cast<std::uint8_t>(blob[idx + 0]),
                static_cast<std::uint8_t>(blob[idx + 1]),
                static_cast<std::uint8_t>(blob[idx + 2]),
                static_cast<std::uint8_t>(blob[idx + 3])
            };
            data->setPixel(startX + x, startZ + z, c);
            idx += 4;
        }
    }
}

std::string TerrainScanner::makeDiskKey(const ScanChunkKey& key) {
    std::string out;
    out.reserve(32);
    out.append(reinterpret_cast<const char*>(&key.chunkX), sizeof(key.chunkX));
    out.append(reinterpret_cast<const char*>(&key.chunkZ), sizeof(key.chunkZ));
    out.append(reinterpret_cast<const char*>(&key.dim), sizeof(key.dim));
    return out;
}

bool TerrainScanner::isChunkLoaded(LevelChunk* chunk) { return chunk && chunk->mLoadState.get() == ChunkState::Loaded; }

void TerrainScanner::update(BlockSource* region, int playerChunkX, int playerChunkZ, int dim, int minY, int maxY) {
    ++totalFrames_;

    auto& cfg              = config::getConfig().terrain;
    int   scanRadiusChunks = cfg.scanRadius / 16;

    updateVisibleSet(playerChunkX, playerChunkZ, dim, scanRadiusChunks);

    static int s_updateLogCounter = 0;
    bool       shouldLog          = (++s_updateLogCounter % 120 == 0);

    ScanChunkKey queueFrontKey{0, 0, 0};
    if (!scanQueue_.empty()) queueFrontKey = scanQueue_.begin()->key;

    if (shouldLog) {
        MapDemo::getInstance().getSelf().getLogger().debug(
            "TerrainScanner::update: frame={}, queue={}, visible={}, playerChunk=({}, {}), dim={}, frontChunk=({}, "
            "{}), frontFrame={}",
            totalFrames_,
            scanQueue_.size(),
            lastSeenFrame_.size(),
            playerChunkX,
            playerChunkZ,
            dim,
            queueFrontKey.chunkX,
            queueFrontKey.chunkZ,
            scanQueue_.empty() ? 0ULL : scanQueue_.begin()->nextScanFrame
        );
    }

    int processed = 0;
    int skipped   = 0;
    int loaded    = 0;
    int evicted   = 0;
    int unloaded  = 0;
    int deferred  = 0;
    while (processed < cfg.scanMaxChunksPerFrame && !scanQueue_.empty()) {
        auto it = scanQueue_.begin();
        if (it->nextScanFrame > totalFrames_) break;

        ScanChunkKey key = it->key;
        scanQueue_.erase(it);
        scanMap_.erase(key);

        // 检查是否仍在视野内
        auto seenIt = lastSeenFrame_.find(key);
        if (seenIt == lastSeenFrame_.end()) {
            ++skipped;
            continue;
        }

        std::uint64_t framesSinceSeen = totalFrames_ - seenIt->second;
        if (framesSinceSeen > static_cast<std::uint64_t>(scanRadiusChunks * 2 * 16)) {
            // 已离开视野 2 倍半径以上，按 chunk 粒度清除缓存
            lastSeenFrame_.erase(seenIt);
            MapCacheManager::getInstance().evictChunk(key.chunkX, key.chunkZ, key.dim);
            ++evicted;
            continue;
        }

        // 检查 chunk 是否已加载
        LevelChunk* chunk = region->getChunk(key.chunkX, key.chunkZ);
        if (!isChunkLoaded(chunk)) {
            // 未加载：放到下一轮扫描，不占用本帧处理上限
            ScanEntry newEntry{totalFrames_ + static_cast<std::uint64_t>(cfg.rescanIntervalFrames), key};
            auto [newIt, inserted] = scanQueue_.insert(newEntry);
            if (inserted) {
                scanMap_[key] = newIt;
            }
            ++unloaded;
            continue;
        }
        ++loaded;

        // 检查是否需要扫描：从磁盘加载或检查时间戳
        bool        needScan = true;
        RegionData* data     = MapCacheManager::getInstance().getRegion(
            MapCacheManager::worldToRegion(key.chunkX * 16, key.chunkZ * 16, key.dim)
        );

        int localChunkX = key.chunkX - floorDiv(key.chunkX, 16) * 16;
        int localChunkZ = key.chunkZ - floorDiv(key.chunkZ, 16) * 16;

        if (data && localChunkX >= 0 && localChunkX < 16 && localChunkZ >= 0 && localChunkZ < 16) {
            std::uint64_t lastScan = data->getChunkLastScanFrame(localChunkX, localChunkZ);
            if (lastScan > 0) {
                if ((totalFrames_ - lastScan) < static_cast<std::uint64_t>(cfg.rescanIntervalFrames)) {
                    needScan = false;
                    ++deferred;
                }
            } else {
                // 内存中无数据，尝试从磁盘加载
                if (loadChunkFromDisk(key, data, localChunkX, localChunkZ)) {
                    needScan = false;
                    ++deferred;
                }
            }
        }

        if (needScan) {
            scanChunk(region, key, minY, maxY);
            ++processed;
        }

        // 重新入队，安排下一次扫描
        ScanEntry newEntry{totalFrames_ + static_cast<std::uint64_t>(cfg.rescanIntervalFrames), key};
        auto [newIt, inserted] = scanQueue_.insert(newEntry);
        if (inserted) {
            scanMap_[key] = newIt;
        }
    }

    if (shouldLog) {
        MapDemo::getInstance().getSelf().getLogger().debug(
            "TerrainScanner::update done: processed={}, loaded={}, deferred={}, unloaded={}, skipped={}, evicted={}",
            processed,
            loaded,
            deferred,
            unloaded,
            skipped,
            evicted
        );
    }

    // 淘汰长时间未见的 chunk（即使它们不在队首）
    for (auto it = lastSeenFrame_.begin(); it != lastSeenFrame_.end();) {
        std::uint64_t framesSinceSeen = totalFrames_ - it->second;
        if (framesSinceSeen > static_cast<std::uint64_t>(scanRadiusChunks * 2 * 16)) {
            const auto& key = it->first;
            MapCacheManager::getInstance().evictChunk(key.chunkX, key.chunkZ, key.dim);
            auto mapIt = scanMap_.find(key);
            if (mapIt != scanMap_.end()) {
                scanQueue_.erase(mapIt->second);
                scanMap_.erase(mapIt);
            }
            it = lastSeenFrame_.erase(it);
        } else {
            ++it;
        }
    }
}

} // namespace map_demo
