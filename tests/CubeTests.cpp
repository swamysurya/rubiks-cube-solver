#include "Cube.hpp"
#include <cassert>
#include <iostream>

int main() {
  // =========================================================================
  // 1. Initialization & Invariant Tests
  // =========================================================================

  Cube cube;

  // Test 1: A freshly created cube must be solved
  assert(cube.isSolved());
  std::cout << "PASS: A newly created cube is solved.\n";

  // Test 2: Check that each face has a uniform color
  for (std::size_t face = 0; face < Cube::FaceCount; ++face) {
    const std::size_t start = face * Cube::StickersPerFace;
    const Color expectedColor = cube.getSticker(start);

    for (std::size_t i = 1; i < Cube::StickersPerFace; ++i) {
      assert(cube.getSticker(start + i) == expectedColor);
    }
  }
  std::cout << "PASS: Every face has a uniform color.\n";

  // Test 3: Check that the cube contains exactly 9 stickers of each of the 6
  // colors
  for (std::size_t colorIndex = 0; colorIndex < 6; ++colorIndex) {
    const Color expectedColor =
        cube.getSticker(colorIndex * Cube::StickersPerFace);
    std::size_t count = 0;

    for (std::size_t i = 0; i < Cube::StickerCount; ++i) {
      if (cube.getSticker(i) == expectedColor) {
        ++count;
      }
    }
    assert(count == Cube::StickersPerFace); // Exactly 9 stickers per color
  }
  std::cout << "PASS: Each face color appears nine times.\n";

  // =========================================================================
  // 2. Front Turn (F) Tests
  // =========================================================================

  Cube originalCube;

  // Test 4: One Front turn alters the cube state (F != I)
  Cube onceTurnedFront;
  onceTurnedFront.rotateFrontClockwise();
  assert(!onceTurnedFront.hasSameState(originalCube));
  std::cout << "PASS: One Front turn changes the cube state.\n";

  // Test 5: Four consecutive Front turns restore the original state (F^4 =
  // I)
  Cube fourTurnFront;
  fourTurnFront.rotateFrontClockwise();
  fourTurnFront.rotateFrontClockwise();
  fourTurnFront.rotateFrontClockwise();
  fourTurnFront.rotateFrontClockwise();
  assert(fourTurnFront.hasSameState(originalCube));
  std::cout << "PASS: Four Front turns restore every sticker position.\n";

  // =========================================================================
  // 3. Up Turn (U) Tests
  // =========================================================================

  // Test 6: One Up turn alters the cube state (U != I)
  Cube onceTurnedUp;
  onceTurnedUp.rotateUpClockwise();
  assert(!onceTurnedUp.hasSameState(originalCube));
  std::cout << "PASS: One Up turn changes the cube state.\n";

  // Test 7: Four consecutive Up turns restore the original state (U^4 = I)
  Cube fourTurnUp;
  fourTurnUp.rotateUpClockwise();
  fourTurnUp.rotateUpClockwise();
  fourTurnUp.rotateUpClockwise();
  fourTurnUp.rotateUpClockwise();
  assert(fourTurnUp.hasSameState(originalCube));
  std::cout << "PASS: Four Up turns restore every sticker position.\n";

  // =========================================================================
  // 4. Right Turn (R) Tests
  // =========================================================================

  // Test 8: One Right turn alters the cube state (R != I)
  Cube onceTurnedRight;
  onceTurnedRight.rotateRightClockwise();
  assert(!onceTurnedRight.hasSameState(originalCube));
  std::cout << "PASS: One Right turn changes the cube state.\n";

  // Test 9: Four consecutive Right turns restore the original state (R^4 = I)
  Cube fourTurnRight;
  fourTurnRight.rotateRightClockwise();
  fourTurnRight.rotateRightClockwise();
  fourTurnRight.rotateRightClockwise();
  fourTurnRight.rotateRightClockwise();
  assert(fourTurnRight.hasSameState(originalCube));
  std::cout << "PASS: Four Right turns restore every sticker position.\n";

  // =========================================================================
  // 5. Left Turn (L) Tests
  // =========================================================================

  // Test 10: One Left turn alters the cube state (L != I)
  Cube onceTurnedLeft;
  onceTurnedLeft.rotateLeftClockwise();
  assert(!onceTurnedLeft.hasSameState(originalCube));
  std::cout << "PASS: One Left turn changes the cube state.\n";

  // Test 11: Four consecutive Left turns restore the original state (L^4 = I)
  Cube fourTurnLeft;
  fourTurnLeft.rotateLeftClockwise();
  fourTurnLeft.rotateLeftClockwise();
  fourTurnLeft.rotateLeftClockwise();
  fourTurnLeft.rotateLeftClockwise();
  assert(fourTurnLeft.hasSameState(originalCube));
  std::cout << "PASS: Four Left turns restore every sticker position.\n";

  return 0;
}
