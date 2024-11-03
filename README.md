# minecraft-clone
Funny minecraft clone project

### Build:
The default profile is debug, check CMakePresets.json for more options
```
mkdir build
cd build
cmake .. --preset=default
cmake --build default
```

### Intellisense
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
In ${PROJECT_ROOT}/clangd:
```
CompileFlags:
  Add:
    - -std=c++23
    - -fmodules
    - -Wall
    - -Wextra
  CompilationDatabase: ./build/clangd
```
Inside ${PROJECT_ROOT}/build, run: (**make sure** clang and clang++ are in your PATH)
```
cmake .. --preset=clangd
```
You may need to build the project with preset clangd:
```
cmake --build clangd
```
If you get an error from clangd: PCH file uses an older PCH format that is no longer supported
You need to build the same version of clang as in the clangd-for-modules repo. Follow clang build instructions in the llvm project.
Make a copy of CMakeUserPresetsTemplate.json and rename it to CMakeUserPresets.json, and replace the clang and clang++ with the path to the built clang and clang++.
Append the preset names with "user-" (without the quotes) when generating CMake configuration.
After importing a module, the project needs to be recompiled (under the clangd profile) and the clangd language server restarted (quite annoying, but oh well).

NOTE: Clang or MSVC (untested) **MUST** be used for this project! Until gcc supports ```import std;``` at least.


### TODO:
Game engine
- Renderer
- Entities
  - Static entities
  - Dynamic entities
The actual game