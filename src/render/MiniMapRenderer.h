#pragma once

namespace map_demo {

class MiniMapRenderer {
public:
    static MiniMapRenderer& getInstance();

    void render();

private:
    MiniMapRenderer() = default;

    [[nodiscard]] float getMapDiameter() const;
    [[nodiscard]] float getMapRadius() const { return getMapDiameter() * 0.5f; }
};

} // namespace map_demo
