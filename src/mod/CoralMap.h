#pragma once

#include "ll/api/mod/NativeMod.h"

namespace coral_map {

class CoralMap {

public:
    static CoralMap& getInstance();

    CoralMap() : mSelf(*ll::mod::NativeMod::current()) {}

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

private:
    ll::mod::NativeMod& mSelf;
};

} // namespace coral_map
