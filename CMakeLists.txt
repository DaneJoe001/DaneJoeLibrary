cmake_minimum_required(VERSION 3.20)
project(DaneJoe VERSION 0.1.1 LANGUAGES CXX)

# @brief 组件构建选项
# @note 按需启用各组件；顶层聚合包会根据已构建组件导出对应目标
option(DANEJOE_BUILD_Logger     "Build Logger component"     ON)
option(DANEJOE_BUILD_Common     "Build Common component"     ON)
option(DANEJOE_BUILD_Database   "Build Database component"   ON)
option(DANEJOE_BUILD_Concurrent "Build Concurrent component" ON)
option(DANEJOE_BUILD_Stringify  "Build Stringify component"  ON)
option(DANEJOE_USE_EXTERNAL "Prefer external/ (git submodules) over libs/" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTING "Enable tests" OFF)

# @brief 全局编译设置
# @note 以目标特性声明 C++20；不启用编译器扩展，保证可移植性
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(BUILD_TESTING)
  include(CTest)
  enable_testing()
endif()

# @brief 组件源码来源
# @note 仅支持 external/（git 子模块）或本仓库 library/ 源码
set(_DANEJOE_BASE_DIR "library")
if(DANEJOE_USE_EXTERNAL AND IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/external")
  set(_DANEJOE_BASE_DIR "external")
  message(STATUS "DaneJoe: Using external/ (submodules) for components")
else()
  message(STATUS "DaneJoe: Using library/ (in-tree sources) for components")
endif()

if(DANEJOE_BUILD_Logger)
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${_DANEJOE_BASE_DIR}/logger")
    add_subdirectory("${_DANEJOE_BASE_DIR}/logger")
  else()
    message(FATAL_ERROR "No logger source directory found: ${_DANEJOE_BASE_DIR}/logger")
  endif()
endif()

if(DANEJOE_BUILD_Common)
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${_DANEJOE_BASE_DIR}/common")
    add_subdirectory("${_DANEJOE_BASE_DIR}/common")
  else()
    message(FATAL_ERROR "No Commons source directory found: ${_DANEJOE_BASE_DIR}/common")
  endif()
endif()

if(DANEJOE_BUILD_Database)
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${_DANEJOE_BASE_DIR}/database")
    add_subdirectory("${_DANEJOE_BASE_DIR}/database")
  else()
    message(FATAL_ERROR "No database source directory found: ${_DANEJOE_BASE_DIR}/database")
  endif()
endif()

if(DANEJOE_BUILD_Concurrent)
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${_DANEJOE_BASE_DIR}/concurrent")
    add_subdirectory("${_DANEJOE_BASE_DIR}/concurrent")
  else()
    message(FATAL_ERROR "No concurrent source directory found: ${_DANEJOE_BASE_DIR}/concurrent")
  endif()
endif()

if(DANEJOE_BUILD_Stringify)
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${_DANEJOE_BASE_DIR}/stringify")
    add_subdirectory("${_DANEJOE_BASE_DIR}/stringify")
  else()
    message(FATAL_ERROR "No stringify source directory found: ${_DANEJOE_BASE_DIR}/stringify")
  endif()
endif()

# @brief 安装聚合包（类似 Qt 的 COMPONENTS 用法）
# @note 生成 DaneJoeConfig.cmake/Version，将 COMPONENTS 映射到各独立子包
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_file("cmake/DaneJoeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeConfig.cmake" @ONLY)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/DaneJoeConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DaneJoe")
