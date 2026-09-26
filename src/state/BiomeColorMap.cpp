#include "state/BiomeColorMap.h"

#include <nlohmann/json.hpp>

#include <fstream>

namespace map_demo {

namespace {

std::optional<BlockColor> parseColor(const nlohmann::json& arr) {
    if (!arr.is_array() || arr.size() < 3) return std::nullopt;
    if (!arr[0].is_number() || !arr[1].is_number() || !arr[2].is_number()) return std::nullopt;
    return BlockColor{
        arr[0].get<std::uint8_t>(),
        arr[1].get<std::uint8_t>(),
        arr[2].get<std::uint8_t>(),
        255
    };
}

} // namespace

BiomeColorMap& BiomeColorMap::getInstance() {
    static BiomeColorMap instance;
    return instance;
}

bool BiomeColorMap::load(const std::filesystem::path& path) {
    entries_.clear();
    defaultColor_.reset();

    std::ifstream file(path);
    if (!file) return false;

    nlohmann::json root;
    try {
        root = nlohmann::json::parse(file);
    } catch (...) {
        return false;
    }
    if (!root.is_object()) return false;

    for (auto& [name, value] : root.items()) {
        if (!value.is_object() || !value.contains("rgb")) continue;
        auto color = parseColor(value["rgb"]);
        if (!color) continue;
        if (name == "default") defaultColor_ = *color;
        else entries_[name] = *color;
    }

    return !entries_.empty() || defaultColor_.has_value();
}

std::optional<BlockColor> BiomeColorMap::rgbOf(std::string_view biomeName) const {
    // Biome::mHash 的名字带命名空间前缀（如 "minecraft:plains"），JSON 键不含前缀
    constexpr std::string_view nsPrefix = "minecraft:";
    if (biomeName.starts_with(nsPrefix)) biomeName.remove_prefix(nsPrefix.size());
    if (auto it = entries_.find(std::string(biomeName)); it != entries_.end()) return it->second;
    return defaultColor_;
}

} // namespace map_demo
