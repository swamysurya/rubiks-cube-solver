


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


## C++ — First Cube Class Declaration

- A header file (`.hpp`) can declare types and class interfaces.
- A source file (`.cpp`) can provide function implementations.
- Header guards prevent repeated inclusion of a header within a translation unit.
- `enum class` provides scoped enumeration values.
- `std::array<T, N>` stores a fixed number of elements of type `T`.
- `static constexpr` defines compile-time constants associated with a class.
- `std::size_t` is commonly used for collection sizes and indexing.
- `private` encapsulates internal state so callers cannot modify it directly.
- A class declaration defines its structure; initialization behavior still needs to be implemented.


### Constructors
- A constructor initializes an object when it is created.
- A constructor has the same name as its class and has no return type.
- A constructor can be declared in a header and implemented in a source file.

### Cube Constructor Implementation
- `ClassName::functionName()` defines a class member outside its class declaration.
- Nested loops can iterate over faces and stickers.
- `std::array` supports indexed access using `operator[]`.
- A two-dimensional logical position can be mapped to a flat array using:
  `flatIndex = rowIndex * rowWidth + columnIndex`.
- CMake must list the source files required to build an executable.


### Displaying a Cube Face as a Grid
- Nested loops can represent rows and columns in a 2D grid.
- A flat array can represent a 2D structure using row-major indexing.
- For a 3x3 face, the local index is `row * 3 + col`.
- The global index is `face * 9 + row * 3 + col`.
- A readable state display helps debug future cube rotations.
- std::boolalpha : it will print 'true' or 'false' in cout instead 1 or 0


### State Inspection and Validation
- Public getters allow controlled observation of private state.
- `std::array::at()` checks bounds and throws `std::out_of_range` for an invalid index.
- A Boolean function can report whether a condition holds.
- Returning `false` early avoids unnecessary checks after a failure is found.
- A solved-state check is not the same as complete cube-state validation.


### CTest — Registering Automated Tests
- CTest is CMake's test-running tool.
- `enable_testing()` enables testing support for the project.
- `add_test()` registers a test with a name and command.
- `ctest --test-dir build` runs registered tests from the build directory.
- `--output-on-failure` displays output for failed tests.
- Automated tests help detect regressions after code changes.


---------------------------
# CMAKE


# Rubik's Cube Solver — Learning Notes

## 1. What is CMake?

CMake is a build-system generator. It reads `CMakeLists.txt` and generates build instructions for tools such as MinGW Makefiles.

CMake does not directly compile C++ code. It configures the build process and coordinates the compiler and build tool.

### Build workflow

1. Write C++ source files.
2. Configure the project using CMake.
3. Generate build instructions.
4. Compile and link the source files.
5. Run the generated executable.

## 2. What is `CMakeLists.txt`?

`CMakeLists.txt` is the configuration file that describes how our C++ project should be built.

### Important commands

**Minimum CMake version**

```cmake
cmake_minimum_required(VERSION 3.20)
```

Declares the minimum CMake version required by the project.

**Project declaration**

```cmake
project(RubiksCubeSolver
    VERSION 1.0.0
    LANGUAGES CXX
)
```

- `RubiksCubeSolver`: project name.
- `VERSION 1.0.0`: project version.
- `LANGUAGES CXX`: project uses C++.

**C++ standard**

```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

- Requests C++20.
- Requires the requested standard.
- Requests standard C++ instead of compiler-specific extensions.

**Create an executable**

```cmake
add_executable(rubiks_solver
    src/main.cpp
    src/Cube.cpp
)
```

- `add_executable()` creates a build target.
- `rubiks_solver` is the target name.
- `main.cpp` contains the application entry point.
- `Cube.cpp` contains the Cube class implementation.

CMake compiles the source files and links them into an executable.

**Configure header search directories**

```cmake
target_include_directories(rubiks_solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

- Tells the compiler where to find header files.
- `PRIVATE` applies the directory to this target.
- `CMAKE_CURRENT_SOURCE_DIR` refers to the directory containing the top-level `CMakeLists.txt`.

**Compiler warnings**

```cmake
target_compile_options(rubiks_solver PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
```

- `-Wall`: enables a useful set of warnings.
- `-Wextra`: enables additional warnings.
- `-Wpedantic`: warns about certain non-standard language extensions.

These options help identify potential mistakes during compilation.

## 3. Why do we have two executable targets?

Our project has two independent programs.

### Application target

```cmake
add_executable(rubiks_solver
    src/main.cpp
    src/Cube.cpp
)
```

Purpose: run the actual Rubik's Cube Solver application.

### Test target

```cmake
add_executable(cube_tests
    tests/CubeTests.cpp
    src/Cube.cpp
)
```

Purpose: execute automated checks against the Cube class.

Both programs need `Cube.cpp` because both use the Cube implementation.

They have separate `main()` functions, so they must be built as separate executables.

## 4. What is `tests/CubeTests.cpp`?

`CubeTests.cpp` contains code that checks whether the Cube class behaves as expected.

Testing helps us detect mistakes without manually inspecting output every time.

### Include required files

```cpp
#include "Cube.hpp"
#include <cassert>
#include <iostream>
```

- `Cube.hpp`: declares the Cube class.
- `<cassert>`: provides the `assert()` macro.
- `<iostream>`: provides `std::cout`.

### Create a Cube object

```cpp
Cube cube;
```

This creates a Cube object. Its constructor initializes the sticker colors.

### Test the solved state

```cpp
assert(cube.isSolved());
```

`assert()` checks a condition.

- If the condition is true, execution continues.
- If the condition is false, the assertion reports a failure and normally terminates the program.

Assertions are disabled when `NDEBUG` is defined, so a more robust test setup may be needed for release builds.

### Loop through the faces

```cpp
for (std::size_t face = 0;
     face < Cube::FaceCount;
     ++face) {
    // Test the face.
}
```

This visits all six faces, with indices from 0 to 5.

### Calculate a face's starting index

```cpp
const std::size_t start =
    face * Cube::StickersPerFace;
```

Each face has nine stickers.

| Face index | Starting sticker index |
|---:|---:|
| 0 | 0 |
| 1 | 9 |
| 2 | 18 |
| 3 | 27 |
| 4 | 36 |
| 5 | 45 |

### Compare sticker colors

```cpp
const Color expectedColor = cube.getSticker(start);

assert(cube.getSticker(start + i) == expectedColor);
```

The first sticker on the face becomes the expected color. The remaining eight stickers are compared against it.

If a sticker has a different color, the assertion fails.

This checks that every face is uniform, but it does not prove that an arbitrary cube arrangement is physically solvable.

### Successful test output

```cpp
std::cout << "PASS: Every face has a uniform color.\n";
return 0;
```

The message is printed if execution reaches this line. Returning `0` indicates successful program execution.

## 5. What is CTest?

CTest is the test-running tool provided by CMake.

**Enable testing**

```cmake
enable_testing()
```

Enables testing support for the project.

**Register a test**

```cmake
add_test(
    NAME CubeInitialization
    COMMAND cube_tests
)
```

- `NAME`: gives the test a descriptive name.
- `COMMAND`: specifies the executable CTest should run.

The test executable performs the checks; CTest launches it and reports the result.

## 6. Important terminal commands

**Configure the project**

```powershell
cmake -S . -B build
```

- `-S .`: use the current directory as the source directory.
- `-B build`: put generated build files in `build/`.

**Build all configured targets**

```powershell
cmake --build build
```

**Run the test executable directly**

```powershell
.\build\cube_tests.exe
```

**Run registered tests**

```powershell
ctest --test-dir build --output-on-failure
```

**Inspect Git changes**

```powershell
git status
git diff
```

**Commit and push changes**

```powershell
git add CMakeLists.txt tests/CubeTests.cpp docs/learning-notes.md
git commit -m "test: add cube initialization checks"
git push
```

## 7. Key concepts to remember

1. CMake describes and configures the build process.
2. `CMakeLists.txt` defines targets, source files, include paths, and compiler options.
3. A build target is a named output CMake knows how to build.
4. Application code and test code should be separate.
5. Tests check expected behavior, not just whether code compiles.
6. CTest runs registered tests and reports their results.
7. Small, automated tests help prevent regressions as the project grows.