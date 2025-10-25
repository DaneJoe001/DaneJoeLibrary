# 本地子库便捷开发工作流（Git Worktree + Sparse-Checkout）

## 适用场景
- **专注子库开发**：仅在 `library/<子库>/` 范围内开发与提交，减少干扰。
- **不改集成方式**：不引入 Submodule/Subtree，保留根仓的历史与 CI 结构。
- **随时提交**：提交记录归属于根仓指定分支，不会丢失。

## 核心思路
- 使用 `git worktree` 新建一个“子库专注”的工作树目录。
- 在该工作树启用 `sparse-checkout`，只检出目标子库路径。
- 在此目录中编辑、构建与提交，历史记录保存在根仓的分支里。

---

## 快速开始（以 `library/stringify/` 为例）
```bash
# 1) 在根仓工作树中：为子库开发新增一个工作树 + 分支
git worktree add ../wt-stringify -b feat/stringify

# 2) 进入新工作树
cd ../wt-stringify

# 3) 启用稀疏检出，仅聚焦子库目录
git sparse-checkout init --cone
git sparse-checkout set library/stringify

# 4) 正常开发、提交（提交记录属于根仓 feat/stringify 分支）
git add .
git commit -m "feat(stringify): 初始实现"
git push origin feat/stringify
```

### 合并与清理
```bash
# 在根仓主工作树中合并开发分支
# 示例：将 feat/stringify 合并回 main
git checkout main
git merge --no-ff feat/stringify

# 不再需要该工作树时进行清理（谨慎）
git worktree remove ../wt-stringify
# 如遇“工作树非干净”限制，请先清理该目录或使用 --force（谨慎）
```

---

## 子库 CMake 可独立工作
> 若子库自带独立的 CMake 构建入口，可直接在工作树中独立构建与运行测试。

- 目录示例：`library/stringify/`
- 在 `../wt-stringify` 工作树中执行：
```bash
# 独立构建（按子库自身 CMakeLists.txt 布局）
cd library/stringify
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j

# 运行测试（如子库提供）
ctest --test-dir build --output-on-failure
```

- 若子库对根工程存在依赖（例如公共头或工具链配置），建议仍从根工程发起构建：
```bash
# 在 wt-stringify 工作树根目录下
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
# 可通过 CMakePresets.json 进一步简化
```

---

## 容器/数组/集合等调试构建提示
- 在“稀疏检出”的子库视图下，仍可引用根仓的公共头与工具（路径相对和 include 路径需在 CMake 中配置妥当）。
- 如需只构建子库相关目标，可在根 CMake/Presets 中为子库目标定义独立的构建 preset 或通过 `--target <name>` 指定。

---

## 与其他方案对比
- **Submodule**：适合子库独立版本/远程/对外分发；本地便捷性不如本方案；维护成本更高。
- **Subtree**：适合“一仓协作，对外镜像同步”；但无法直接获得“仅子库视图”的体验。
- **在子目录直接 `git init`（嵌套仓库）**：不推荐，会导致双重追踪与工具链混乱。

---

## 常见问题
- Q：为什么不直接在当前工作树做 `sparse-checkout`？
  - A：会影响主开发视图，且切换目录集较繁琐。单独 `worktree` 更清爽、互不影响。
- Q：提交会不会丢失？
  - A：不会。所有提交都落在根仓的分支上（例如 `feat/stringify`）。
- Q：如何并行开发多个子库？
  - A：为每个子库新建一个工作树与分支，例如 `../wt-logger`、`../wt-database` 等。

---

## 约定与建议
- 建议以 `wt-<name>` 命名工作树目录，以 `feat/<name>` 命名开发分支。
- 子库若具备独立 CMake，优先在子库目录下独立构建；否则从根工程构建以复用通用配置。
- 如需 CI 支持“子库聚焦构建”，在根 CMake 或 Presets 中为子库定义独立 target/preset。
