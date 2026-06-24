#include "state/MapState.h"

#include <algorithm>

namespace map_demo {

MapState& MapState::getInstance() {
    static MapState instance;
    return instance;
}

void MapState::updatePlayer(float x, float y, float z, float yaw) {
    player_.x = x;
    player_.y = y;
    player_.z = z;
    player_.yaw = yaw;
    player_.hasPlayer = true;
    lastUpdate_ = std::chrono::steady_clock::now();
}

void MapState::updateSmoothCamera(float deltaTime) {
    if (!player_.hasPlayer) return;

    deltaTime = std::clamp(deltaTime, 0.0f, 0.1f);

    auto springDamper = [this, deltaTime](float target, float& current, float& velocity) {
        float displacement = target - current;
        float springForce  = displacement * kSpringStrength;
        float dampingForce = -velocity * kDamping;
        float acceleration = springForce + dampingForce;

        velocity += acceleration * deltaTime;
        current  += velocity * deltaTime;
    };

    springDamper(player_.x, smoothX_, velocityX_);
    springDamper(player_.z, smoothZ_, velocityZ_);

    // yaw 平滑需要考虑 0/360 环绕
    float yawDiff = player_.yaw - smoothYaw_;
    while (yawDiff > 180.0f) yawDiff -= 360.0f;
    while (yawDiff < -180.0f) yawDiff += 360.0f;

    float displacementYaw = yawDiff;
    float springForceYaw  = displacementYaw * kSpringStrength;
    float dampingForceYaw = -velocityYaw_ * kDamping;
    float accelerationYaw = springForceYaw + dampingForceYaw;

    velocityYaw_ += accelerationYaw * deltaTime;
    smoothYaw_   += velocityYaw_ * deltaTime;
    while (smoothYaw_ > 360.0f) smoothYaw_ -= 360.0f;
    while (smoothYaw_ < 0.0f) smoothYaw_ += 360.0f;
}

} // namespace map_demo
