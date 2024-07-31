# Visual Studio Code Workspace Directory Generator

This project is to create a program that references VSCode workspace file and creates a workspace directory.

## How to build

### Common

```shell
git clone https://github.com/Kamioda/WorkspaceDirectoryGenerator.git
cd WorkspaceDirectoryGenerator
git submodule init
git submodule update
```

### CMake

```shell
cmake -S . -B build
cmake --build build
```

### Make

```shell
make
```

If gcc(g++) is not installed in your computer, this command cannot run.

### GCC

```shell
g++ -o wdg Main.cpp -std=c++20 -I ./3rdparty/json/include Main.cpp
```

### Clang

```shell
clang++ -o wdg Main.cpp -std=c++20 -I ./3rdparty/json/include Main.cpp
```

### Visual Studio Compiler

```shell
cl /EHsc /std:c++20 /Fe:wdg.exe /I ./3rdparty/json/include Main.cpp
```

## How to use

Please input this command in your terminal.

```shell
wdg --file <VSCode Workspace file path>
```

or

```shell
wdg -f <VSCode Workspace file path>
```

Only one workspace file can be specified on the command line per process.

## Example of a workspace file that runs this program

```json
{
    "folders": [
        {
            "name": "Project A",
            "path": "./project_a"
        },
        {
            "name": "Project B",
            "path": "./project_b"
        }
    ]
}
```

If none of the patterns listed below apply, this program will do nothing or throw an error.

- Command line is incorrectly specified
- Reserved workspace file is not found
- Workspace file is invalid
- Key named "folder" is not found
- Type of key named "folder" is not an array
- No object that contains the key named "path" in the array of keys named "folder"
- All directory exists
