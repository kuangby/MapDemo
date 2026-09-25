#include "state/TerrainColorUtils.h"

#include "config/Config.h"
#include "state/BlockColorManager.h"

#include "mc/world/level/dimension/Dimension.h"
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/BlockSource.h>
#include <mc/world/level/ChunkBlockPos.h>
#include <mc/world/level/ChunkLocalHeight.h>
#include <mc/world/level/biome/Biome.h>
#include <mc/world/level/biome/biome_color_sampling/BiomeColorSampling.h>
#include <mc/world/level/biome/biome_color_sampling/MapPolicy.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/BlockType.h>
#include <mc/world/level/block/components/BlockMapColorComponent.h>

#include <algorithm>

namespace map_demo {

static BlockColor toBlockColor(mce::Color const& c) {
    auto channel = [](float v) { return static_cast<std::uint8_t>(std::clamp(v, 0.0f, 1.0f) * 255.0f + 0.5f); };
    return BlockColor{channel(c.r), channel(c.g), channel(c.b), channel(c.a)};
}

// 与原版地图一致的颜色计算：
// 有 BlockMapColorComponent 时，最终颜色 = 组件基础色 mMapColor × 群系染色（按 mTintMethod 采样，
// TintMethod::None 时染色为纯白即原色）；没有组件时回退到虚函数 getMapColor。
// 直接读 BlockType::mMapColor 只是未染色的基础色，水/草/树叶等染色方块会偏黑。
// 注意：BiomeAndPatternMapPolicy::get 返回的染色 alpha 恒为 0（IDA 确认），alpha 必须取基础色的。
static mce::Color getVanillaMapColor(Block const& block, BlockSource& source, BlockPos const& pos) {
    if (auto const* comp = block.tryGetComponent<BlockMapColorComponent>()) {
        auto const& policy = BiomeColorSampling::getMapPolicy(comp->mTintMethod);
        mce::Color  tint   = policy.get(source, pos);
        mce::Color  base   = comp->mMapColor.get();
        return mce::Color(base.r * tint.r, base.g * tint.g, base.b * tint.b, base.a);
    }
    return block.getBlockType().getMapColor(source, pos, block);
}

// 获取方块在地图上的颜色（含群系染色）
static BlockColor getBlockMapColor(LevelChunk* chunk, BlockSource& source, ChunkWorldPos pos, int y) {
    ChunkBlockPos localPos(
        static_cast<uchar>(pos.x),
        ChunkLocalHeight{static_cast<short>(y - chunk->mMin->y)},
        static_cast<uchar>(pos.z)
    );
    Block const& block = chunk->getBlock(localPos);
    // 占位符方块：按透明处理，避免无效颜色写入缓存
    if (block.getTypeName() == "minecraft:client_request_placeholder_block") return BlockColor{0, 0, 0, 0};

    // 水：改用群系水面颜色（biome_color.json 的 resource 风格强染色），
    // 原版地图水色（mMapWaterColorARGB）各群系差异太小
    if (block.getTypeName() == "minecraft:water") {
        auto const& biome      = chunk->getBiome(localPos);
        auto        biomeColor = BlockColorManager::getInstance().getBiomeColor(biome.mHash.get().getString());
        if (biomeColor.hasWater) {
            return BlockColor{biomeColor.water.r, biomeColor.water.g, biomeColor.water.b, 255};
        }
    }

    BlockPos worldPos(chunk->mPosition->x * 16 + pos.x, y, chunk->mPosition->z * 16 + pos.z);
    return toBlockColor(getVanillaMapColor(block, source, worldPos));
}

// 无方块可取时的 fallback 颜色（透明）
static BlockColor getEmptyColor() { return BlockColor{0, 0, 0, 0}; }

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
BlockColor processWater(LevelChunk* chunk, BlockSource& source, int cx, int cz, int waterSurfaceY, int minY) {
    // 获取水颜色（含群系染色）
    BlockColor waterColor =
        getBlockMapColor(chunk, source, {static_cast<uchar>(cx), static_cast<uchar>(cz)}, waterSurfaceY);
    int  solidY     = waterSurfaceY;
    bool foundSolid = false;

    // 向下查找水下的固体方块
    while (solidY > minY) {
        solidY--;
        ChunkBlockPos solidPos(
            static_cast<uchar>(cx),
            ChunkLocalHeight{static_cast<short>(solidY - minY)},
            static_cast<uchar>(cz)
        );
        Block const&       solidBlock = chunk->getBlock(solidPos);
        std::string const& solidName  = solidBlock.getTypeName();
        if (solidName != "minecraft:water" && solidName != "minecraft:air" && solidName != "air") {
            foundSolid = true;
            break;
        }
    }

    if (foundSolid) {
        BlockColor solidColor =
            getBlockMapColor(chunk, source, {static_cast<uchar>(cx), static_cast<uchar>(cz)}, solidY);

        // 计算水深和透明度（与 BedrockMap 相同的线性混合公式）
        int   waterDepth   = waterSurfaceY - solidY;
        float waterOpacity = std::min(0.1f * static_cast<float>(waterDepth), 0.8f);

        // 线性混合：(1 - opacity) * solid + opacity * water
        BlockColor finalColor;
        finalColor.r = static_cast<std::uint8_t>(
            (1.0f - waterOpacity) * static_cast<float>(solidColor.r) + waterOpacity * static_cast<float>(waterColor.r)
        );
        finalColor.g = static_cast<std::uint8_t>(
            (1.0f - waterOpacity) * static_cast<float>(solidColor.g) + waterOpacity * static_cast<float>(waterColor.g)
        );
        finalColor.b = static_cast<std::uint8_t>(
            (1.0f - waterOpacity) * static_cast<float>(solidColor.b) + waterOpacity * static_cast<float>(waterColor.b)
        );
        finalColor.a = 255;

        return finalColor;
    }

    return waterColor;
}

// 基于 cameraHeight 的方块颜色获取，同时返回高度信息
BlockColor
getTerrainPixelAtCameraHeight(LevelChunk* chunk, ChunkWorldPos pos, int cameraHeight, bool& outHitPlaceholder) {
    int minY  = chunk->mMin->y;
    int maxY  = chunk->mMax->y;
    int dimId = chunk->mDimension.getDimensionId();

    BlockSource& source = chunk->mDimension.getBlockSourceFromMainChunkSource();

    // 高度信息
    int surfaceHeight = (*chunk->mHeightmap)[16 * pos.z + pos.x].mVal + minY;

    // 检查 cameraHeight 是否在有效范围内
    if (cameraHeight < minY) {
        return getEmptyColor();
    }

    auto getBlockName = [&](int y) -> std::string {
        ChunkBlockPos localPos(
            static_cast<uchar>(pos.x),
            ChunkLocalHeight{static_cast<short>(y - minY)},
            static_cast<uchar>(pos.z)
        );
        std::string name = chunk->getBlock(localPos).getTypeName();
        if (name == "minecraft:client_request_placeholder_block") outHitPlaceholder = true;
        return name;
    };

    auto blockColorAt = [&](int y) -> BlockColor { return getBlockMapColor(chunk, source, pos, y); };

    // 如果 cameraHeight 高于维度最高高度，使用原有表面查找逻辑
    if (cameraHeight > maxY) {
        int height = surfaceHeight;
        if (height < minY || height > maxY) height = maxY;

        // 向上遍历找到最顶部的非空气方块
        for (int y = height; y <= maxY; ++y) {
            std::string name = getBlockName(y);

            if (name == "minecraft:air" || name == "air") {
                if (y > minY) {
                    std::string surfaceName = getBlockName(y - 1);

                    if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                        return processWater(chunk, source, pos.x, pos.z, y - 1, minY);
                    }

                    return blockColorAt(y - 1);
                }
                return getEmptyColor();
            }
        }

        // 到达 maxY 仍未找到空气
        std::string surfaceName = getBlockName(maxY);

        if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
            return processWater(chunk, source, pos.x, pos.z, maxY, minY);
        }

        return blockColorAt(maxY);
    }

    // 获取 cameraHeight 处的方块
    std::string cameraName = getBlockName(cameraHeight);

    // 情况 1: cameraHeight 处是空气
    if (cameraName == "minecraft:air" || cameraName == "air") {
        int height = surfaceHeight;

        if (height < cameraHeight) {
            // mHeightmap 在 cameraHeight 下方，说明上方是空气
            for (int y = height; y <= cameraHeight; ++y) {
                std::string name = getBlockName(y);

                if (name == "minecraft:air" || name == "air") {
                    if (y > minY) {
                        std::string surfaceName = getBlockName(y - 1);

                        // 透明水效果
                        if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                            return processWater(chunk, source, pos.x, pos.z, y - 1, minY);
                        }

                        return blockColorAt(y - 1);
                    }
                    return getEmptyColor();
                }
            }

            // 到达 cameraHeight 仍未找到空气
            std::string surfaceName = getBlockName(cameraHeight);

            if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                return processWater(chunk, source, pos.x, pos.z, cameraHeight, minY);
            }

            return blockColorAt(cameraHeight);
        } else {
            // mHeightmap >= cameraHeight，说明在地下或地表
            for (int y = cameraHeight; y >= minY; --y) {
                std::string name = getBlockName(y);

                if (name != "minecraft:air" && name != "air") {
                    // 找到非空气方块
                    if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                        return processWater(chunk, source, pos.x, pos.z, y, minY);
                    }
                    return blockColorAt(y);
                }
            }
            return getEmptyColor();
        }
    }

    // 情况 2: cameraHeight 处不是空气，判断透明度
    bool isOpaque = isBlockOpaque(cameraName, dimId);

    if (isOpaque) {
        // 不透明：跳过第一段连续的不透明方块，找到第一个半透明方块
        // 或者找到空气后，在空气下方找到第一个方块
        for (int y = cameraHeight - 1; y >= minY; --y) {
            std::string name = getBlockName(y);

            if (name == "minecraft:air" || name == "air") {
                // 找到空气，在空气下方找到第一个非空气方块
                for (int y2 = y - 1; y2 >= minY; --y2) {
                    std::string airBelowName = getBlockName(y2);

                    if (airBelowName != "minecraft:air" && airBelowName != "air") {
                        // 找到空气下方的第一个方块
                        if (config::getConfig().terrain.enableTransparentWater && airBelowName == "minecraft:water") {
                            return processWater(chunk, source, pos.x, pos.z, y2, minY);
                        }
                        return blockColorAt(y2);
                    }
                }
                return getEmptyColor();
            }

            bool currentOpaque = isBlockOpaque(name, dimId);
            if (!currentOpaque) {
                // 找到半透明方块，直接显示
                if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                    return processWater(chunk, source, pos.x, pos.z, y, minY);
                }
                return blockColorAt(y);
            }
            // 不透明方块，继续向下（跳过第一段连续的不透明方块）
        }
        return getEmptyColor();
    } else {
        // 半透明：直接显示这个方块
        if (config::getConfig().terrain.enableTransparentWater && cameraName == "minecraft:water") {
            return processWater(chunk, source, pos.x, pos.z, cameraHeight, minY);
        }
        return blockColorAt(cameraHeight);
    }
}

} // namespace map_demo
