#!/usr/bin/env bash
set -euo pipefail

#/**
# @file scripts/sync_subrepos.sh
# @brief 使用 git subtree 将主仓组件同步到各子仓（bash 版）。
# @details
#  - 需在主仓根目录执行（library_danejoe）。
#  - 默认将 `library/<component>` 子树强制推送到对应远程的 master 分支。
#  - 请确保子仓允许强推或临时取消保护。
# @usage
#  直接执行脚本：`bash scripts/sync_subrepos.sh`
# @note 远程别名约定：github-logger, github-common, github-database, github-concurrent, github-stringify
#*/

# Usage: run from repo root (library_danejoe)
# Requires remotes: github-logger, github-common, github-database, github-concurrent, github-stringify

sync_component () {
  #/**
  # @brief 同步单个组件到指定远程 master。
  # @param $1 组件名（logger/common/database/concurrent/stringify）
  # @param $2 远程名（如 github-logger）
  #*/
  local comp="$1" remote="$2"
  local split="split-$comp"
  echo "==> Sync $comp to $remote:master"
  git branch -D "$split" >/dev/null 2>&1 || true
  git subtree split --prefix="library/$comp" -b "$split"
  git push -f "$remote" "$split:master"
}

sync_component logger      github-logger
sync_component common      github-common
sync_component database    github-database
sync_component concurrent  github-concurrent
sync_component stringify   github-stringify

echo "All components synced."
