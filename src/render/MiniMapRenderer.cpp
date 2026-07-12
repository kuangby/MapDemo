#include "render/MiniMapRenderer.h"

#include "config/Config.h"
#include "data/BlockColor.h"
#include "data/pos/ChunkWorldPos.h"
#include "data/pos/RegionChunkPos.h"
#include "data/pos/RegionPos.h"
#include "data/pos/WorldPos.h"
#include "mod/MapDemo.h"
#include "state/render/RegionRenderer.h"


#include <imgui.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>

#include "data/cache/MapCacheManager.h"
#include "state/ChunkManager.h"
#include "state/MapState.h"


namespace map_demo {

using Clock = std::chrono::high_resolution_clock;

MiniMapRenderer& MiniMapRenderer::getInstance() {
    static MiniMapRenderer instance;
    return instance;
}

float MiniMapRenderer::getMapDiameter() const {
    auto& io  = ImGui::GetIO();
    auto& cfg = config::getConfig().miniMap;
    return io.DisplaySize.x * cfg.sizeRatio;
}

namespace {

ImU32 toImCol32(std::uint32_t rgba) {
    std::uint8_t r = (rgba >> 24) & 0xFF;
    std::uint8_t g = (rgba >> 16) & 0xFF;
    std::uint8_t b = (rgba >> 8) & 0xFF;
    std::uint8_t a = rgba & 0xFF;
    return IM_COL32(r, g, b, a);
}

bool pointInCircle(const ImVec2& p, const ImVec2& center, float radius) {
    float dx = p.x - center.x;
    float dy = p.y - center.y;
    return dx * dx + dy * dy <= radius * radius;
}

bool clipLineToCircle(
    const ImVec2& a,
    const ImVec2& b,
    const ImVec2& center,
    float         radius,
    ImVec2&       outA,
    ImVec2&       outB
) {
    float  r2 = radius * radius;
    ImVec2 d  = ImVec2(b.x - a.x, b.y - a.y);
    ImVec2 f  = ImVec2(a.x - center.x, a.y - center.y);

    float A = d.x * d.x + d.y * d.y;
    float B = 2.0f * (f.x * d.x + f.y * d.y);
    float C = f.x * f.x + f.y * f.y - r2;

    if (A < 0.0001f) {
        if (pointInCircle(a, center, radius)) {
            outA = a;
            outB = b;
            return true;
        }
        return false;
    }

    float disc = B * B - 4.0f * A * C;
    if (disc < 0.0f) {
        if (pointInCircle(a, center, radius)) {
            outA = a;
            outB = b;
            return true;
        }
        return false;
    }

    disc     = std::sqrt(disc);
    float t1 = (-B - disc) / (2.0f * A);
    float t2 = (-B + disc) / (2.0f * A);

    t1 = std::clamp(t1, 0.0f, 1.0f);
    t2 = std::clamp(t2, 0.0f, 1.0f);

    if (t1 > t2) return false;
    if (t2 < 0.0f || t1 > 1.0f) return false;

    outA = ImVec2(a.x + d.x * t1, a.y + d.y * t1);
    outB = ImVec2(a.x + d.x * t2, a.y + d.y * t2);
    return true;
}

// 绘制一个方块的地表颜色，限制在圆形范围内
void drawTerrainPixel(
    ImDrawList*   drawList,
    float         worldX,
    float         worldZ,
    BlockColor    color,
    const ImVec2& center,
    float         radius,
    float         cx,
    float         cy,
    float         scale
) {
    if (color.a == 0) return;

    // 计算该方块在屏幕上的四个角
    float sx0 = cx + (worldX - 0.5f - center.x) * scale;
    float sx1 = cx + (worldX + 0.5f - center.x) * scale;
    float sy0 = cy + (worldZ - 0.5f - center.y) * scale;
    float sy1 = cy + (worldZ + 0.5f - center.y) * scale;

    // 简单剔除：方块中心离圆心太远就不画
    float dx = (sx0 + sx1) * 0.5f - cx;
    float dy = (sy0 + sy1) * 0.5f - cy;
    if (dx * dx + dy * dy > (radius + scale) * (radius + scale)) return;

    drawList->AddRectFilled(ImVec2(sx0, sy0), ImVec2(sx1, sy1), IM_COL32(color.r, color.g, color.b, color.a));
}

} // namespace

void MiniMapRenderer::render() {
    auto  renderT0 = Clock::now();
    auto& cfg      = config::getConfig();
    auto& mmc      = cfg.miniMap;

    static int s_renderCount = 0;
    ++s_renderCount;
    auto& io    = ImGui::GetIO();
    auto& state = MapState::getInstance();
    state.updateSmoothCamera(io.DeltaTime);
    if (!state.showMiniMap || !state.hasPlayer()) return;

    float diameter = getMapDiameter();
    float radius   = diameter * 0.5f;

    float cx = io.DisplaySize.x - mmc.marginRight - radius;
    float cy = mmc.marginTop + radius;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    ImVec2      center(cx, cy);

    ImU32 bgColor = toImCol32(mmc.backgroundColor);
    {
        std::uint8_t a = static_cast<std::uint8_t>(255 * state.backgroundAlpha);
        bgColor        = (bgColor & 0x00FFFFFF) | (a << IM_COL32_A_SHIFT);
    }
    drawList->AddCircleFilled(center, radius, bgColor, mmc.circleSegments);

    float renderRadiusBlocks = static_cast<float>(mmc.radiusChunks * 16);
    float scale              = radius / renderRadiusBlocks;

    float smoothX = state.smoothX();
    float smoothZ = state.smoothZ();

    auto worldToScreen = [&](float worldX, float worldZ) -> ImVec2 {
        return ImVec2(cx + (worldX - smoothX) * scale, cy + (worldZ - smoothZ) * scale);
    };

    // 请求异步烘焙本帧涉及的所有 region
    // auto requestBake = [&](const RegionPos& pos, const std::shared_ptr<RegionCacheData>& data) {
    //     if (!data || !data->isBakedDirty()) return;
    //     RegionRenderer::getInstance().requestBake(data, pos, pos.dimId);
    // };

    // 绘制地形
    if (cfg.terrain.enable) {
        auto& mapCacheManager = MapCacheManager::getInstance();
        auto& regionRenderer  = RegionRenderer::getInstance();

        int dimId = state.dimensionId();

        int minWorldX = static_cast<int>(std::floor(smoothX - renderRadiusBlocks));
        int maxWorldX = static_cast<int>(std::floor(smoothX + renderRadiusBlocks));
        int minWorldZ = static_cast<int>(std::floor(smoothZ - renderRadiusBlocks));
        int maxWorldZ = static_cast<int>(std::floor(smoothZ + renderRadiusBlocks));

        // for (int worldZ = minWorldZ; worldZ <= maxWorldZ; ++worldZ) {
        //     for (int worldX = minWorldX; worldX <= maxWorldX; ++worldX) {
        //         auto pos = RegionPos(WorldPos{worldX, worldZ, dim});
        //         auto data = MapCacheManager::getInstance().getRegion(pos);
        //         if (!data) continue;

        //         int localX = worldX - (pos.x * RegionData::SIZE);
        //         int localZ = worldZ - (pos.z * RegionData::SIZE);
        //         if (localX < 0) localX += RegionData::SIZE;
        //         if (localZ < 0) localZ += RegionData::SIZE;

        //         auto color = data->getPixel(localX, localZ);
        //         if (color.a == 0) continue;

        //         requestBake(pos, data);
        //         color = data->getBakedPixel(localX, localZ);

        //         drawTerrainPixel(
        //             drawList,
        //             static_cast<float>(worldX),
        //             static_cast<float>(worldZ),
        //             color,
        //             ImVec2(smoothX, smoothZ),
        //             radius - 1.0f,
        //             cx,
        //             cy,
        //             scale
        //         );
        //     }
        // }
        auto minWorldPos = WorldPos{minWorldX, minWorldZ, dimId};
        auto maxWorldPos = WorldPos{maxWorldX, maxWorldZ, dimId};

        auto minRegionPos = RegionPos{minWorldPos};
        auto maxRegionPos = RegionPos{maxWorldPos};

        auto minRegionChunkPos = RegionChunkPos{minWorldPos};
        auto maxRegionChunkPos = RegionChunkPos{maxWorldPos};

        auto minChunkWorldPos = ChunkWorldPos{minWorldPos};
        auto maxChunkWorldPos = ChunkWorldPos{maxWorldPos};

        for (int regionPosZ = minRegionPos.z; regionPosZ <= maxRegionPos.z; regionPosZ++) {
            for (int regionPosX = minRegionPos.x; regionPosX <= maxRegionPos.x; regionPosX++) {
                auto regionPos = RegionPos{regionPosX, regionPosZ, dimId};
                auto region    = mapCacheManager.getRegion(regionPos);

                if (!region) continue;

                if (region->isBakedDirty()) regionRenderer.requestBake(region, regionPos, dimId);

                auto minChunkPos = RegionChunkPos(0, 0);
                if (regionPosX == minRegionPos.x) minChunkPos.x = minRegionChunkPos.x;
                if (regionPosZ == minRegionPos.z) minChunkPos.z = minRegionChunkPos.z;

                auto maxChunkPos = RegionChunkPos(15, 15);
                if (regionPosX == maxRegionPos.x) maxChunkPos.x = maxRegionChunkPos.x;
                if (regionPosZ == maxRegionPos.z) maxChunkPos.z = maxRegionChunkPos.z;

                for (int chunkPosZ = minChunkPos.z; chunkPosZ <= maxChunkPos.z; chunkPosZ++) {
                    for (int chunkPosX = minChunkPos.x; chunkPosX <= maxChunkPos.x; chunkPosX++) {
                        auto chunkPos = RegionChunkPos{chunkPosX, chunkPosZ};
                        auto chunk    = region->getChunkData(chunkPos);

                        if (!chunk) continue;

                        auto minPos = ChunkWorldPos(0, 0);
                        if (regionPosX == minRegionPos.x && chunkPosX == minChunkPos.x) minPos.x = minChunkWorldPos.x;
                        if (regionPosZ == minRegionPos.z && chunkPosZ == minChunkPos.z) minPos.z = minChunkWorldPos.z;

                        auto maxPos = ChunkWorldPos(15, 15);
                        if (regionPosX == maxRegionPos.x && chunkPosX == maxChunkPos.x) maxPos.x = maxChunkWorldPos.x;
                        if (regionPosZ == maxRegionPos.z && chunkPosZ == maxChunkPos.z) maxPos.z = maxChunkWorldPos.z;

                        for (int posZ = minPos.z; posZ <= maxPos.z; posZ++) {
                            for (int posX = minPos.x; posX <= maxPos.x; posX++) {
                                auto       pos       = ChunkWorldPos{posX, posZ};
                                auto&      blockData = chunk->getBlockCacheData(pos);
                                BlockColor color;
                                if (blockData.bakedColor.a) color = blockData.bakedColor;
                                else if (blockData.color.a) color = blockData.color;
                                else continue;

                                auto worldPos = WorldPos{regionPos, chunkPos, pos};

                                drawTerrainPixel(
                                    drawList,
                                    static_cast<float>(worldPos.x),
                                    static_cast<float>(worldPos.z),
                                    color,
                                    ImVec2(smoothX, smoothZ),
                                    radius - 1.0f,
                                    cx,
                                    cy,
                                    scale
                                );
                            }
                        }
                    }
                }
            }
        }
    }

    auto centerChunk = ChunkPos(smoothX, smoothZ);

    ImU32 chunkLineColor    = toImCol32(mmc.chunkLineColor);
    ImU32 currentChunkColor = toImCol32(mmc.currentChunkColor);

    float lineClipRadius = radius - mmc.lineClipInset;
    auto  gridLines      = ChunkManager::getGridLines(centerChunk.x, centerChunk.z, mmc.radiusChunks);

    ImVec2 a, b;
    for (const auto& [z, xRange] : gridLines.horizontal) {
        ImVec2 p1 = worldToScreen(xRange.first, z);
        ImVec2 p2 = worldToScreen(xRange.second, z);
        if (clipLineToCircle(p1, p2, center, lineClipRadius, a, b))
            drawList->AddLine(a, b, chunkLineColor, mmc.lineThickness);
    }
    for (const auto& [x, zRange] : gridLines.vertical) {
        ImVec2 p1 = worldToScreen(x, zRange.first);
        ImVec2 p2 = worldToScreen(x, zRange.second);
        if (clipLineToCircle(p1, p2, center, lineClipRadius, a, b))
            drawList->AddLine(a, b, chunkLineColor, mmc.lineThickness);
    }

    {
        auto   bounds = ChunkManager::getChunkBounds(centerChunk.x, centerChunk.z);
        ImVec2 tl     = worldToScreen(bounds.minX, bounds.minZ);
        ImVec2 tr     = worldToScreen(bounds.maxX, bounds.minZ);
        ImVec2 br     = worldToScreen(bounds.maxX, bounds.maxZ);
        ImVec2 bl     = worldToScreen(bounds.minX, bounds.maxZ);

        if (clipLineToCircle(tl, tr, center, lineClipRadius, a, b))
            drawList->AddLine(a, b, currentChunkColor, mmc.lineThickness);
        if (clipLineToCircle(tr, br, center, lineClipRadius, a, b))
            drawList->AddLine(a, b, currentChunkColor, mmc.lineThickness);
        if (clipLineToCircle(br, bl, center, lineClipRadius, a, b))
            drawList->AddLine(a, b, currentChunkColor, mmc.lineThickness);
        if (clipLineToCircle(bl, tl, center, lineClipRadius, a, b))
            drawList->AddLine(a, b, currentChunkColor, mmc.lineThickness);
    }

    float yawRad = state.renderYawRad();
    float cosY   = std::cos(yawRad);
    float sinY   = std::sin(yawRad);

    auto rotate = [&](float x, float z) -> ImVec2 {
        return ImVec2(cx + (x * cosY - z * sinY), cy + (x * sinY + z * cosY));
    };

    ImU32 arrowOutline = toImCol32(mmc.playerArrowOutlineColor);
    ImU32 arrowFill    = toImCol32(mmc.playerArrowFillColor);

    drawList->AddTriangleFilled(
        rotate(0.0f, -mmc.arrow.length),
        rotate(-mmc.arrow.halfWidth, mmc.arrow.length),
        rotate(mmc.arrow.halfWidth, mmc.arrow.length),
        arrowOutline
    );
    drawList->AddTriangleFilled(
        rotate(0.0f, -mmc.arrow.innerLength),
        rotate(-mmc.arrow.innerWidth, mmc.arrow.innerLength),
        rotate(mmc.arrow.innerWidth, mmc.arrow.innerLength),
        arrowFill
    );

    char coordBuf[64];
    snprintf(
        coordBuf,
        sizeof(coordBuf),
        "%d, %d, %d",
        state.player().blockX(),
        state.player().blockY(),
        state.player().blockZ()
    );
    ImVec2 textSize = ImGui::CalcTextSize(coordBuf);
    ImVec2 textPos(cx - textSize.x * 0.5f, cy + radius + mmc.coordTextMargin);
    drawList->AddText(ImVec2(textPos.x + 1.0f, textPos.y + 1.0f), toImCol32(mmc.coordShadowColor), coordBuf);
    drawList->AddText(textPos, toImCol32(mmc.coordTextColor), coordBuf);

    drawList->AddCircle(center, radius, toImCol32(mmc.borderColor), mmc.circleSegments, mmc.borderThickness);

    if (s_renderCount % 60 == 0) {
        auto totalUs = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - renderT0).count();
        MapDemo::getInstance().getSelf().getLogger().debug(
            "MiniMapRenderer::render: count={}, total={}us",
            s_renderCount,
            totalUs
        );
    }
}

} // namespace map_demo
