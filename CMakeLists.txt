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
