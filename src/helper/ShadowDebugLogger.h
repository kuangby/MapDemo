#pragma once

#include "config/Config.h"

#include <fmt/format.h>

#include <fstream>
#include <mutex>
#include <string_view>

namespace map_demo {

// 阴影调试文件日志：贯穿 标脏计算 -> 标脏执行 -> bake 调度 -> bake 执行 全流程，
// 用于排查阴影残留（该刷新的 chunk 是否被标脏、是否入队、是否完成 bake）。
// 输出文件：<mod数据目录>/logs/shadow_debug.log（追加模式），线程安全。
class ShadowDebugLogger {
public:
    static ShadowDebugLogger& getInstance();

    template <typename... Args>
    void log(fmt::format_string<Args...> format, Args&&... args) {
        if (!enabled_) return;
        write(fmt::vformat(format.get(), fmt::make_format_args(args...)));
    }

    void               setEnabled(bool enabled) { enabled_ = enabled; }
    [[nodiscard]] bool isEnabled() const { return enabled_; }

    // 世界方块坐标是否在观察列表中（bake 时输出详细 ray-march 追踪）
    [[nodiscard]] static bool isWatchedBlock(int worldX, int worldZ) {
        for (auto& [x, z] : config::getConfig().terrain.shadow.watchBlocks) {
            if (x == worldX && z == worldZ) return true;
        }
        return false;
    }

    // 观察列表中是否有方块落在指定 chunk 内
    [[nodiscard]] static bool hasWatchedBlockInChunk(int chunkX, int chunkZ) {
        for (auto& [x, z] : config::getConfig().terrain.shadow.watchBlocks) {
            int bx = x >= 0 ? x / 16 : (x + 1) / 16 - 1;
            int bz = z >= 0 ? z / 16 : (z + 1) / 16 - 1;
            if (bx == chunkX && bz == chunkZ) return true;
        }
        return false;
    }

    void shutdown();

private:
    ShadowDebugLogger() = default;

    void write(std::string_view message);

    std::mutex    mutex_;
    std::ofstream file_;
    bool          enabled_   = false;
    bool          openTried_ = false;
};

} // namespace map_demo
