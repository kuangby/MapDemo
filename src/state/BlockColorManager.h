#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace map_demo {

struct BlockColor {
    std::uint8_t r{0};
    std::uint8_t g{0};
    std::uint8_t b{0};
    std::uint8_t a{255};

    bool operator==(const BlockColor& other) const noexcept {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }
    bool operator!=(const BlockColor& other) const noexcept { return !(*this == other); }
};

struct BiomeColor {
    BlockColor rgb;
    BlockColor grass;
    BlockColor leaves;
    BlockColor water;
    bool       hasGrass{false};
    bool       hasLeaves{false};
    bool       hasWater{false};
};

class BlockColorManager {
public:
    static BlockColorManager& getInstance();

    bool loadFromFiles(const std::string& blockColorPath, const std::string& biomeColorPath);

    [[nodiscard]] BlockColor getBlockColor(const std::string& blockName) const;

    // 根据群系名（不是方块名）获取色调
    [[nodiscard]] BiomeColor getBiomeColor(const std::string& biomeName) const;

    // 将方块颜色与群系色调混合（仅影响 water / leave / grass 类方块）
    [[nodiscard]] BlockColor blendWithBiome(const std::string& blockName, BlockColor color, const std::string& biomeName) const;

    [[nodiscard]] bool isLoaded() const { return loaded_; }

private:
    BlockColorManager() = default;

    std::unordered_map<std::string, BlockColor> blockColors_;
    std::unordered_map<std::string, BiomeColor> biomeColors_;
    bool loaded_{false};
};

} // namespace map_demo
