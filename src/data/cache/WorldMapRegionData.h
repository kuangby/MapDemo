#pragma once

#include <array>
#include <atomic>
#include <cstdint>
#include <cstring>
#include <shared_mutex>


namespace map_demo {

// 大地图 region 缓存数据：256x256 方块的 RGBA 颜色图
// 由 bake 工作线程在 bake 结束、写回之前生成；渲染线程读取上传纹理
class WorldMapRegionData {
public:
    static constexpr int kSize     = 256; // 1 region = 256x256 blocks
    static constexpr int kDataSize = kSize * kSize * 4;

    std::array<std::uint8_t, kDataSize> colors{}; // RGBA

    std::atomic<bool> diskDirty{false};    // 待写盘
    std::atomic<bool> textureDirty{false}; // 待上传 GPU
    std::atomic<bool> everFilled{false};   // 是否写入过任何数据（区分"未加载"与"无数据"）

    mutable std::shared_mutex mutex_; // 保护 colors

    // 锁内拷贝出整张 region 图（渲染线程上传纹理前调用）
    void copyColors(std::array<std::uint8_t, kDataSize>& out) const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        std::memcpy(out.data(), colors.data(), kDataSize);
    }

    // 锁内从 blob 恢复（IO 线程加载磁盘数据后调用）
    void loadColors(const void* data, std::size_t size) {
        if (size != kDataSize) return;
        std::unique_lock<std::shared_mutex> lock(mutex_);
        std::memcpy(colors.data(), data, kDataSize);
        everFilled   = true;
        textureDirty = true;
    }
};

} // namespace map_demo
