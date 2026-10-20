


### 2. Compilation Command

```powershell
g++ -std=c++20 -Wall -Wextra -Wpedantic src/main.cpp -o rubiks_solver.exe
```

- `g++`: invokes the C++ compiler.
- `-std=c++20`: selects the C++20 language standard.
- `-Wall`: enables a broad set of useful warnings.
- `-Wextra`: enables additional warnings.
- `-Wpedantic`: warns about certain non-standard extensions.
- `src/main.cpp`: specifies the source file.
- `-o rubiks_solver.exe`: names the output executable.

### 3. Why Compiler Warnings Matter

Warnings can identify suspicious or potentially incorrect code.
They do not guarantee that a program is bug-free.

We should understand each warning and fix genuine issues
rather than suppress warnings without investigation.


### git commands
```powershell
git status
```
```powershell
Get-Content src/main.cpp
```
```powershell
Test-Path docs/learning-notes.md
```
```powershell
git diff --cached
```
```powershell
git diff
```
```powershell
git ls-files
```


### Terminal commands

```powershell
Get-ChildItem -Recurse -File
winget install Kitware.CMake
```

### git commit msg formats
```
<type>: <short description>
```

Common types:
Type	When to use	Example
feat	dNew functionality	feat: add cube rotation logic
fix	Bug fix	fix: correct cube move validation
docs	Documentation changes	docs: add project requirements
build	Build system changes	build: configure CMake
test	Adding or updating tests	test: add cube initialization tests
refactor	Restructure code without changing behavior	refactor: simplify cube state representation
chore	Maintenance tasks	chore: add executable to gitignore

VS Code's terminal inherits environment variables when the VS Code process starts. When you install CMake, the installer may update Windows' PATH, but your already-open VS Code process can keep the old environment. After restarting VS Code, the new terminal inherits the updated PATH, so cmake --version works.

```
$env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")
```

Check whether CMake is installed
```
winget list --id Kitware.CMake
```


CMake lets us describe the project once in a configuration file. It then generates the build instructions needed by the available build tool.
CMakeLists.txt
Project name, source files, C++ standard, compiler options

CMake configure step
Generates native build instructions

Build and run
Compile the program and execute it


cmake -S . -B build -G "MinGW Makefiles"

## CMake — Initial Project Configuration

- CMake is a build-system generator that describes how a project should be built.
- `CMakeLists.txt` defines project configuration and build targets.
- `project()` declares the project and its programming language.
- `add_executable()` defines an executable target and its source files.
- `CMAKE_CXX_STANDARD` requests a C++ language standard.
- `target_compile_options()` applies compiler options to a specific target.
- `cmake -S . -B build` configures the project using the current directory as the source and `build/` as the build directory.
- `cmake --build build` builds the configured targets.
- Generated build files belong in the build directory and should not be committed.

## Cube Representation — Design Decisions

- A standard 3×3×3 Rubik's Cube has six faces and 54 sticker positions.
- `enum class` represents a restricted set of named values, such as sticker colors.
- `std::array` is appropriate when the number of elements is fixed at compile time.
- A class encapsulates data and the operations that work on that data.
- A face-index convention prevents inconsistent indexing across cube operations.
- Row-major indexing stores a 3×3 face as three consecutive rows.
- Architecture documentation records design decisions and helps future contributors understand the project.
- Design and testing should precede complex move and solver implementations.
