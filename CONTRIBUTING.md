# Contributing

- 分支策略：`master` 受保护；从 `feature/<topic>` 或 `fix/<topic>` 发起 PR。
- 提交消息：遵循你的规范 `commit0x: 简要说明`，例如：`commit12: fix logger rotation bug`。
- 本地构建与测试：
  - 主仓：
    ```bash
    cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
    cmake --build build --parallel
    ctest --test-dir build --output-on-failure
    ```
  - 子仓：在子仓根目录同样执行（按需安装依赖，如 `libsqlite3-dev`）。
- PR 检查清单：
  - [ ] CI 通过（构建 + 测试）
  - [ ] 添加/更新测试
  - [ ] 文档更新（如接口/行为变更）
- 同步策略：
  - 常规：仅在主仓开发，通过 `git subtree` 同步子仓：
    ```bash
    git subtree split --prefix=library/<component> -b split-<component>
    git push -f github-<component> split-<component>:master
    ```
  - 子仓紧急修复后，需合回主仓再下发：
    ```bash
    git subtree pull --prefix=library/<component> github-<component> master --squash
    git subtree split --prefix=library/<component> -b split-<component>
    git push -f github-<component> split-<component>:master
    ```
- 许可证：本项目使用 Apache-2.0。建议源文件添加 SPDX：`// SPDX-License-Identifier: Apache-2.0`。
