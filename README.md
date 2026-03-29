# cocos2dx317_qipai_project

基于 **cocos2d-x 3.17.2** 的纸牌关卡项目（C++）。

## 运行环境（macOS）

- Xcode（命令行工具可用）
- CMake（建议 >= 3.20）
- Python 3

## 从 0 到可运行

1. 克隆仓库

```bash
git clone git@github.com:iTheSen/chessNcard_game.git
cd chessNcard_game
```

2. 初始化 `cocos2d-x` 子模块（只需要这个顶层子模块）

```bash
git submodule update --init cocos2d
```

3. 准备 cocos2d 外部依赖（Python3 脚本）

```bash
python3 scripts/setup_cocos2d_deps.py
```

这一步会做三件事：
- 下载 `cocos2d-x-3rd-party-libs-bin` 依赖包
- 解压到 `cocos2d/external`
- 自动应用 macOS/Xcode 兼容补丁

4. 配置并编译（x86_64）

```bash
cmake -S . -B build-cmake-x86-vscode -G Xcode -DCMAKE_OSX_ARCHITECTURES=x86_64
cmake --build build-cmake-x86-vscode --config Debug --target QipaiGame -j 10
```

5. 启动

```bash
open build-cmake-x86-vscode/bin/QipaiGame/Debug/QipaiGame.app
```

## VSCode（CMake Tools）启动

1. `Configure` 先执行一次  
2. `Build Target` 选 `QipaiGame`（不要选 `ALL_BUILD`）  
3. `Launch Target` 选 `QipaiGame`  
4. 点击运行/调试

## 更新代码后建议

```bash
git pull
git submodule update --init cocos2d
python3 scripts/setup_cocos2d_deps.py
cmake --build build-cmake-x86-vscode --config Debug --target QipaiGame -j 10
```

