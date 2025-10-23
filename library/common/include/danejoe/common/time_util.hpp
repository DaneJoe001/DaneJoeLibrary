#pragma once

/**
 * @file time_util.hpp
 * @brief 时间工具类
 * @author DaneJoe001 
 * @version 0.1.1
 * @date 2025-10-24
 */

#include <chrono>
#include <cstdint>
#include <string>

/// @brief 获取当前时间字符串
#define DANEJOE_NOW_TIME_STR DaneJoe::TimeUtil::get_now_time_str()

/**
 * @namespace DaneJoe
 * @brief DaneJoe命名空间
 */
namespace DaneJoe
{
    /**
     * @class TimeUtil
     * @brief 时间工具类
     */
    class TimeUtil
    {
    public:
        /**
         * @brief 获取当前时间字符串
         * @return std::string 时间字符串
         */
        static std::string get_now_time_str();
        /**
         * @brief 获取指定时间点对应的时间字符串
         * @param tp 时间点
         */
        static std::string get_time_str(const std::chrono::system_clock::time_point& tp);
        /**
         * @brief 获取当前时间戳毫秒
         * @return int64_t 时间戳(毫秒)
         */
        static int64_t get_time_stamp_ms(const std::chrono::system_clock::time_point& tp);
        /**
         * @brief 获取指定时间戳对应的时间点
         * @param timestamp 时间戳(毫秒)
         */
        static std::chrono::system_clock::time_point get_time_point_ms(int64_t timestamp);
    };
}