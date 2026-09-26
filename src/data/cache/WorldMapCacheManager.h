#pragma once

#include "data/cache/WorldMapRegionData.h"
#include "data/pos/ChunkPosWithDim.h"
#include "data/pos/RegionPos.h"

#include <ll/api/data/KeyValueDB.h>


#include <array>
#include <atomic>
#include <filesystem>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>


class ClientInstance;
class LocalPlayer;

namespace coral_map {

class ShadowRenderChunkData;

// 大地图缓存管理器：以 region（256x256 方块）为单位缓存 bake 结果并落盘
//
// 线程模型：
// - updateFrom*Bake 由 bake 工作线程调用（非主线程）
// - fetchForRender 由渲染线程调用
// - 磁盘读写由专属 IO 线程完成（锁内取队列/浅拷贝，锁外读写盘）
class WorldMapCacheManager {
public:
    enum class FetchResult {
        NotLoaded, // 无数据（若磁盘可能存在则已排队加载）
        NoChange,  // 有数据但自上次取出后未变化
        Updated    // 数据已拷贝到 out，需要更新纹理
    };

    static WorldMapCacheManager& getInstance();

    // bake 工作线程：region 级 bake 结束、写回之前调用
    void updateFromRegionBake(
        const RegionPos&                                                             pos,
        const std::array<std::array<std::shared_ptr<ShadowRenderChunkData>, 16>, 16>& baked
    );

    // bake 工作线程：chunk 级 bake 结束、写回之前调用（只更新对应 16x16 区域）
    void updateFromChunkBake(const ChunkPosWithDim& chunkPos, const ShadowRenderChunkData& baked);

    // 渲染线程：取出待上传纹理的 region 图
    // forceCopy=true 时，只要 region 有数据就拷贝并返回 Updated（用于纹理被回收后重建）
    FetchResult fetchForRender(
        const RegionPos&                                              pos,
        std::array<std::uint8_t, WorldMapRegionData::kDataSize>& out,
        bool                                                          forceCopy = false
    );

    // 渲染线程：region 是否已有可用数据（无数据则画占位底色，不建纹理）
    bool hasData(const RegionPos& pos);

    // 进入世界：按本地存档 / 远程服务器解析存储目录并打开 KeyValueDB
    void onEnterWorld(ClientInstance* clientInstance, LocalPlayer* player);

    // 离开世界：全部落盘并清空内存缓存
    void onLeaveWorld();

    void shutdown();

private:
    WorldMapCacheManager() = default;
    ~WorldMapCacheManager();

    std::shared_ptr<WorldMapRegionData> getOrCreateRegion(const RegionPos& pos);

    void ioWorker();
    void flushDirty(); // 把所有 diskDirty 的 region 写盘（可在任意线程调用）

    static std::string makeKey(const RegionPos& pos);
    static std::string sanitizePathComponent(std::string s);

    std::unordered_map<RegionPos, std::shared_ptr<WorldMapRegionData>> regions_; // nullptr = 已排队 IO 加载中
    std::shared_mutex                                                  mutex_;

    std::vector<RegionPos> loadQueue_; // 待从磁盘加载（mutex_ 保护）

    std::unique_ptr<ll::data::KeyValueDB> db_;
    std::filesystem::path                 storageDir_;
    std::mutex                            dbMutex_;  // 保护 db_ 与 storageDir_（IO 线程与主线程并发访问）
    std::atomic<bool>                     dbOpen_{false}; // db_ 是否可用（无锁读取；锁顺序固定为 dbMutex_ -> mutex_）

    std::thread       ioThread_;
    std::atomic<bool> ioStop_{false};
};

} // namespace coral_map
