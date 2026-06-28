#include "state/TerrainColorUtils.h"

#include "config/Config.h"
#include "mod/MapDemo.h"
#include "state/BlockColorManager.h"

#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/ChunkLocalHeight.h>
#include <mc/world/level/biome/Biome.h>
#include <mc/world/level/block/Block.h>

namespace map_demo {

// 获取3D生物群系名称
std::string getBiomeNameAtY(LevelChunk* chunk, int cx, int cz, int y, int minY) {
    try {
        auto const& biome = chunk->getBiome(ChunkBlockPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(y - minY)},
            static_cast<uchar>(cz)
        ));
        return biome.mHash.get().getString();
    } catch (...) {
        return "";
    }
}

// 获取 biome fallback 颜色
BlockColor getBiomeFallbackColor(const std::string& biomeName) {
    if (!biomeName.empty()) {
        auto biomeColor = BlockColorManager::getInstance().getBiomeColor(biomeName);
        return biomeColor.rgb;
    }
    return BlockColor{0, 0, 0, 0};
}

// 获取带生物群系混合的方块颜色
BlockColor getBlockColorWithBiome(const std::string& name, const std::string& biomeName) {
    auto color = BlockColorManager::getInstance().getBlockColor(name);
    if (color.a == 0) {
        return BlockColor{173, 8, 172, 255}; // 未知方块：品红色
    }
    if (!biomeName.empty()) {
        color = BlockColorManager::getInstance().blendWithBiome(name, color, biomeName);
    }
    return color;
}

// 判断方块是否不透明（特判优化）
bool isBlockOpaque(const std::string& name, int dim) {
    // 特判优化：常见方块直接返回，避免频繁查表
    if (dim == 0) { // 主世界
        if (name == "minecraft:stone" || name == "minecraft:deepslate" || name == "minecraft:grass_block"
            || name == "minecraft:dirt" || name == "minecraft:bedrock") {
            return true;
        }
    } else if (dim == 1) { // 地狱
        if (name == "minecraft:netherrack" || name == "minecraft:bedrock" || name == "minecraft:soul_sand"
            || name == "minecraft:soul_soil") {
            return true;
        }
    } else if (dim == 2) { // 末地
        if (name == "minecraft:end_stone" || name == "minecraft:bedrock") {
            return true;
        }
    }

    // 通用判断：使用 block_color.json 的 alpha 通道
    auto color = BlockColorManager::getInstance().getBlockColor(name);
    return color.a == 255;
}

// 处理水的特殊效果（透明水）
BlockColor processWater(
    LevelChunk* chunk,
    int         cx,
    int         cz,
    int         waterSurfaceY,
    int         minY,
    const std::string& /*biomeName*/,
    const std::function<BlockColor(const std::string&, int)>& getBlockColorWithBiome
) {
    // 获取水颜色（已与生物群系混合）
    BlockColor waterColor = getBlockColorWithBiome("minecraft:water", waterSurfaceY);
    int        solidY     = waterSurfaceY;
    bool       foundSolid = false;

    // 向下查找水下的固体方块
    while (solidY > minY) {
        solidY--;
        ChunkBlockPos solidPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(solidY - minY)},
            static_cast<uchar>(cz)
        );
        Block const& solidBlock = chunk->getBlock(solidPos);
        std::string  solidName  = solidBlock.getTypeName();
        if (solidName != "minecraft:water" && solidName != "minecraft:air" && solidName != "air") {
            foundSolid = true;
            break;
        }
    }

    if (foundSolid) {
        ChunkBlockPos solidPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(solidY - minY)},
            static_cast<uchar>(cz)
        );
        Block const& solidBlock = chunk->getBlock(solidPos);
        BlockColor   solidColor = getBlockColorWithBiome(solidBlock.getTypeName(), solidY);

        // 计算水深和透明度（与 BedrockMap 相同的线性混合公式）
        int   waterDepth   = waterSurfaceY - solidY;
        float waterOpacity = std::min(0.1f * waterDepth, 0.7f);

        // 线性混合：(1 - opacity) * solid + opacity * water
        BlockColor finalColor;
        finalColor.r = static_cast<std::uint8_t>((1.0f - waterOpacity) * solidColor.r + waterOpacity * waterColor.r);
        finalColor.g = static_cast<std::uint8_t>((1.0f - waterOpacity) * solidColor.g + waterOpacity * waterColor.g);
        finalColor.b = static_cast<std::uint8_t>((1.0f - waterOpacity) * solidColor.b + waterOpacity * waterColor.b);
        finalColor.a = 255;

        return finalColor;
    }

    return waterColor;
}

// 基于 cameraHeight 的方块颜色获取
BlockColor getBlockColorAtCameraHeight(
    LevelChunk* chunk, int cx, int cz, int cameraHeight, int minY, int maxY, int dim
) {
    // 获取2D生物群系（用于fallback）
    std::string fallbackBiomeName;
    try {
        auto const& biome = chunk->getBiome(ChunkBlockPos::from2D(static_cast<uchar>(cx), static_cast<uchar>(cz)));
        fallbackBiomeName = biome.mHash.get().getString();
    } catch (...) {}

    // 获取带生物群系混合的方块颜色（使用3D群系）
    auto getColor = [&](const std::string& name, int y) -> BlockColor {
        std::string currentBiomeName = getBiomeNameAtY(chunk, cx, cz, y, minY);
        return getBlockColorWithBiome(name, currentBiomeName);
    };

    // 检查 cameraHeight 是否在有效范围内
    if (cameraHeight < minY) {
        return getBiomeFallbackColor(fallbackBiomeName);
    }

    // 如果 cameraHeight 高于维度最高高度，使用原有表面查找逻辑
    if (cameraHeight > maxY) {
        int height = (*chunk->mHeightmap)[16 * cz + cx].mVal + minY;
        if (height < minY || height > maxY) height = maxY;

        // 向上遍历找到最顶部的非空气方块
        for (int y = height; y <= maxY; ++y) {
            ChunkBlockPos localPos(
                static_cast<uchar>(cx),
                ChunkLocalHeight{static_cast<short>(y - minY)},
                static_cast<uchar>(cz)
            );
            Block const& block = chunk->getBlock(localPos);
            std::string  name  = block.getTypeName();

            if (name == "minecraft:air" || name == "air") {
                if (y > minY) {
                    ChunkBlockPos below(
                        static_cast<uchar>(cx),
                        ChunkLocalHeight{static_cast<short>(y - 1 - minY)},
                        static_cast<uchar>(cz)
                    );
                    Block const& surfaceBlock = chunk->getBlock(below);
                    std::string  surfaceName  = surfaceBlock.getTypeName();

                    // 透明水效果
                    if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                        return processWater(chunk, cx, cz, y - 1, minY, fallbackBiomeName, getColor);
                    }

                    return getColor(surfaceName, y - 1);
                }
                return getBiomeFallbackColor(fallbackBiomeName);
            }
        }

        // 到达 maxY 仍未找到空气
        ChunkBlockPos localPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(maxY - minY)},
            static_cast<uchar>(cz)
        );
        Block const& block = chunk->getBlock(localPos);
        std::string  name  = block.getTypeName();

        if (name == "minecraft:air" || name == "air") {
            return getBiomeFallbackColor(fallbackBiomeName);
        }

        return getColor(name, maxY);
    }

    // 获取 cameraHeight 处的方块
    ChunkBlockPos cameraPos(
        static_cast<uchar>(cx),
        ChunkLocalHeight{static_cast<short>(cameraHeight - minY)},
        static_cast<uchar>(cz)
    );
    Block const& cameraBlock = chunk->getBlock(cameraPos);
    std::string  cameraName  = cameraBlock.getTypeName();

    // 情况 1: cameraHeight 处是空气
    if (cameraName == "minecraft:air" || cameraName == "air") {
        int height = (*chunk->mHeightmap)[16 * cz + cx].mVal + minY;

        if (height < cameraHeight) {
            // mHeightmap 在 cameraHeight 下方，说明上方是空气
            for (int y = height; y <= maxY; ++y) {
                ChunkBlockPos localPos(
                    static_cast<uchar>(cx),
                    ChunkLocalHeight{static_cast<short>(y - minY)},
                    static_cast<uchar>(cz)
                );
                Block const& block = chunk->getBlock(localPos);
                std::string  name  = block.getTypeName();

                if (name == "minecraft:air" || name == "air") {
                    if (y > minY) {
                        ChunkBlockPos below(
                            static_cast<uchar>(cx),
                            ChunkLocalHeight{static_cast<short>(y - 1 - minY)},
                            static_cast<uchar>(cz)
                        );
                        Block const& surfaceBlock = chunk->getBlock(below);
                        std::string  surfaceName  = surfaceBlock.getTypeName();

                        // 透明水效果
                        if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                            return processWater(chunk, cx, cz, y - 1, minY, fallbackBiomeName, getColor);
                        }

                        return getColor(surfaceName, y - 1);
                    }
                    return getBiomeFallbackColor(fallbackBiomeName);
                }
            }

            // 到达 maxY 仍未找到空气
            ChunkBlockPos localPos(
                static_cast<uchar>(cx),
                ChunkLocalHeight{static_cast<short>(maxY - minY)},
                static_cast<uchar>(cz)
            );
            Block const& block = chunk->getBlock(localPos);
            std::string  name  = block.getTypeName();

            if (name == "minecraft:air" || name == "air") {
                return getBiomeFallbackColor(fallbackBiomeName);
            }

            return getColor(name, maxY);
        } else {
            // mHeightmap >= cameraHeight，说明在地下或地表
            for (int y = cameraHeight; y >= minY; --y) {
                ChunkBlockPos localPos(
                    static_cast<uchar>(cx),
                    ChunkLocalHeight{static_cast<short>(y - minY)},
                    static_cast<uchar>(cz)
                );
                Block const& block = chunk->getBlock(localPos);
                std::string  name  = block.getTypeName();

                if (name != "minecraft:air" && name != "air") {
                    // 找到非空气方块
                    if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                        return processWater(chunk, cx, cz, y, minY, fallbackBiomeName, getColor);
                    }
                    return getColor(name, y);
                }
            }
            return getBiomeFallbackColor(fallbackBiomeName);
        }
    }

    // 情况 2: cameraHeight 处不是空气，判断透明度
    bool isOpaque = isBlockOpaque(cameraName, dim);

    if (isOpaque) {
        // 不透明：跳过第一段连续的不透明方块，找到第一个半透明方块
        // 或者找到空气后，在空气下方找到第一个方块
        for (int y = cameraHeight; y >= minY; --y) {
            ChunkBlockPos localPos(
                static_cast<uchar>(cx),
                ChunkLocalHeight{static_cast<short>(y - minY)},
                static_cast<uchar>(cz)
            );
            Block const& block = chunk->getBlock(localPos);
            std::string  name  = block.getTypeName();

            if (name == "minecraft:air" || name == "air") {
                // 找到空气，在空气下方找到第一个非空气方块
                for (int y2 = y - 1; y2 >= minY; --y2) {
                    ChunkBlockPos airBelowPos(
                        static_cast<uchar>(cx),
                        ChunkLocalHeight{static_cast<short>(y2 - minY)},
                        static_cast<uchar>(cz)
                    );
                    Block const& airBelowBlock = chunk->getBlock(airBelowPos);
                    std::string  airBelowName  = airBelowBlock.getTypeName();

                    if (airBelowName != "minecraft:air" && airBelowName != "air") {
                        // 找到空气下方的第一个方块
                        if (config::getConfig().terrain.enableTransparentWater && airBelowName == "minecraft:water") {
                            return processWater(chunk, cx, cz, y2, minY, fallbackBiomeName, getColor);
                        }
                        return getColor(airBelowName, y2);
                    }
                }
                return getBiomeFallbackColor(fallbackBiomeName);
            }

            bool currentOpaque = isBlockOpaque(name, dim);
            if (!currentOpaque) {
                // 找到半透明方块，直接显示
                if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                    return processWater(chunk, cx, cz, y, minY, fallbackBiomeName, getColor);
                }
                return getColor(name, y);
            }
            // 不透明方块，继续向下（跳过第一段连续的不透明方块）
        }
        return getBiomeFallbackColor(fallbackBiomeName);
    } else {
        // 半透明：直接显示这个方块
        if (config::getConfig().terrain.enableTransparentWater && cameraName == "minecraft:water") {
            return processWater(chunk, cx, cz, cameraHeight, minY, fallbackBiomeName, getColor);
        }
        return getColor(cameraName, cameraHeight);
    }
}

} // namespace map_demo
