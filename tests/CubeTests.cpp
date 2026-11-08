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

  // =========================================================================
  // 6. Down Turn (D) Tests
  // =========================================================================

  // Test 12: One Down turn alters the cube state (D != I)
  Cube onceTurnedDown;
  onceTurnedDown.rotateDownClockwise();
  assert(!onceTurnedDown.hasSameState(originalCube));
  std::cout << "PASS: One Down turn changes the cube state.\n";

  // Test 13: Four consecutive Down turns restore the original state (D^4 = I)
  Cube fourTurnDown;
  fourTurnDown.rotateDownClockwise();
  fourTurnDown.rotateDownClockwise();
  fourTurnDown.rotateDownClockwise();
  fourTurnDown.rotateDownClockwise();
  assert(fourTurnDown.hasSameState(originalCube));
  std::cout << "PASS: Four Down turns restore every sticker position.\n";

  // =========================================================================
  // 7. Back Turn (B) Tests & C++20 operator== / operator!=
  // =========================================================================

  // Test 14: One Back turn alters the cube state (B != I) using C++20
  // operator!=
  Cube onceTurnedBack;
  onceTurnedBack.rotateBackClockwise();
  assert(onceTurnedBack != originalCube);
  std::cout << "PASS: One Back turn changes the cube state (verified with "
               "operator!=).\n";

  // Test 15: Four consecutive Back turns restore the original state (B^4 = I)
  // using operator==
  Cube fourTurnBack;
  fourTurnBack.rotateBackClockwise();
  fourTurnBack.rotateBackClockwise();
  fourTurnBack.rotateBackClockwise();
  fourTurnBack.rotateBackClockwise();
  assert(fourTurnBack == originalCube);
  std::cout << "PASS: Four Back turns restore every sticker position (verified "
               "with operator==).\n";

  // =========================================================================
  // 8. Counter-Clockwise (Prime) Rotations: Up Prime (U') Tests
  // =========================================================================

  // Test 16: Up Prime alters state (U' != I) and cancels Up (U * U' = I)
  Cube testU;
  testU.rotateUpClockwise();
  testU.rotateUpCounterClockwise();
  assert(testU == originalCube);

  Cube onceTurnedUPrime;
  onceTurnedUPrime.rotateUpCounterClockwise();
  assert(onceTurnedUPrime != originalCube);
  std::cout << "PASS: Up Prime (U') changes state and cancels U (U * U' = I).\n";

  // Test 17: Four consecutive Up Prime turns restore original state ((U')^4 = I)
  Cube fourTurnUPrime;
  fourTurnUPrime.rotateUpCounterClockwise();
  fourTurnUPrime.rotateUpCounterClockwise();
  fourTurnUPrime.rotateUpCounterClockwise();
  fourTurnUPrime.rotateUpCounterClockwise();
  assert(fourTurnUPrime == originalCube);
  std::cout << "PASS: Four Up Prime turns restore every sticker position ((U')^4 = I).\n";

  // Test 18: Reverse cancellation order (U' * U = I)
  Cube reverseCancelU;
  reverseCancelU.rotateUpCounterClockwise();
  reverseCancelU.rotateUpClockwise();
  assert(reverseCancelU == originalCube);
  std::cout << "PASS: Reverse cancellation verified (U' * U = I).\n";

  return 0;
}
