#pragma once

/**
 * @file data_type.hpp
 * @brief 数据类型常用类型枚举工具
 * @author DaneJoe001 
 * @version 0.1.1
 * @date 2025-10-24
 */

#include <map>
#include <any>
#include <cstdint>
#include <string>
#include <vector>
#include <type_traits>

/**
 * @namespace DaneJoe
 * @brief DaneJoe 命名空间
 */
namespace DaneJoe
{
    /// @brief C字符串类型
    using CStrType= const char*;
    /**
     * @enum DataType
     * @brief 数据类型
     * @note 主要是为了反序列化时能返回正确的类型
     */
    enum class DataType :uint8_t
    {
        /// @brief 对象
        Object,
        /// @brief 无符号8位整数
        UInt8,
        /// @brief 有符号8位整数
        Int8,
        /// @brief 无符号16位整数
        UInt16,
        /// @brief 有符号16位整数
        Int16,
        /// @brief 无符号32位整数
        UInt32,
        /// @brief 有符号32位整数
        Int32,
        /// @brief 无符号64位整数
        UInt64,
        /// @brief 有符号64位整数
        Int64,
        /// @brief 单精度浮点数
        Float,
        /// @brief 双精度浮点数
        Double,
        /// @brief 使用一字节01表示
        Bool,
        /// @brief 字符串，字符编码由标志位确定
        /// @note 当前默认使用UTF-8，后续再拓展
        String,
        /// @brief 字节流
        ByteArray,
        /// @brief 映射
        Map,
        /// @brief 数组
        Array,
        /// @brief 字典
        Dictionary,
        /// @brief 空值
        Null,
        /// @brief 未知类型
        Unknown
    };

    /**
     * @brief 获取数据类型枚举
     * @tparam 数据类型
     * @return DataType 数据类型枚举
     */
    template <class T>
    DataType get_data_type()
    {
        if constexpr (std::is_same_v<T, uint8_t>)
        {
            return DataType::UInt8;
        }
        else if constexpr (std::is_same_v<T, int8_t>)
        {
            return DataType::Int8;
        }
        else if constexpr (std::is_same_v<T, uint16_t>)
        {
            return DataType::UInt16;
        }
        else if constexpr (std::is_same_v<T, int16_t>)
        {
            return DataType::Int16;
        }
        else if constexpr (std::is_same_v<T, uint32_t>)
        {
            return DataType::UInt32;
        }
        else if constexpr (std::is_same_v<T, int32_t>)
        {
            return DataType::Int32;
        }
        else if constexpr (std::is_same_v<T, uint64_t>)
        {
            return DataType::UInt64;
        }
        else if constexpr (std::is_same_v<T, int64_t>)
        {
            return DataType::Int64;
        }
        else if constexpr (std::is_same_v<T, float>)
        {
            return DataType::Float;
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return DataType::Double;
        }
        else if constexpr (std::is_same_v<T, bool>)
        {
            return DataType::Bool;
        }
        else if constexpr (std::is_same_v<T, std::string>)
        {
            return DataType::String;
        }
        else if constexpr (std::is_same_v<T, std::vector<uint8_t>>)
        {
            return DataType::ByteArray;
        }
        else if constexpr (std::is_same_v<T, std::nullptr_t>)
        {
            return DataType::Null;
        }
        else if constexpr (std::is_same_v<std::decay_t<T>, CStrType>)
        {
            return DataType::String;
        }
        else
        {
            return DataType::Unknown;
        }
    }
    /**
     * @brief 获取数据类型长度
     * @note 仅支持基础数据类型
     * @param type 数据类型枚举
     * @return uint32_t 数据类型长度
     * @note 变长类型返回0
     */
    uint32_t get_data_type_length(DataType type);
    /**
     * @brief 获取数据类型字符串
     * @param type 数据类型枚举
     * @return std::string 数据类型字符串
     */
    std::string to_string(DataType type);
    /**
     * @brief 获取数据类型枚举
     * @param type_code 数据类型标志位
     * @return DataType 数据类型枚举
     */
    DataType to_data_type(uint8_t type_code);

}