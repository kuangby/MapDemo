#pragma once

#include "data/BlockColor.h"


#include <algorithm>
#include <array>
#include <cstdint>

namespace map_demo {

inline int clamp255(int v) { return std::clamp(v, 0, 255); }

inline BlockColor multiplyColor(BlockColor c, float factor) {
    return BlockColor{
        static_cast<std::uint8_t>(clamp255(static_cast<int>(static_cast<float>(c.r) * factor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(static_cast<float>(c.g) * factor))),
        static_cast<std::uint8_t>(clamp255(static_cast<int>(static_cast<float>(c.b) * factor))),
        c.a
    };
}

inline std::array<float, 81> buildBevelTable(int scale) {
    constexpr float kEdgeBright  = 1.18f;
    constexpr float kEdgeDark    = 0.72f;
    constexpr float kCornerBoost = 0.40f;

    const int   edgeW       = std::max(1, scale / 6);
    const float rcpEw       = 1.0f / static_cast<float>(edgeW);
    const int   totalPixels = scale * scale;

    std::array<float, 81> table{};

    // 枚举所有关系组合
    for (int hl = 0; hl < 3; ++hl)
        for (int hr = 0; hr < 3; ++hr)
            for (int ht = 0; ht < 3; ++ht)
                for (int hb = 0; hb < 3; ++hb) {
                    float sumFactor = 0.0f;

                    for (int dy = 0; dy < scale; ++dy) {
                        float tyT = (dy < edgeW) ? 1.0f - static_cast<float>(dy) * rcpEw : 0.0f;
                        float tyB = (dy >= scale - edgeW) ? static_cast<float>(dy - (scale - edgeW)) * rcpEw : 0.0f;

                        for (int dx = 0; dx < scale; ++dx) {
                            float txL = (dx < edgeW) ? 1.0f - static_cast<float>(dx) * rcpEw : 0.0f;
                            float txR = (dx >= scale - edgeW) ? static_cast<float>(dx - (scale - edgeW)) * rcpEw : 0.0f;

                            if (txL == 0.0f && txR == 0.0f && tyT == 0.0f && tyB == 0.0f) {
                                sumFactor += 1.0f;
                                continue;
                            }

                            float factor = 1.0f;

                            // 边缘效应
                            auto applyEdge = [&](float t, int rel) {
                                if (t <= 0.0f) return;
                                if (rel == 1) factor *= 1.0f + (kEdgeBright - 1.0f) * t;
                                else if (rel == 2) factor *= 1.0f + (kEdgeDark - 1.0f) * t;
                            };
                            applyEdge(txL, hl);
                            applyEdge(txR, hr);
                            applyEdge(tyT, ht);
                            applyEdge(tyB, hb);

                            // 角落效应
                            auto applyCorner = [&](float tc, int r1, int r2) {
                                if (tc <= 0.0f) return;
                                if (r1 == 1 && r2 == 1) factor *= 1.0f + (kEdgeBright - 1.0f) * tc * kCornerBoost;
                                else if (r1 == 2 && r2 == 2) factor *= 1.0f + (kEdgeDark - 1.0f) * tc * kCornerBoost;
                            };
                            applyCorner(std::min(txL, tyT), hl, ht);
                            applyCorner(std::min(txR, tyT), hr, ht);
                            applyCorner(std::min(txL, tyB), hl, hb);
                            applyCorner(std::min(txR, tyB), hr, hb);

                            factor     = std::clamp(factor, 0.55f, 1.58f);
                            sumFactor += factor;
                        }
                    }

                    int index    = hl * 27 + hr * 9 + ht * 3 + hb;
                    table[index] = sumFactor / static_cast<float>(totalPixels);
                }

    return table;
}

} // namespace map_demo