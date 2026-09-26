#include "state/TerrainColorUtils.h"

#include "config/Config.h"
#include "state/BiomeColorMap.h"

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
#include <mc/world/level/material/Material.h>

#include <algorithm>

namespace coral_map {

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

    BlockPos worldPos(chunk->mPosition->x * 16 + pos.x, y, chunk->mPosition->z * 16 + pos.z);

    // 水：改用群系水面颜色（WaterRenderAttributes，游戏内渲染水色，resource 风格强染色），
    // 原版地图水色（mMapWaterColorARGB）各群系差异太小
    if (block.getTypeName() == "minecraft:water") {
        int argb = BiomeColorSampling::getWaterColor(chunk->getBiome(localPos), worldPos);
        return BlockColor{
            static_cast<std::uint8_t>((argb >> 16) & 0xFF),
            static_cast<std::uint8_t>((argb >> 8) & 0xFF),
            static_cast<std::uint8_t>(argb & 0xFF),
            255
        };
    }

    return toBlockColor(getVanillaMapColor(block, source, worldPos));
}

// 无方块可取时的 fallback 颜色（透明）
static BlockColor getEmptyColor() { return BlockColor{0, 0, 0, 0}; }

// 虚空（整列无方块）时显示的颜色：优先取 biome_color.json 中的群系 rgb 代表色，
// 缺失时回退到游戏内群系草地色采样（与地图上草地方块同色）
static BlockColor getBiomeVoidColor(LevelChunk* chunk, ChunkWorldPos pos, int minY) {
    ChunkBlockPos localPos(static_cast<uchar>(pos.x), ChunkLocalHeight{0}, static_cast<uchar>(pos.z));
    Biome const&  biome = chunk->getBiome(localPos);
    if (auto color = BiomeColorMap::getInstance().rgbOf(biome.mHash->getString())) return *color;
    BlockPos worldPos(chunk->mPosition->x * 16 + pos.x, minY, chunk->mPosition->z * 16 + pos.z);
    int      argb = BiomeColorSampling::getMapGrassColor(biome, worldPos);
    return BlockColor{
        static_cast<std::uint8_t>((argb >> 16) & 0xFF),
        static_cast<std::uint8_t>((argb >> 8) & 0xFF),
        static_cast<std::uint8_t>(argb & 0xFF),
        255
    };
}

// 判断方块是否不透明（材质为固体即视为不透明，替代原 block_color.json 的 alpha 查表）
static bool isBlockOpaque(Block const& block) { return block.getMaterial().mSolid; }

// 处理水的特殊效果（透明水）：拆出水下固体色与水面信息，混合推迟到烘焙期阴影之后
WaterSplit
processWater(LevelChunk* chunk, BlockSource& source, int cx, int cz, int waterSurfaceY, int minY, bool& outHitPlaceholder) {
    WaterSplit result;

    // 获取水颜色（含群系染色）
    result.waterSurfaceColor =
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
        // 水下方块是占位符（子区块未加载完）时也置标记，让上层快速回扫
        if (solidName == "minecraft:client_request_placeholder_block") outHitPlaceholder = true;
        if (solidName != "minecraft:water" && solidName != "minecraft:air" && solidName != "air") {
            foundSolid = true;
            break;
        }
    }

    if (foundSolid) {
        result.solidColor =
            getBlockMapColor(chunk, source, {static_cast<uchar>(cx), static_cast<uchar>(cz)}, solidY);
        result.waterDepth = static_cast<uint8_t>(std::min(waterSurfaceY - solidY, 255));
        return result;
    }

    // 一路到 minY 都是水/空气：深度按到 minY 计（叠加时透明度直接封顶），固体色回退为水面色
    result.solidColor = result.waterSurfaceColor;
    result.waterDepth = static_cast<uint8_t>(std::min(waterSurfaceY - minY, 255));
    return result;
}

// 基于 cameraHeight 的方块颜色获取，同时返回高度信息
BlockColor getTerrainPixelAtCameraHeight(
    LevelChunk*   chunk,
    ChunkWorldPos pos,
    int           cameraHeight,
    bool&         outHitPlaceholder,
    WaterSplit*   outWater
) {
    int minY = chunk->mMin->y;
    int maxY = chunk->mMax->y;

    BlockSource& source = chunk->mDimension.getBlockSourceFromMainChunkSource();

    // 高度信息
    int surfaceHeight = (*chunk->mHeightmap)[16 * pos.z + pos.x].mVal + minY;

    // 检查 cameraHeight 是否在有效范围内
    if (cameraHeight < minY) {
        return getEmptyColor();
    }

    auto getBlockAt = [&](int y) -> Block const& {
        return chunk->getBlock(ChunkBlockPos(
            static_cast<uchar>(pos.x),
            ChunkLocalHeight{static_cast<short>(y - minY)},
            static_cast<uchar>(pos.z)
        ));
    };

    auto getBlockName = [&](int y) -> std::string {
        std::string name = getBlockAt(y).getTypeName();
        if (name == "minecraft:client_request_placeholder_block") outHitPlaceholder = true;
        return name;
    };

    auto blockColorAt = [&](int y) -> BlockColor { return getBlockMapColor(chunk, source, pos, y); };

    // 透明水：拆出水面信息交给烘焙期叠加，此处只返回水下固体色
    auto waterPixel = [&](int y) -> BlockColor {
        WaterSplit ws = processWater(chunk, source, pos.x, pos.z, y, minY, outHitPlaceholder);
        if (outWater) *outWater = ws;
        return ws.solidColor;
    };

    // 虚空（整列无方块）：显示群系颜色
    auto voidColor = [&]() -> BlockColor { return getBiomeVoidColor(chunk, pos, minY); };

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
                        return waterPixel(y - 1);
                    }

                    return blockColorAt(y - 1);
                }
                return voidColor();
            }
        }

        // 到达 maxY 仍未找到空气
        std::string surfaceName = getBlockName(maxY);

        if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
            return waterPixel(maxY);
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
                            return waterPixel(y - 1);
                        }

                        return blockColorAt(y - 1);
                    }
                    return voidColor();
                }
            }

            // 到达 cameraHeight 仍未找到空气
            std::string surfaceName = getBlockName(cameraHeight);

            if (config::getConfig().terrain.enableTransparentWater && surfaceName == "minecraft:water") {
                return waterPixel(cameraHeight);
            }

            return blockColorAt(cameraHeight);
        } else {
            // mHeightmap >= cameraHeight，说明在地下或地表
            for (int y = cameraHeight; y >= minY; --y) {
                std::string name = getBlockName(y);

                if (name != "minecraft:air" && name != "air") {
                    // 找到非空气方块
                    if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                        return waterPixel(y);
                    }
                    return blockColorAt(y);
                }
            }
            return voidColor();
        }
    }

    // 情况 2: cameraHeight 处不是空气，判断透明度
    bool isOpaque = isBlockOpaque(getBlockAt(cameraHeight));

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
                            return waterPixel(y2);
                        }
                        return blockColorAt(y2);
                    }
                }
                return voidColor();
            }

            bool currentOpaque = isBlockOpaque(getBlockAt(y));
            if (!currentOpaque) {
                // 找到半透明方块，直接显示
                if (config::getConfig().terrain.enableTransparentWater && name == "minecraft:water") {
                    return waterPixel(y);
                }
                return blockColorAt(y);
            }
            // 不透明方块，继续向下（跳过第一段连续的不透明方块）
        }
        return getEmptyColor();
    } else {
        // 半透明：直接显示这个方块
        if (config::getConfig().terrain.enableTransparentWater && cameraName == "minecraft:water") {
            return waterPixel(cameraHeight);
        }
        return blockColorAt(cameraHeight);
    }
}

} // namespace coral_map
