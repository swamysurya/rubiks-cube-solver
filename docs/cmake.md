# CMake & Build System — Learning Notes

## 1. What is CMake?
CMake is a **build-system generator**. It reads `CMakeLists.txt` and generates native build instructions for specific build tools (such as MinGW Makefiles, Ninja, or Visual Studio).

CMake **does not** compile C++ code directly. It coordinates the compiler (`g++`/`c++`) and build tool (`mingw32-make`).

---

## 2. What to Do BEFORE Setting Up CMake (Prerequisites)

Before writing `CMakeLists.txt` or configuring CMake, four essential preparatory steps must be completed:

### 1. Install & Verify Toolchain
Verify that your terminal can run the C++ compiler, build tool, and CMake:
```powershell
g++ --version            # Must support C++20
mingw32-make --version   # Build tool
cmake --version          # CMake 3.20 or newer
```
Ensure their directories are included in your system `PATH`.

### 2. Define Project Requirements
Decide on project specifications:
- Language standard: **C++20**
- Application scope: Command-line interface with automated test suite
- *(Documented in `docs/requirements.md`)*

### 3. Establish Project Directory Structure
Create the standard folder layout so CMake knows where files belong:
```text
rubiks-cube-solver/
├── include/     # Header files (.hpp)
├── src/         # Implementation files (.cpp) and main.cpp
├── tests/       # Unit test files (.cpp)
└── docs/        # Documentation and notes
```

### 4. Initialize Git and Set Up `.gitignore`
Initialize version control and tell Git never to track compiled files or the build directory:
```text
# Windows executables
*.exe

# CMake build directory
build/
```

---

## 3. Deep Dive into `CMakeLists.txt`

```cmake
# Tells CMake: "This project requires at least CMake version 3.20. The project name is RubiksCubeSolver, version 1.0.0, and it uses C++ (CXX)."
# - cmake_minimum_required tells CMake which minimum version the project supports.
# - project() declares the project name, version, and language.
cmake_minimum_required(VERSION 3.20)

project(RubiksCubeSolver
    VERSION 1.0.0
    LANGUAGES CXX
)

# Tells CMake: "Compile everything using standard ISO C++20. If the compiler doesn't support C++20, stop with an error instead of quietly compiling with an older standard."
# - CMAKE_CXX_STANDARD 20: Request C++20.
# - CMAKE_CXX_STANDARD_REQUIRED ON: Don't silently fall back to an older C++ standard.
# - CMAKE_CXX_EXTENSIONS OFF: Request standard C++ instead of compiler-specific extensions.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_executable() creates a build target—a named output that CMake knows how to build.
# Target 1: rubiks_solver (main application)
# - src/main.cpp contains the application entry point main().
# - src/Cube.cpp contains the Cube class implementation.
add_executable(rubiks_solver
    src/main.cpp
    src/Cube.cpp
)

# Target 2: cube_tests (automated unit test runner)
# - tests/CubeTests.cpp has its own main() function to test Cube logic in isolation.
# - Both targets include src/Cube.cpp because both need the Cube implementation.
add_executable(cube_tests
    tests/CubeTests.cpp
    src/Cube.cpp
)

# Tells CMake: "When #include "Cube.hpp" appears in the source files, look inside the include/ directory to find it."
# - PRIVATE means these include paths apply only to these specific targets.
target_include_directories(cube_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(rubiks_solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tells CMake: "If we are using the GNU GCC compiler (MinGW), turn on extra warnings (-Wall -Wextra -Wpedantic) to help us catch mistakes before they turn into bugs."
# - -Wall: enables a useful set of warnings.
# - -Wextra: enables additional warnings.
# - -Wpedantic: warns about language extensions outside standard C++20.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(rubiks_solver PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Tells CMake: "Enable testing support and register cube_tests.exe under the test name CubeTests. When someone runs ctest, run this executable and report if it passed or failed."
# - enable_testing() enables testing support in CMake.
# - add_test() registers the cube_tests executable under the test name CubeTests for CTest.
enable_testing()

add_test(
    NAME CubeTests
    COMMAND cube_tests
)
```

---

## 4. Why Compiler Warnings Matter (`-Wall -Wextra -Wpedantic`)
- `-Wall`: Enables a broad set of useful warnings (uninitialized variables, unused variables, etc.).
- `-Wextra`: Enables additional checks (signed/unsigned comparisons, missing return statements).
- `-Wpedantic`: Warns about non-standard language extensions outside pure ISO C++20.
- Warnings help catch bugs early during compilation rather than debugging unexpected crashes at runtime.

---

## 5. Why Do We Have Two Executable Targets?
Our project builds two separate programs:
1. `rubiks_solver` (`src/main.cpp` + `src/Cube.cpp`): The interactive application users run.
2. `cube_tests` (`tests/CubeTests.cpp` + `src/Cube.cpp`): Automated test runner.

**Why separate them?**  
Both `main.cpp` and `CubeTests.cpp` contain an `int main()` function. If compiled into one executable, the linker throws a duplicate symbol error. Splitting them into two targets allows testing the `Cube` logic in isolation without running the CLI.

---

## 6. What to Do AFTER Writing `CMakeLists.txt` (The 5-Step Lifecycle)

```
[ 1. Configure ]  ──>  [ 2. Build ]  ──>  [ 3. Test ]  ──>  [ 4. Run ]  ──>  [ 5. Commit ]
 cmake -B build        cmake --build       ctest             .\build\...       git commit
```

### Step 1: Configure the Project
Reads `CMakeLists.txt`, creates the `build/` directory, and generates native Makefiles:
```powershell
cmake -B build -G "MinGW Makefiles"
```
*(Does not compile code yet).*

### Step 2: Build / Compile
Compiles the C++ source files into `.exe` binaries inside `build/`:
```powershell
cmake --build build
```

### Step 3: Run Automated Tests
Verifies code correctness before running the app:
```powershell
ctest --test-dir build --output-on-failure
```
*(Or directly: `.\build\cube_tests.exe`)*

### Step 4: Run the Main Program
Executes the main application:
```powershell
.\build\rubiks_solver.exe
```

### Step 5: Save & Commit to Git
Saves verified configuration and code to version control:
```powershell
git status
git add CMakeLists.txt
git commit -m "build: configure project with CMake"
git push origin main
```

---

## 7. Build Commands Quick Reference

| Action | Command |
| :--- | :--- |
| **Configure from scratch** | `cmake -B build -G "MinGW Makefiles"` |
| **Compile all targets** | `cmake --build build` |
| **Run tests via CTest** | `ctest --test-dir build --output-on-failure` |
| **Run tests directly** | `.\build\cube_tests.exe` |
| **Run application** | `.\build\rubiks_solver.exe` |
| **Clean reconfigure** | `Remove-Item -Recurse -Force build`<br>`cmake -B build -G "MinGW Makefiles"`<br>`cmake --build build` |

---

## 8. Windows & VS Code Environment Tips
- **PATH Inheritance**: When CMake or MinGW is installed, the installer updates system PATH. However, existing VS Code terminal windows retain the old environment. You must either restart VS Code or refresh PATH in PowerShell:
  ```powershell
  $env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path", "User")
  ```
- **Checking Installed Tools via winget**:
  ```powershell
  winget list --id Kitware.CMake
  ```

---

## 9. Incremental Compilation: Why Subsequent Builds Are Faster

### 9.1 The Observation
The first time you run `cmake --build build`, every `.cpp` file is compiled and linked. On subsequent runs — especially when only one or two files have changed — the build finishes dramatically faster.

### 9.2 How It Works: Timestamp-Based Dependency Tracking
The build tool (MinGW Make or Ninja) maintains an internal **Dependency Graph** mapping each source file to its compiled object file. Before compiling any file, it compares file modification timestamps:

```text
Is  LastModified(CubeTests.cpp)  >  LastModified(CubeTests.cpp.obj) ?
      ├── YES ──► Source is newer than its object file. Recompile it.

Is  LastModified(main.cpp)       >  LastModified(main.cpp.obj) ?
      └── NO  ──► Object file is up to date. Skip entirely.
```

If a source file has not been modified since its `.obj` was last generated, recompiling it would produce a byte-for-byte identical result. Skipping it saves CPU time.

### 9.3 Proof from Build Logs

#### Full Build (All files modified or first build):
```text
[ 12%] Building CXX object CMakeFiles/rubiks_solver.dir/src/main.cpp.obj
[ 25%] Building CXX object CMakeFiles/rubiks_solver.dir/src/Cube.cpp.obj
[ 37%] Building CXX object CMakeFiles/rubiks_solver.dir/src/Notation.cpp.obj
[ 50%] Linking CXX executable rubiks_solver.exe
[ 62%] Building CXX object CMakeFiles/cube_tests.dir/tests/CubeTests.cpp.obj
[ 75%] Building CXX object CMakeFiles/cube_tests.dir/src/Cube.cpp.obj
[ 87%] Building CXX object CMakeFiles/cube_tests.dir/src/Notation.cpp.obj
[100%] Linking CXX executable cube_tests.exe
```
*6 compilations + 2 link steps.*

#### Incremental Build (Only `CubeTests.cpp` modified):
```text
[ 50%] Built target rubiks_solver          <── SKIPPED! (already up to date)
[ 62%] Building CXX object CMakeFiles/cube_tests.dir/tests/CubeTests.cpp.obj
[ 75%] Linking CXX executable cube_tests.exe
[100%] Built target cube_tests
```
*Only 1 compilation + 1 link step. The entire `rubiks_solver` target was skipped.*

### 9.4 Why Header Changes Are Slower Than Source Changes
The build system also tracks `#include` dependencies:
- **Editing a `.cpp` file** (e.g. `tests/CubeTests.cpp`): Only that single `.obj` is recompiled.
- **Editing a `.hpp` file** (e.g. `include/Cube.hpp`): Because `Cube.hpp` is `#include`-d by `Cube.cpp`, `main.cpp`, and `CubeTests.cpp` (transitive inclusion), the build system marks all three as stale and recompiles all of them.

This is why keeping headers minimal and stable is an important C++ design discipline.

### 9.5 OS-Level RAM Caching
On the first build, the operating system loads the compiler binary (`g++.exe`), standard library headers (`<iostream>`, `<vector>`, `<string_view>`), and project files from disk into RAM. On subsequent builds, these files remain in the OS file cache (hot memory), reducing disk I/O latency to near zero.

### 9.6 Summary

| Build Type | What Gets Compiled | When to Use |
| :--- | :--- | :--- |
| **Clean Build** (`cmake --build build --clean-first`) | Every file in the project | After major toolchain changes or suspected build corruption |
| **Incremental Build** (`cmake --build build`) | **Only the files modified** since the last build | Normal development workflow (default) |
