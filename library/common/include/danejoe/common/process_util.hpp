#pragma once

/**
 * @file process_util.hpp
 * @brief 进程工具类
 * @author DaneJoe001 
 * @version 0.1.1
 * @date 2025-10-24
 */

/**
 * @namespace DaneJoe
 * @brief DaneJoe命名空间
  */
namespace DaneJoe
{
    /**
     * @class UtilProcess
     * @brief 进程工具类
     */
    class ProcessUtil
    {
    public:
        /**
         * @brief 获取进程ID
         * @return 进程ID
         */
        static int get_pid();
    };
};