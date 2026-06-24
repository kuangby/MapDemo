#pragma once

#include <atomic>
#include <chrono>
#include <cmath>

namespace map_demo {

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
    void updateSmoothCamera(float deltaTime);

    [[nodiscard]] const PlayerState& player() const { return player_; }
    [[nodiscard]] float              smoothX() const { return smoothX_; }
    [[nodiscard]] float              smoothZ() const { return smoothZ_; }
    [[nodiscard]] float              smoothYaw() const { return smoothYaw_; }
    [[nodiscard]] bool               hasPlayer() const { return player_.hasPlayer; }

    bool  showMiniMap{true};
    float backgroundAlpha{1.0f}; // 0.0 ~ 1.0

private:
    MapState() = default;

    PlayerState player_;

    float smoothX_{0.0f};
    float smoothZ_{0.0f};
    float smoothYaw_{0.0f};

    std::chrono::steady_clock::time_point lastUpdate_{std::chrono::steady_clock::now()};

    // 弹簧阻尼参数
    static constexpr float kSpringStrength = 12.0f;
    static constexpr float kDamping        = 8.0f;

    float velocityX_{0.0f};
    float velocityZ_{0.0f};
    float velocityYaw_{0.0f};
};

} // namespace map_demo
