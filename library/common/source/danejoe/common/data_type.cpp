#include "danejoe/common/data_type.hpp"

uint32_t DaneJoe::get_data_type_length(DataType type)
{
    switch (type)
    {
        case DataType::UInt8:  return 1;
        case DataType::Int8:   return 1;
        case DataType::UInt16: return 2;
        case DataType::Int16:  return 2;
        case DataType::UInt32: return 4;
        case DataType::Int32:  return 4;
        case DataType::UInt64: return 8;
        case DataType::Int64:  return 8;
        case DataType::Float:  return 4;
        case DataType::Double: return 8;
        default: return 0;
    }
}

std::string DaneJoe::to_string(DataType type)
{
    switch (type)
    {
        case DataType::Object:     return "Object";
        case DataType::UInt8:      return "UInt8";
        case DataType::Int8:       return "Int8";
        case DataType::UInt16:     return "UInt16";
        case DataType::Int16:      return "Int16";
        case DataType::UInt32:     return "UInt32";
        case DataType::Int32:      return "Int32";
        case DataType::UInt64:     return "UInt64";
        case DataType::Int64:      return "Int64";
        case DataType::Float:      return "Float";
        case DataType::Double:     return "Double";
        case DataType::Bool:       return "Bool";
        case DataType::String:     return "String";
        case DataType::ByteArray:  return "ByteArray";
        case DataType::Map:        return "Map";
        case DataType::Array:      return "Array";
        case DataType::Dictionary: return "Dictionary";
        case DataType::Null:       return "Null";
        case DataType::Unknown:    return "Unknown";
        default:                   return "Unknown";
    }
}

DaneJoe::DataType DaneJoe::to_data_type(uint8_t type_code)
{
    // 若外部有自定义编码规则，可在此调整映射。
    // 默认按枚举顺序进行映射，越界则返回 Unknown。
    switch (type_code)
    {
        case 0:  return DataType::Object;
        case 1:  return DataType::UInt8;
        case 2:  return DataType::Int8;
        case 3:  return DataType::UInt16;
        case 4:  return DataType::Int16;
        case 5:  return DataType::UInt32;
        case 6:  return DataType::Int32;
        case 7:  return DataType::UInt64;
        case 8:  return DataType::Int64;
        case 9:  return DataType::Float;
        case 10: return DataType::Double;
        case 11: return DataType::Bool;
        case 12: return DataType::String;
        case 13: return DataType::ByteArray;
        case 14: return DataType::Map;
        case 15: return DataType::Array;
        case 16: return DataType::Dictionary;
        case 17: return DataType::Null;
        default: return DataType::Unknown;
    }
}