#pragma once

#include <cstdint>


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
} // namespace map_demo