#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
@file scripts/sync_subrepos.py
@brief 使用 git subtree 将主仓组件同步到各子仓（Python3 跨平台版）。
@details
  - 在主仓根目录执行（`library_danejoe/`）。
  - 将 `library/<component>` 子树拆分为临时分支并强制推送到子仓目标分支（默认 `master`）。
  - 需要提前配置各组件对应的远程别名。
@usage
  python3 scripts/sync_subrepos.py --all
  python3 scripts/sync_subrepos.py --components logger common --branch master
  python3 scripts/sync_subrepos.py --all --branch monorepo-sync
  python3 scripts/sync_subrepos.py --all --dry-run
@note 默认远程映射：
  - logger      -> github-logger
  - common      -> github-common
  - database    -> github-database
  - concurrent  -> github-concurrent
  - stringify   -> github-stringify
"""
from __future__ import annotations
import argparse
import subprocess
import sys
from typing import List, Dict

DEFAULT_COMPONENTS = [
    ("logger",     "github-logger"),
    ("common",     "github-common"),
    ("database",   "github-database"),
    ("concurrent", "github-concurrent"),
    ("stringify",  "github-stringify"),
]


def run(cmd: List[str], dry_run: bool = False) -> int:
    """@brief 执行命令或在干跑模式下打印。
    @param cmd 命令及参数列表，如 ["git", "status"].
    @param dry_run 若为 True，仅打印不执行。
    @return 进程返回码，干跑时恒为 0。
    """
    print("+", " ".join(cmd))
    if dry_run:
        return 0
    proc = subprocess.run(cmd)
    return proc.returncode


def ensure_branch_deleted(branch: str, dry_run: bool) -> None:
    """@brief 删除本地分支（若不存在则忽略）。
    @param branch 需要删除的分支名。
    @param dry_run 干跑模式。
    """
    # git branch -D <branch> (ignore if missing)
    rc = run(["git", "branch", "-D", branch], dry_run=dry_run)
    if rc != 0:
        # try to continue even if deletion failed (branch may not exist)
        print(f"(info) delete branch {branch} returned {rc}, continuing...")


def sync_component(component: str, remote: str, branch: str, prefix: str, dry_run: bool) -> int:
    """@brief 同步单个组件子树到指定远程分支。
    @param component 组件名（logger/common/database/concurrent/stringify）。
    @param remote 远程名（如 github-logger）。
    @param branch 子仓目标分支，默认 master。
    @param prefix 主仓组件根目录前缀，默认 library。
    @param dry_run 干跑模式。
    @return 非 0 表示失败的返回码。
    """
    split_branch = f"split-{component}"
    print(f"==> Sync {component} -> {remote}:{branch}")
    ensure_branch_deleted(split_branch, dry_run)
    rc = run(["git", "subtree", "split", f"--prefix={prefix}/{component}", "-b", split_branch], dry_run=dry_run)
    if rc != 0:
        print(f"(error) subtree split failed for {component}")
        return rc
    rc = run(["git", "push", "-f", remote, f"{split_branch}:{branch}"], dry_run=dry_run)
    if rc != 0:
        print(f"(error) push failed for {component}")
    return rc


def parse_args(argv: List[str]) -> argparse.Namespace:
    """@brief 解析命令行参数。
    @param argv 参数列表（不含程序名）。
    @return 解析后的命名空间对象。
    """
    p = argparse.ArgumentParser(description="Sync subrepos from monorepo via git subtree")
    g = p.add_mutually_exclusive_group(required=True)
    g.add_argument("--all", action="store_true", help="sync all default components")
    g.add_argument("--components", nargs="*", help="components to sync (subset of: logger common database concurrent stringify)")
    p.add_argument("--branch", default="master", help="target branch in subrepos (default: master)")
    p.add_argument("--prefix", default="library", help="monorepo path prefix (default: library)")
    p.add_argument("--dry-run", action="store_true", help="print commands without executing")
    # allow override remotes via repeated --remote comp=remote
    p.add_argument("--remote", action="append", default=[], help="override remote mapping, e.g. --remote logger=origin-logger")
    return p.parse_args(argv)


def build_mapping(overrides: List[str]) -> Dict[str, str]:
    """@brief 构建组件到远程名的映射表。
    @param overrides 形如 "logger=origin-logger" 的覆盖项列表。
    @return 映射字典，例如 {"logger": "github-logger", ...}。
    """
    mapping = {c: r for c, r in DEFAULT_COMPONENTS}
    for item in overrides:
        if "=" not in item:
            print(f"(warn) ignore invalid --remote item: {item}")
            continue
        c, r = item.split("=", 1)
        c = c.strip(); r = r.strip()
        if not c or not r:
            print(f"(warn) ignore invalid --remote item: {item}")
            continue
        mapping[c] = r
    return mapping


def main(argv: List[str]) -> int:
    """@brief 程序入口。
    @param argv 命令行参数（不含程序名）。
    @return 进程退出码。
    """
    args = parse_args(argv)
    mapping = build_mapping(args.remote)

    if args.all:
        components = [c for c, _ in DEFAULT_COMPONENTS]
    else:
        # components specified explicitly
        components = args.components or []
        unknown = [c for c in components if c not in mapping]
        if unknown:
            print(f"(error) unknown components: {', '.join(unknown)}")
            return 2

    # execute
    status = 0
    for comp in components:
        remote = mapping[comp]
        rc = sync_component(comp, remote, args.branch, args.prefix, args.dry_run)
        status = status or rc
    if status == 0:
        print("All components synced.")
    return status


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
