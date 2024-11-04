# minecraft-clone
Funny, minimum-compromises minecraft clone project in C++

### Build:
The default profile is debug, check CMakePresets.json for more options
```
mkdir build
cd build
cmake .. --preset=default
cmake --build default
```

### Intellisense:
TLDR: Intellisense with modules is a pain.

The following instructions are to get intellisense working with C++20 modules in VSCode using Clang.

If you want to use MSVC (or visual studio), in which case clangd is not needed, you can upload a seperate set of profile templates and instructions.

To get intellisense to work with C++20 modules (for VSCode, Clang):

Use clangd LSP instead of C/C++ IntelliSense from Microsoft.
Follow the instructions to build clangd from this repo: https://github.com/ChuanqiXu9/clangd-for-modules.
Additionally, build LLVM + Clang from that same repository (to ensure that PCH versions are the same).
Make a copy of CMakeUserPresetsTemplate.json and rename it to CMakeUserPresets.json, and replace clang and clang++ with the path to the built clang and clang++.

In ```${PROJECT_ROOT}.vscode/settings.json```, set:
```
{
  "clangd.arguments": ["--experimental-modules-support"],
  "clangd.path": "path/to/clangd-for-modules"
}
```

In ```${PROJECT_ROOT}/.clangd```:
```
CompileFlags:
  Add:
    - -std=c++23
    - -fmodules
    - -Wall
    - -Wextra
    - -stdlib=libc++
  CompilationDatabase: ./build/debug
```

Inside ```${PROJECT_ROOT}/build```, run: (**make sure** clang and clang++ are in your PATH)
```
cmake .. --preset=user-debug
cmake --build debug
```

After importing a module, the project needs to be recompiled (under the profile where clangd is getting its compilation database from), to regenerate its compilation database, and the clangd server needs to reparse the file (it needs to be saved, or closed and reopened).
To automatically recompile the project on file changes, and to reconfigure cmake on cmake file changes, you can use the file-watcher extension. Add the following to your ```${PROJECT_ROOT}.vscode/settings```:
```
"filewatcher.commands": [
  {
    "match": "\\.(?:cpp|cppm|cxx|ixx|hpp|c|h)",
    "cmd": "cmake --build ${workspaceRoot}/build/debug",
    "event": "onFileChange"
  },
  {
    "match": "\\.(?:cpp|cppm|cxx|ixx|hpp|c|h)",
    "cmd": "cmake --build ${workspaceRoot}/build/debug",
    "event": "onFileCreate",
  },
  {
    "match": "\\.(?:cpp|cppm|cxx|ixx|hpp|c|h)",
    "cmd": "cmake --build ${workspaceRoot}/build/debug",
    "event": "onFileDelete"
  },
  {
    "match": "\\.(?:cpp|cppm|cxx|ixx|hpp|c|h)",
    "cmd": "cmake --build ${workspaceRoot}/build/debug",
    "event": "onFileRename",
  }
]
```
You can use CMakeTools to auto reconfigure cmake on changes to cmake files.

**NOTE**: Only compilers that have support for ```import std;``` can be used for this project! That means no gcc for now sadly D:

### TODO:
Game engine
- Mod loader

Mods
- Base mod (basic libraries, renderer, window)

Make the real game :D