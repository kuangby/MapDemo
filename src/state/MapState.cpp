#include "state/MapState.h"

#include "config/Config.h"

#include <algorithm>

namespace map_demo {

MapState& MapState::getInstance() {
    static MapState instance;
    return instance;
}

void MapState::updatePlayer(float x, float y, float z, float yaw) {
    updatePlayer(x, y, z, yaw, dimensionId_);
}

void MapState::updatePlayer(float x, float y, float z, float yaw, int dimensionId) {
    player_.x = x;
    player_.y = y;
    player_.z = z;
    player_.yaw = yaw;
    player_.hasPlayer = true;
    dimensionId_      = dimensionId;
    lastUpdate_       = std::chrono::steady_clock::now();
}

void MapState::updateSmoothCamera(float deltaTime) {
    if (!player_.hasPlayer) return;

    auto& cfg       = config::getConfig().smoothCamera;
    deltaTime         = std::clamp(deltaTime, 0.0f, cfg.maxDeltaTime);

    auto springDamper = [&](float target, float& current, float& velocity) {
        float displacement = target - current;
        float springForce  = displacement * cfg.springStrength;
        float dampingForce = -velocity * cfg.damping;
        float acceleration = springForce + dampingForce;

        velocity += acceleration * deltaTime;
        current  += velocity * deltaTime;
    };

    springDamper(player_.x, smoothX_, velocityX_);
    springDamper(player_.z, smoothZ_, velocityZ_);

    // yaw 平滑：在连续的未环绕角度空间进行弹簧阻尼
    float yawDiff = player_.yaw - smoothYaw_;
    while (yawDiff > 180.0f) yawDiff -= 360.0f;
    while (yawDiff < -180.0f) yawDiff += 360.0f;

    float targetYaw = smoothYaw_ + yawDiff;
    springDamper(targetYaw, smoothYaw_, velocityYaw_);
}

float MapState::renderYawRad() const {
    auto& cfg = config::getConfig().smoothCamera;
    constexpr float PI = 3.14159265f;
    return (smoothYaw_ + cfg.renderYawOffset) * PI / 180.0f;
}

void MapState::resetSmoothCamera(float x, float z, float yaw) {
    smoothX_     = x;
    smoothZ_     = z;
    smoothYaw_   = yaw;
    velocityX_   = 0.0f;
    velocityZ_   = 0.0f;
    velocityYaw_ = 0.0f;
}

void MapState::clearPlayer() {
    player_.hasPlayer = false;
    smoothX_          = 0.0f;
    smoothZ_          = 0.0f;
    smoothYaw_        = 0.0f;
    dimensionId_      = 0;
    velocityX_        = 0.0f;
    velocityZ_        = 0.0f;
    velocityYaw_      = 0.0f;
}

} // namespace map_demo
