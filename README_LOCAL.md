# Local Cocos2d-x 3.17 Project

## Open This Directory
- /Users/dengyingsen/Desktop/git_clone/cocos2dx317_qipai_project

## Build (x86_64 / Rosetta)
```bash
cmake -S . -B build-x86_64 -G Xcode -DCMAKE_OSX_ARCHITECTURES=x86_64 -DCMAKE_OSX_DEPLOYMENT_TARGET=26.0
cmake --build build-x86_64 --config Debug --target QipaiGame --parallel 8
```

## Run
```bash
open build-x86_64/bin/QipaiGame/Debug/QipaiGame.app
```
