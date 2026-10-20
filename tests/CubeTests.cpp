
#include "Cube.hpp"

#include <cassert>
#include <iostream>

int main() {
    Cube cube;
    // assert(cube.isSolved()) verifies the constructor creates a solved cube.
    assert(cube.isSolved());

    std::cout << "PASS: A newly created cube is solved.\n";
    // Check that each face has a uniform color.
    for (std::size_t face = 0; face < Cube::FaceCount; ++face) {
        const std::size_t start = face * Cube::StickersPerFace;

        const Color expectedColor = cube.getSticker(start);

        for (std::size_t i = 1; i < Cube::StickersPerFace; ++i) {
            assert(cube.getSticker(start + i) == expectedColor);
        }
    }

    std::cout << "PASS: Every face has a uniform color.\n";

    // Currently, we check whether a new cube is solved and whether each face has a uniform color. Let's also check that the array contains exactly nine stickers of each color.
    for (std::size_t colorIndex = 0; colorIndex < 6; ++colorIndex) {
        const Color expectedColor = cube.getSticker(colorIndex * Cube::StickersPerFace);

        std::size_t count = 0;

        for (std::size_t i = 0; i < Cube::StickerCount; ++i) {
            if (cube.getSticker(i) == expectedColor) {
                ++count;
            }
        }

        assert(count == Cube::StickersPerFace);
    }

    std::cout << "PASS: Each face color appears nine times.\n";


    Cube originalCube;
    Cube fourTurnCube;

    fourTurnCube.rotateFrontClockwise();
    fourTurnCube.rotateFrontClockwise();
    fourTurnCube.rotateFrontClockwise();
    fourTurnCube.rotateFrontClockwise();

    assert(fourTurnCube.hasSameState(originalCube));

    std::cout << "PASS: Four Front turns restore every sticker position.\n";

    Cube onceTurnedCube;

    onceTurnedCube.rotateFrontClockwise();

    assert(!onceTurnedCube.hasSameState(originalCube));

    std::cout << "PASS: One Front turn changes the cube state.\n";

    return 0;
}
