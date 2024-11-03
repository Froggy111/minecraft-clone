# minecraft-clone
Funny minecraft clone project

To build:
```
mkdir build
cd build
cmake .. --preset=default
cmake --build default
```

To get intellisense to work with C++20 modules:
Use clangd LSP instead of C/C++ IntelliSense from Microsoft
Follow the instructions to build clangd from this repo: https://github.com/ChuanqiXu9/clangd-for-modules
In ${PROJECT_ROOT}.vscode/settings.json, set:
```
{
  "clangd.arguments": ["--experimental-modules-support"],
  "clangd.path": "path/to/clangd-for-modules"
}
```
In ${PROJECT_ROOT}.clangd:
```
CompileFlags:
  Add:
    - -std=c++23
    - -fmodules
    - -Wall
    - -Wextra
  CompilationDatabase: ./build/debug # change this to whatever build profile you are using
```


TODO:
Game engine
- Renderer
- Entities
  - Static entities
  - Dynamic entities
The actual game