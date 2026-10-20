
cmake_minimum_required(VERSION 3.20)

project(RubiksCubeSolver
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rubiks_solver
    src/main.cpp
    src/Cube.cpp
)

add_executable(cube_tests
    tests/CubeTests.cpp
    src/Cube.cpp
)

target_include_directories(cube_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories(rubiks_solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(rubiks_solver PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

enable_testing()

add_test(
    NAME CubeInitialization
    COMMAND cube_tests
)
