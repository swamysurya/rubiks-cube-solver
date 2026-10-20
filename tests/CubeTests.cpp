
#include "Cube.hpp"

#include <cassert>
#include <iostream>

int main() {
    Cube cube;
    // assert(cube.isSolved()) verifies the constructor creates a solved cube.
    assert(cube.isSolved());

    std::cout << "PASS: A newly created cube is solved.\n";

    for (std::size_t face = 0; face < Cube::FaceCount; ++face) {
        const std::size_t start = face * Cube::StickersPerFace;

        const Color expectedColor = cube.getSticker(start);

        for (std::size_t i = 1; i < Cube::StickersPerFace; ++i) {
            assert(cube.getSticker(start + i) == expectedColor);
        }
    }

    std::cout << "PASS: Every face has a uniform color.\n";
    return 0;
}
