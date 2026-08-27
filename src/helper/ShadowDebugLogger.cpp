#include "helper/ShadowDebugLogger.h"

#include "mod/MapDemo.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <thread>

namespace map_demo {

ShadowDebugLogger& ShadowDebugLogger::getInstance() {
    static ShadowDebugLogger instance;
    return instance;
}

void ShadowDebugLogger::write(std::string_view message) {
    std::lock_guard lock(mutex_);

    if (!openTried_) {
        openTried_ = true;
        auto dir = MapDemo::getInstance().getSelf().getDataDir() / "logs";
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        file_.open(dir / "shadow_debug.log", std::ios::app);
        if (!file_) {
            MapDemo::getInstance().getSelf().getLogger().error("ShadowDebugLogger: failed to open log file");
            enabled_ = false;
            return;
        }
    }
    if (!file_) return;

    auto        now = std::chrono::system_clock::now();
    auto        ms  = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t t   = std::chrono::system_clock::to_time_t(now);
    std::tm     tm{};
    localtime_s(&tm, &t);

    file_ << fmt::format(
        "[{:02}:{:02}:{:02}.{:03}][tid={:05}] {}\n",
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        ms.count(),
        std::hash<std::thread::id>{}(std::this_thread::get_id()) % 100000,
        message
    );
    file_.flush();
}

void ShadowDebugLogger::shutdown() {
    std::lock_guard lock(mutex_);
    if (file_) file_.close();
}

} // namespace map_demo
