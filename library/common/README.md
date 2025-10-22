# DaneJoe Common

实用工具库（时间、进程、数据类型 to_string 等）。

## 构建
```bash
cmake -S . -B build --preset gcc-debug -DBUILD_TESTING=ON
cmake --build build
```

## 运行示例/测试
```bash
ctest --test-dir build -V -R common\.demo
# 或直接运行
./build/library/common/tests/danejoe_common_demo
```

## 作为依赖使用
CMake:
```cmake
find_package(DaneJoeCommon CONFIG REQUIRED)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE DaneJoe::Commons)
```
