#include "state/BlockColorManager.h"

#include "mod/MapDemo.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <vector>

namespace map_demo {

namespace {

BlockColor parseColor(const nlohmann::json& arr) {
    BlockColor c{};
    if (arr.is_array() && arr.size() >= 3) {
        c.r = arr[0].get<std::uint8_t>();
        c.g = arr[1].get<std::uint8_t>();
        c.b = arr[2].get<std::uint8_t>();
        if (arr.size() >= 4) c.a = arr[3].get<std::uint8_t>();
    }
    return c;
}

} // namespace

BlockColorManager& BlockColorManager::getInstance() {
    static BlockColorManager instance;
    return instance;
}

bool BlockColorManager::loadFromFiles(const std::string& blockColorPath, const std::string& biomeColorPath) {
    loaded_ = false;
    blockColors_.clear();
    biomeColors_.clear();

    auto& logger = MapDemo::getInstance().getSelf().getLogger();

    try {
        {
            std::ifstream in(blockColorPath);
            if (!in) {
                logger.debug("BlockColorManager: cannot open block_color.json at '{}'", blockColorPath);
                return false;
            }
            nlohmann::json root;
            in >> root;

            for (auto& [blockName, tagObj] : root.items()) {
                if (!tagObj.is_object() || tagObj.empty()) continue;
                auto it                 = tagObj.begin();
                blockColors_[blockName] = parseColor(it.value());
            }
            logger.debug("BlockColorManager: loaded {} block colors", blockColors_.size());
        }

        {
            std::ifstream in(biomeColorPath);
            if (!in) {
                logger.debug("BlockColorManager: cannot open biome_color.json at '{}'", biomeColorPath);
                return false;
            }
            nlohmann::json root;
            in >> root;

            for (auto& [biomeName, obj] : root.items()) {
                BiomeColor bc{};
                if (obj.contains("rgb")) bc.rgb = parseColor(obj["rgb"]);
                if (obj.contains("grass")) {
                    bc.grass    = parseColor(obj["grass"]);
                    bc.hasGrass = true;
                }
                if (obj.contains("leaves")) {
                    bc.leaves    = parseColor(obj["leaves"]);
                    bc.hasLeaves = true;
                }
                if (obj.contains("water")) {
                    bc.water    = parseColor(obj["water"]);
                    bc.hasWater = true;
                }
                biomeColors_[biomeName] = bc;
            }
            logger.debug("BlockColorManager: loaded {} biome colors", biomeColors_.size());
        }

        loaded_ = !blockColors_.empty();
        return loaded_;
    } catch (const std::exception& e) {
        logger.debug("BlockColorManager: exception during load: {}", e.what());
        return false;
    } catch (...) {
        logger.debug("BlockColorManager: unknown exception during load");
        return false;
    }
}

BlockColor BlockColorManager::getBlockColor(const std::string& blockName) const {
    auto it = blockColors_.find(blockName);
    if (it != blockColors_.end()) return it->second;

    if (blockName.rfind("minecraft:", 0) == 0) {
        auto it2 = blockColors_.find(blockName.substr(10));
        if (it2 != blockColors_.end()) return it2->second;
    }
    MapDemo::getInstance().getSelf().getLogger().debug("BlockColorManager: block color not found for '{}'", blockName);
    return BlockColor{0, 0, 0, 0};
}

BiomeColor BlockColorManager::getBiomeColor(const std::string& biomeName) const {
    auto it = biomeColors_.find(biomeName);
    if (it != biomeColors_.end()) return it->second;

    auto def = biomeColors_.find("default");
    if (def != biomeColors_.end()) return def->second;

    return BiomeColor{};
}

BlockColor
BlockColorManager::blendWithBiome(const std::string& blockName, BlockColor color, const std::string& biomeName) const {
    auto biome = getBiomeColor(biomeName);

    auto applyTint = [](BlockColor base, BlockColor tint) {
        return BlockColor{
            static_cast<std::uint8_t>((base.r * tint.r) / 255),
            static_cast<std::uint8_t>((base.g * tint.g) / 255),
            static_cast<std::uint8_t>((base.b * tint.b) / 255),
            base.a
        };
    };

    std::string lower;
    lower.reserve(blockName.size());
    for (char c : blockName) lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

    if (lower.find("water") != std::string::npos && biome.hasWater) {
        color = applyTint(color, biome.water);
    } else if (lower.find("leave") != std::string::npos && biome.hasLeaves) {
        color = applyTint(color, biome.leaves);
    } else if (lower.find("grass") != std::string::npos && biome.hasGrass) {
        color = applyTint(color, biome.grass);
    }

    return color;
}

} // namespace map_demo
