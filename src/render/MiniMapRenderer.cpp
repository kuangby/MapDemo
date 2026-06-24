#include "render/MiniMapRenderer.h"

#include "mod/MapDemo.h"

#include <imgui.h>

#include <algorithm>
#include <cmath>
#include <cstdio>

#include "state/ChunkManager.h"
#include "state/MapState.h"

namespace map_demo {

MiniMapRenderer& MiniMapRenderer::getInstance() {
    static MiniMapRenderer instance;
    return instance;
}

float MiniMapRenderer::getMapDiameter() const {
    auto& io = ImGui::GetIO();
    return io.DisplaySize.x * MAP_SIZE_RATIO;
}

namespace {

bool clipLineToCircle(const ImVec2& a, const ImVec2& b, const ImVec2& center, float radius, ImVec2& outA, ImVec2& outB) {
    float r2 = radius * radius;
    auto inCircle = [&](const ImVec2& p) -> bool {
        float dx = p.x - center.x;
        float dy = p.y - center.y;
        return dx * dx + dy * dy <= r2;
    };

    ImVec2 d = ImVec2(b.x - a.x, b.y - a.y);
    ImVec2 f = ImVec2(a.x - center.x, a.y - center.y);

    float A = d.x * d.x + d.y * d.y;
    float B = 2.0f * (f.x * d.x + f.y * d.y);
    float C = f.x * f.x + f.y * f.y - r2;

    if (A < 0.0001f) {
        if (inCircle(a)) {
            outA = a;
            outB = b;
            return true;
        }
        return false;
    }

    float disc = B * B - 4.0f * A * C;
    if (disc < 0.0f) {
        if (inCircle(a)) {
            outA = a;
            outB = b;
            return true;
        }
        return false;
    }

    disc = std::sqrt(disc);
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

} // namespace

void MiniMapRenderer::render() {
    static int s_renderCount = 0;
    if (++s_renderCount % 60 == 0) {
        auto& state = MapState::getInstance();
        MapDemo::getInstance().getSelf().getLogger().debug(
            "MiniMapRenderer::render: count={}, hasPlayer={}", s_renderCount, state.hasPlayer()
        );
    }
    auto& io    = ImGui::GetIO();
    auto& state = MapState::getInstance();
    state.updateSmoothCamera(io.DeltaTime);
    if (!state.showMiniMap || !state.hasPlayer()) return;

    float diameter = getMapDiameter();
    float radius   = diameter * 0.5f;

    float cx = io.DisplaySize.x - MARGIN_RIGHT - radius;
    float cy = MARGIN_TOP + radius;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    ImVec2      center(cx, cy);

    // 背景（黑色圆形）
    ImU32 bgColor = IM_COL32(0, 0, 0, static_cast<int>(255 * state.backgroundAlpha));
    drawList->AddCircleFilled(center, radius, bgColor, 64);

    float renderRadiusBlocks = static_cast<float>(MAP_RADIUS_CHUNKS * 16);
    float scale              = radius / renderRadiusBlocks;

    float smoothX = state.smoothX();
    float smoothZ = state.smoothZ();

    auto worldToScreen = [&](float worldX, float worldZ) -> ImVec2 {
        return ImVec2(cx + (worldX - smoothX) * scale, cy + (worldZ - smoothZ) * scale);
    };

    auto centerChunk   = ChunkManager::worldToChunk(smoothX, smoothZ);
    auto visibleChunks = ChunkManager::getInstance().getVisibleChunks(centerChunk.x, centerChunk.z, MAP_RADIUS_CHUNKS);

    ImU32 chunkLineColor    = IM_COL32(120, 120, 120, 255);
    ImU32 currentChunkColor = IM_COL32(60, 160, 255, 255);

    // 绘制区块边界线（精确圆形裁剪，留出 1px 边距防止线宽溢出）
    float lineClipRadius = radius - 1.0f;
    for (const auto& chunk : visibleChunks) {
        auto bounds = ChunkManager::getChunkBounds(chunk.x, chunk.z);

        // 简单剔除：chunk 中心太远就不画
        float chunkCenterX = (bounds.minX + bounds.maxX) * 0.5f;
        float chunkCenterZ = (bounds.minZ + bounds.maxZ) * 0.5f;
        float dx           = chunkCenterX - smoothX;
        float dz           = chunkCenterZ - smoothZ;
        float dist         = std::sqrt(dx * dx + dz * dz);
        if (dist > renderRadiusBlocks + 11.3f) continue; // 11.3 = half chunk diagonal

        ImVec2 tl = worldToScreen(bounds.minX, bounds.minZ);
        ImVec2 tr = worldToScreen(bounds.maxX, bounds.minZ);
        ImVec2 br = worldToScreen(bounds.maxX, bounds.maxZ);
        ImVec2 bl = worldToScreen(bounds.minX, bounds.maxZ);

        ImVec2 a, b;
        if (clipLineToCircle(tl, tr, center, lineClipRadius, a, b)) drawList->AddLine(a, b, chunkLineColor, 1.0f);
        if (clipLineToCircle(tr, br, center, lineClipRadius, a, b)) drawList->AddLine(a, b, chunkLineColor, 1.0f);
        if (clipLineToCircle(br, bl, center, lineClipRadius, a, b)) drawList->AddLine(a, b, chunkLineColor, 1.0f);
        if (clipLineToCircle(bl, tl, center, lineClipRadius, a, b)) drawList->AddLine(a, b, chunkLineColor, 1.0f);
    }

    // 当前 chunk 高亮：在 chunk 中心画圆点，避免矩形/粗线溢出圆形
    ImVec2 currentChunkCenter = worldToScreen(centerChunk.x * 16.0f + 8.0f, centerChunk.z * 16.0f + 8.0f);
    {
        float dx = currentChunkCenter.x - center.x;
        float dz = currentChunkCenter.y - center.y;
        if (dx * dx + dz * dz <= radius * radius) {
            drawList->AddCircleFilled(currentChunkCenter, 5.0f, currentChunkColor, 16);
        }
    }

    // 玩家箭头
    float yawRad = (state.smoothYaw() + 180.0f) * 3.14159265f / 180.0f;
    float cosY   = std::cos(yawRad);
    float sinY   = std::sin(yawRad);

    auto rotate = [&](float x, float z) -> ImVec2 {
        return ImVec2(cx + (x * cosY - z * sinY), cy + (x * sinY + z * cosY));
    };

    drawList->AddTriangleFilled(rotate(0.0f, -10.0f), rotate(-7.0f, 10.0f), rotate(7.0f, 10.0f), IM_COL32(0, 0, 0, 255));
    drawList->AddTriangleFilled(rotate(0.0f, -8.0f), rotate(-5.0f, 8.0f), rotate(5.0f, 8.0f), IM_COL32(220, 50, 50, 255));

    // 坐标文字
    char coordBuf[64];
    snprintf(coordBuf, sizeof(coordBuf), "%d, %d, %d", state.player().blockX(), state.player().blockY(), state.player().blockZ());
    ImVec2 textSize = ImGui::CalcTextSize(coordBuf);
    ImVec2 textPos(cx - textSize.x * 0.5f, cy + radius + 8.0f);
    drawList->AddText(ImVec2(textPos.x + 1.0f, textPos.y + 1.0f), IM_COL32(0, 0, 0, 200), coordBuf);
    drawList->AddText(textPos, IM_COL32(255, 255, 255, 255), coordBuf);

    // 小地图外边框
    drawList->AddCircle(center, radius, IM_COL32(80, 80, 80, 255), 64, 2.0f);
}

} // namespace map_demo
