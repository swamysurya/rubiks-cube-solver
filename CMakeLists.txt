
# This says that the project requires CMake 3.20 or newer.
# It does not install CMake. It tells CMake which minimum version the project supports.
cmake_minimum_required(VERSION 3.20)


# This declares:
# - RubiksCubeSolver — project name.
# - VERSION 1.0.0 — project version.
# - LANGUAGES CXX — the project uses C++.
project(RubiksCubeSolver
    VERSION 1.0.0
    LANGUAGES CXX
)
# CMAKE_CXX_STANDARD 20	Request C++20.
# CMAKE_CXX_STANDARD_REQUIRED ON	Don't silently fall back to an older C++ standard.
# CMAKE_CXX_EXTENSIONS OFF	Request standard C++ instead of compiler-specific extensions where supported.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add_executable() creates a build target—a named output that CMake knows how to build.
# Here:
# - rubiks_solver is the target name.
# - src/main.cpp contains the program's main() function.
# # - src/Cube.cpp contains the implementation of the Cube class.
# CMake compiles these source files separately and links their object files into the final executable.
# Why include both source files? Because main.cpp uses the Cube class, whose functions are implemented in Cube.cpp.
add_executable(rubiks_solver
    src/main.cpp
    src/Cube.cpp
)

# This creates a second target called cube_tests.
# Notice that it uses tests/CubeTests.cpp instead of src/main.cpp.
# Why? Because the test file has its own main() function. If we included both main.cpp and CubeTests.cpp in one executable, we'd have two main() functions, causing a linking error.
# We include Cube.cpp in both targets because both the application and the test program need the Cube implementation.

add_executable(cube_tests
    tests/CubeTests.cpp
    src/Cube.cpp
)
# Tell the compiler where headers are located. The PRIVATE keyword means that the include directories are used only for this target and not for targets that link to it.
target_include_directories(cube_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(rubiks_solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# This means: if the compiler is GNU GCC, enable these warning options for rubiks_solver.
# - -Wall — enables a useful set of warnings.
# - -Wextra — enables additional warnings.
# - -Wpedantic — warns about certain language extensions outside the selected standard.
# Warnings help catch potential mistakes early. They don't replace tests.

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(rubiks_solver PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# These lines tell CMake's testing system that a test exists.
# - enable_testing() enables testing support.
# - NAME CubeInitialization gives the test a descriptive name.
# - COMMAND cube_tests tells CTest to execute the test program.
# One distinction matters here: cube_tests.exe is the program that performs the checks. CTest is the tool that launches it and reports whether it passed.

enable_testing()


add_test(
    NAME CubeTests
    COMMAND cube_tests
)