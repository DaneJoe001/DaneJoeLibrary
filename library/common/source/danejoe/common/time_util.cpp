#include <ctime>
#include <sstream>
#include <iomanip>

#include "danejoe/common/time_util.hpp"

std::string DaneJoe::TimeUtil::get_now_time_str()
{
    using namespace std::chrono;
    auto now = system_clock::now();
    return get_time_str(now);
}

std::string DaneJoe::TimeUtil::get_time_str(const std::chrono::system_clock::time_point& tp)
{
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &tt);
#else
    localtime_r(&tt, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int64_t DaneJoe::TimeUtil::get_time_stamp_ms(const std::chrono::system_clock::time_point& tp)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
}

std::chrono::system_clock::time_point DaneJoe::TimeUtil::get_time_point_ms(int64_t timestamp)
{
    return std::chrono::system_clock::time_point(std::chrono::milliseconds(timestamp));
}
