# Visual Studio Code Workspace Directory Generator

This project is to create a program that references VSCode workspace file and creates a workspace directory.

## How to build

This project can build by CMake.

```shell
git clone https://github.com/Kamioda/WorkspaceDirectoryGenerator.git
cd WorkspaceDirectoryGenerator
git submodule init
git submodule update
cmake -S . -B build
cmake --build build
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
