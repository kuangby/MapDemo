#pragma once

namespace map_demo {

class MiniMapRenderer {
public:
    static MiniMapRenderer& getInstance();

    void render();

private:
    MiniMapRenderer() = default;

    // 小地图配置
    static constexpr float MAP_SIZE_RATIO    = 1.0f / 6.0f; // 直径 = 窗口宽度 / 6
    static constexpr int   MAP_RADIUS_CHUNKS = 5;
    static constexpr float MARGIN_RIGHT      = 20.0f;
    static constexpr float MARGIN_TOP        = 20.0f;

    [[nodiscard]] float getMapDiameter() const;
    [[nodiscard]] float getMapRadius() const { return getMapDiameter() * 0.5f; }
};

} // namespace map_demo
