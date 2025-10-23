# CI 指南（GitHub Actions）

本项目提供主仓工作流 `.github/workflows/ci.yml`，自动执行：
- 构建与测试：对每个组件（logger/common/database/concurrent/stringify）分别构建与测试
- 安装与 `find_package()` 验证：确保安装后的包能被外部项目消费

## 触发方式
- push / pull_request / 手动 workflow_dispatch

## 在哪里看结果
- 仓库页面 → Actions → 选择对应 workflow 与运行记录 → 查看 job 与每个 step 的日志输出

## 常见问题
- 缺少依赖：Ubuntu 环境已安装 `cmake`、`ninja-build`，并为 database 安装了 `libsqlite3-dev`
- 测试失败：在本地执行与 CI 相同命令进行复现：
  ```bash
  cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
  cmake --build build --parallel
  ctest --test-dir build --output-on-failure
  ```
- 子仓 CI：可以复制主仓的 `build-test` job 至子仓，仅保留自身组件。
