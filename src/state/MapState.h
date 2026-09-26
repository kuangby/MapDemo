#pragma once

#include <chrono>
#include <cmath>

namespace coral_map {

struct PlayerState {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
    float yaw{0.0f}; // degrees
    bool  hasPlayer{false};

    [[nodiscard]] inline int blockX() const { return static_cast<int>(std::floor(x)); }
    [[nodiscard]] inline int blockY() const { return static_cast<int>(std::floor(y)); }
    [[nodiscard]] inline int blockZ() const { return static_cast<int>(std::floor(z)); }
    [[nodiscard]] inline int chunkX() const { return blockX() >> 4; }
    [[nodiscard]] inline int chunkZ() const { return blockZ() >> 4; }
};

class MapState {
public:
    static MapState& getInstance();

    void updatePlayer(float x, float y, float z, float yaw);
    void updatePlayer(float x, float y, float z, float yaw, int dimensionId);
    void updateSmoothCamera(float deltaTime);
    void resetSmoothCamera(float x, float z, float yaw);
    void clearPlayer();

    [[nodiscard]] const PlayerState& player() const { return player_; }
    [[nodiscard]] float              smoothX() const { return smoothX_; }
    [[nodiscard]] float              smoothZ() const { return smoothZ_; }
    [[nodiscard]] float              smoothYaw() const { return smoothYaw_; }
    [[nodiscard]] int                dimensionId() const { return dimensionId_; }
    [[nodiscard]] float              renderYawRad() const;

    [[nodiscard]] bool               hasPlayer() const { return player_.hasPlayer; }

    bool showMiniMap{true};

    // 大地图状态
    bool  showWorldMap{false};
    float worldMapOffsetX{0.0f}; // 相对平滑相机的偏移（方块）
    float worldMapOffsetZ{0.0f};
    float worldMapZoom{1.0f}; // 像素/方块

private:
    MapState() = default;

    PlayerState player_;
    int         dimensionId_{0};

    float smoothX_{0.0f};
    float smoothZ_{0.0f};
    float smoothYaw_{0.0f}; // 未环绕的连续 yaw，用于平滑

    std::chrono::steady_clock::time_point lastUpdate_{std::chrono::steady_clock::now()};

    float velocityX_{0.0f};
    float velocityZ_{0.0f};
    float velocityYaw_{0.0f};
};

} // namespace coral_map
