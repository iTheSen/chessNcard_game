#!/usr/bin/env python3
"""Prepare cocos2d-x 3rd-party deps (Python 3 replacement for download-deps.py)."""

from __future__ import annotations

import json
import shutil
import sys
import tempfile
import urllib.request
import zipfile
from pathlib import Path


def _safe_remove(path: Path) -> None:
    if path.is_dir():
        shutil.rmtree(path)
    elif path.exists():
        path.unlink()


def _copy_tree_contents(src_dir: Path, dst_dir: Path) -> None:
    for item in src_dir.iterdir():
        target = dst_dir / item.name
        if item.is_dir():
            shutil.copytree(item, target, dirs_exist_ok=True)
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(item, target)


def _patch_macos_audio_header(cocos_root: Path) -> None:
    header_path = cocos_root / "cocos/audio/mac/CDXMacOSXSupport.h"
    if not header_path.exists():
        return

    content = header_path.read_text(encoding="utf-8")
    if "#if __has_include(<AudioToolbox/AudioSession.h>)" in content:
        return

    old_block = (
        "enum AudioSessionProperties {\n"
        "\tkAudioSessionProperty_OtherAudioIsPlaying,\n"
        "\tkAudioSessionProperty_AudioRoute\t\n"
        "};"
    )
    new_block = (
        "#if __has_include(<AudioToolbox/AudioSession.h>)\n"
        "#import <AudioToolbox/AudioSession.h>\n"
        "#else\n"
        "enum AudioSessionProperties {\n"
        "\tkAudioSessionProperty_OtherAudioIsPlaying,\n"
        "\tkAudioSessionProperty_AudioRoute\n"
        "};\n"
        "#endif"
    )

    if old_block not in content:
        return

    header_path.write_text(content.replace(old_block, new_block), encoding="utf-8")
    print(f"[INFO] Patched macOS audio compatibility: {header_path}")


def _patch_macos_audio_manager(cocos_root: Path) -> None:
    source_path = cocos_root / "cocos/audio/mac/CDAudioManager.m"
    if not source_path.exists():
        return

    content = source_path.read_text(encoding="utf-8")

    if "__MAC_OS_X_VERSION_MAX_ALLOWED >= 101500" in content:
        return

    old_is_other_audio = (
        "-(BOOL) isOtherAudioPlaying {\n"
        "    UInt32 isPlaying = 0;\n"
        "    UInt32 varSize = sizeof(isPlaying);\n"
        "    AudioSessionGetProperty (kAudioSessionProperty_OtherAudioIsPlaying, &varSize, &isPlaying);\n"
        "    return (isPlaying != 0);\n"
        "}\n"
    )
    new_is_other_audio = (
        "-(BOOL) isOtherAudioPlaying {\n"
        "#if defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= 101500)\n"
        "    return NO;\n"
        "#else\n"
        "    UInt32 isPlaying = 0;\n"
        "    UInt32 varSize = sizeof(isPlaying);\n"
        "    AudioSessionGetProperty (kAudioSessionProperty_OtherAudioIsPlaying, &varSize, &isPlaying);\n"
        "    return (isPlaying != 0);\n"
        "#endif\n"
        "}\n"
    )

    old_is_device_muted_guard = (
        "#if TARGET_IPHONE_SIMULATOR\n"
        "    //Calling audio route stuff on the simulator causes problems\n"
        "    return NO;\n"
        "#else    \n"
    )
    new_is_device_muted_guard = (
        "#if TARGET_IPHONE_SIMULATOR\n"
        "    //Calling audio route stuff on the simulator causes problems\n"
        "    return NO;\n"
        "#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= 101500)\n"
        "    return NO;\n"
        "#else    \n"
    )

    patched = content
    if old_is_other_audio in patched:
        patched = patched.replace(old_is_other_audio, new_is_other_audio)
    if old_is_device_muted_guard in patched:
        patched = patched.replace(old_is_device_muted_guard, new_is_device_muted_guard, 1)

    if patched != content:
        source_path.write_text(patched, encoding="utf-8")
        print(f"[INFO] Patched macOS audio compatibility: {source_path}")


def _patch_font_atlas_iconv(cocos_root: Path) -> None:
    source_path = cocos_root / "cocos/2d/CCFontAtlas.cpp"
    if not source_path.exists():
        return

    content = source_path.read_text(encoding="utf-8")
    patched = content

    patched = patched.replace("iconv_close(_iconv);", "iconv_close((iconv_t)_iconv);")
    patched = patched.replace("iconv(_iconv, (char**)&pin, &inLen, &pout, &outLen);", "iconv((iconv_t)_iconv, (char**)&pin, &inLen, &pout, &outLen);")

    if patched != content:
        source_path.write_text(patched, encoding="utf-8")
        print(f"[INFO] Patched iconv compatibility: {source_path}")


def _patch_audio_cache_header(cocos_root: Path) -> None:
    header_path = cocos_root / "cocos/audio/apple/AudioCache.h"
    if not header_path.exists():
        return

    content = header_path.read_text(encoding="utf-8")
    patched = content
    if "#include <functional>\n" not in patched:
        patched = patched.replace("#include <vector>\n", "#include <vector>\n#include <functional>\n", 1)
    if "#include <memory>\n" not in patched:
        patched = patched.replace("#include <functional>\n", "#include <functional>\n#include <memory>\n", 1)
    if patched != content:
        header_path.write_text(patched, encoding="utf-8")
        print(f"[INFO] Patched Apple audio header includes: {header_path}")


def main() -> int:
    repo_root = Path(__file__).resolve().parents[1]
    cocos_root = repo_root / "cocos2d"
    external_dir = cocos_root / "external"
    config_path = external_dir / "config.json"

    if not config_path.exists():
        print(f"[ERROR] config not found: {config_path}")
        return 1

    with config_path.open("r", encoding="utf-8") as fp:
        config = json.load(fp)

    version = config["version"]
    repo_name = config["repo_name"]
    repo_parent = config["repo_parent"]
    move_dirs = config.get("move_dirs", {})

    zip_name = f"{version}.zip"
    url = f"{repo_parent}{repo_name}/archive/{zip_name}"
    extracted_root_name = f"{repo_name}-{version[1:]}" if version.startswith("v") else f"{repo_name}-{version}"

    print(f"[INFO] Downloading deps from: {url}")
    with tempfile.TemporaryDirectory(prefix="cocos2d-deps-") as tmp:
        tmp_dir = Path(tmp)
        zip_path = tmp_dir / zip_name

        with urllib.request.urlopen(url) as resp, zip_path.open("wb") as out:
            shutil.copyfileobj(resp, out)

        print(f"[INFO] Extracting: {zip_path.name}")
        with zipfile.ZipFile(zip_path, "r") as zf:
            zf.extractall(tmp_dir)

        extracted_root = tmp_dir / extracted_root_name
        if not extracted_root.exists():
            print(f"[ERROR] extracted folder not found: {extracted_root}")
            return 1

        print("[INFO] Cleaning cocos2d/external ...")
        for item in external_dir.iterdir():
            if item.name == "config.json":
                continue
            _safe_remove(item)

        print("[INFO] Copying deps into cocos2d/external ...")
        _copy_tree_contents(extracted_root, external_dir)

        if move_dirs:
            print("[INFO] Moving special dirs ...")
            for src_name, dst_rel in move_dirs.items():
                src_path = external_dir / src_name
                dst_base = cocos_root / dst_rel
                dst_path = dst_base / src_name
                if not src_path.exists():
                    continue
                dst_base.mkdir(parents=True, exist_ok=True)
                _safe_remove(dst_path)
                shutil.move(str(src_path), str(dst_path))

    _patch_macos_audio_header(cocos_root)
    _patch_macos_audio_manager(cocos_root)
    _patch_font_atlas_iconv(cocos_root)
    _patch_audio_cache_header(cocos_root)

    print("[OK] cocos2d external dependencies are ready.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
