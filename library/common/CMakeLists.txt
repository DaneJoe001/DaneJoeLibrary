cmake_minimum_required(VERSION 3.20)
project(DaneJoeCommon VERSION 0.1.0 LANGUAGES CXX)
option(DANEJOE_COMMON_BUILD_TESTS "Build tests for DaneJoeCommon" ON)

# @brief 定义实用工具库目标
# @note 通过命名空间别名 `DaneJoe::Commons` 对外暴露
add_library(DaneJoeCommon
  "source/danejoe/common/data_type.cpp"
  "source/danejoe/common/process_util.cpp"
  "source/danejoe/common/time_util.cpp"
  "include/danejoe/common/process_util.hpp"
  "include/danejoe/common/time_util.hpp"
)
add_library(DaneJoe::Commons ALIAS DaneJoeCommon)

# @brief 公开头文件目录
# @note BUILD_INTERFACE 指向源码树；INSTALL_INTERFACE 指向安装树
target_include_directories(DaneJoeCommon
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# @brief 以目标特性声明 C++20
target_compile_features(DaneJoeCommon PUBLIC cxx_std_20)

# @brief 安装目标与头文件
include(GNUInstallDirs)
install(TARGETS DaneJoeCommon
  EXPORT DaneJoeCommonTargets
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# 生成版本头并安装
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/include/danejoe/version/common_version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/include/danejoe/version/common_version.h"
  @ONLY
)
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/include/danejoe/version/common_version.h"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/danejoe/version")

# @brief 生成并安装 CMake 包配置（Config + Version + Targets）
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeCommonConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_file("cmake/DaneJoeUtilsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeCommonConfig.cmake" @ONLY)

install(EXPORT DaneJoeCommonTargets
  NAMESPACE DaneJoe::
  FILE DaneJoeCommonTargets.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DaneJoeCommon"
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeCommonConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeCommonConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DaneJoeCommon"
)

if(DANEJOE_COMMON_BUILD_TESTS)
  include(CTest)
  enable_testing()
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
  endif()
endif()
