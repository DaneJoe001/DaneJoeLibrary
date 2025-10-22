# DaneJoe C++ Libraries

高质量、模块化的 C++ 组件库集合，可独立或聚合使用：`logger`、`common`、`database`、`concurrent`、`stringify`。

## 特性
- **模块化**：每个组件均可独立安装和使用，也可通过聚合包统一接入
- **现代 C++**：统一 C++20，跨平台、可移植
- **完善安装包**：提供 `Config/Version/Targets`，便于 `find_package()`
- **一致的测试结构**：各组件提供 `demo` 可执行样例

## 快速开始
```bash
cmake -S . -B build --preset gcc-debug -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build -N
```

## 组件一览
- `library/logger/`：日志库（别名 `DaneJoe::Logger`）
- `library/common/`：通用工具（别名 `DaneJoe::Commons`）
- `library/database/`：数据库抽象（别名 `DaneJoe::Database`）
- `library/concurrent/`：并发容器/线程池（别名 `DaneJoe::Concurrent`）
- `library/stringify/`：字符串化工具（别名 `DaneJoe::Stringify`）

## 文档
- 组件开发规范与测试模板：`document/COMPONENT_GUIDE.md`
- 各组件说明：
  - `library/logger/README.md`
  - `library/common/README.md`
  - `library/database/README.md`
  - `library/concurrent/README.md`
  - `library/stringify/README.md`

## 使用方式（外部项目）
- 安装后聚合接入：`find_package(DaneJoe CONFIG REQUIRED)`
- 精确接入某个组件：`find_package(DaneJoeLogger CONFIG REQUIRED)` 等
- 源码联编：`add_subdirectory(<path-to-repo>)`

欢迎根据组件需求选用或扩展，详细开发规范见 `document/COMPONENT_GUIDE.md`。
