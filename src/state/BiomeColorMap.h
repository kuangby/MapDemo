#pragma once

#include "data/BlockColor.h"

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

namespace map_demo {

// 群系虚空底色表：从 resource/biome_color.json 加载各群系的 rgb 代表色，按群系名索引
// 查询顺序：群系条目 → default 条目；都没有时由调用方回退到游戏内群系草地色采样
class BiomeColorMap {
public:
    static BiomeColorMap& getInstance();

    // 加载 JSON；失败时清空表（后续查询全部落空，调用方回退游戏内采样）
    bool load(const std::filesystem::path& path);

    // 群系的虚空底色（JSON 中的 rgb 字段）
    [[nodiscard]] std::optional<BlockColor> rgbOf(std::string_view biomeName) const;

private:
    std::unordered_map<std::string, BlockColor> entries_;
    std::optional<BlockColor>                   defaultColor_;
};

} // namespace map_demo
