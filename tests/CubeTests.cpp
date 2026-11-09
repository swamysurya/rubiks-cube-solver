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
  // make up face clock wise counter clockwise make cube back to originl state
  Cube testU;
  testU.rotateUpClockwise();
  testU.rotateUpCounterClockwise();
  assert(testU == originalCube);

  Cube onceTurnedUPrime;
  onceTurnedUPrime.rotateUpCounterClockwise();
  assert(onceTurnedUPrime != originalCube);
  std::cout
      << "PASS: Up Prime (U') changes state and cancels U (U * U' = I).\n";

  // Test 17: Four consecutive Up Prime turns restore original state ((U')^4 =
  // I)
  Cube fourTurnUPrime;
  fourTurnUPrime.rotateUpCounterClockwise();
  fourTurnUPrime.rotateUpCounterClockwise();
  fourTurnUPrime.rotateUpCounterClockwise();
  fourTurnUPrime.rotateUpCounterClockwise();
  assert(fourTurnUPrime == originalCube);
  std::cout << "PASS: Four Up Prime turns restore every sticker position "
               "((U')^4 = I).\n";

  // Test 18: Reverse cancellation order (U' * U = I)
  Cube reverseCancelU;
  reverseCancelU.rotateUpCounterClockwise();
  reverseCancelU.rotateUpClockwise();
  assert(reverseCancelU == originalCube);
  std::cout << "PASS: Reverse cancellation verified (U' * U = I).\n";

  // Test 19: Down Prime alters state (D' != I) and cancels Down (D * D' = I)
  Cube testD;
  testD.rotateDownClockwise();
  testD.rotateDownCounterClockwise();
  assert(testD == originalCube);

  Cube onceTurnedDPrime;
  onceTurnedDPrime.rotateDownCounterClockwise();
  assert(onceTurnedDPrime != originalCube);
  std::cout
      << "PASS: Down Prime (D') changes state and cancels D (D * D' = I).\n";

  // Test 20: Four consecutive Down Prime turns restore original state ((D')^4 =
  // I)
  Cube fourTurnDPrime;
  fourTurnDPrime.rotateDownCounterClockwise();
  fourTurnDPrime.rotateDownCounterClockwise();
  fourTurnDPrime.rotateDownCounterClockwise();
  fourTurnDPrime.rotateDownCounterClockwise();
  assert(fourTurnDPrime == originalCube);
  std::cout << "PASS: Four Down Prime turns restore every sticker position "
               "((D')^4 = I).\n";

  // Test 21: Reverse cancellation order (D' * D = I)
  Cube reverseCancelD;
  reverseCancelD.rotateDownCounterClockwise();
  reverseCancelD.rotateDownClockwise();
  assert(reverseCancelD == originalCube);
  std::cout << "PASS: Reverse cancellation verified (D' * D = I).\n";

  // Test 22: Front Prime alters state (F' != I) and cancels Front (F * F' = I)
  Cube testF;
  testF.rotateFrontClockwise();
  testF.rotateFrontCounterClockwise();
  assert(testF == originalCube);

  Cube onceTurnedFPrime;
  onceTurnedFPrime.rotateFrontCounterClockwise();
  assert(onceTurnedFPrime != originalCube);
  std::cout
      << "PASS: Front Prime (F') changes state and cancels F (F * F' = I).\n";

  // Test 23: Four consecutive Front Prime turns restore original state ((F')^4
  // = I)
  Cube fourTurnFPrime;
  fourTurnFPrime.rotateFrontCounterClockwise();
  fourTurnFPrime.rotateFrontCounterClockwise();
  fourTurnFPrime.rotateFrontCounterClockwise();
  fourTurnFPrime.rotateFrontCounterClockwise();
  assert(fourTurnFPrime == originalCube);
  std::cout << "PASS: Four Front Prime turns restore every sticker position "
               "((F')^4 = I).\n";

  // Test 24: Reverse cancellation order (F' * F = I)
  Cube reverseCancelF;
  reverseCancelF.rotateFrontCounterClockwise();
  reverseCancelF.rotateFrontClockwise();
  assert(reverseCancelF == originalCube);
  std::cout << "PASS: Reverse cancellation verified (F' * F = I).\n";

  // Test 25: Back Prime alters state (B' != I) and cancels Back (B * B' = I)
  Cube testB;
  testB.rotateBackClockwise();
  testB.rotateBackCounterClockwise();
  assert(testB == originalCube);

  Cube onceTurnedBPrime;
  onceTurnedBPrime.rotateBackCounterClockwise();
  assert(onceTurnedBPrime != originalCube);
  std::cout
      << "PASS: Back Prime (B') changes state and cancels B (B * B' = I).\n";

  // Test 26: Four consecutive Back Prime turns restore original state ((B')^4 =
  // I)
  Cube fourTurnBPrime;
  fourTurnBPrime.rotateBackCounterClockwise();
  fourTurnBPrime.rotateBackCounterClockwise();
  fourTurnBPrime.rotateBackCounterClockwise();
  fourTurnBPrime.rotateBackCounterClockwise();
  assert(fourTurnBPrime == originalCube);
  std::cout << "PASS: Four Back Prime turns restore every sticker position "
               "((B')^4 = I).\n";

  // Test 27: Reverse cancellation order (B' * B = I)
  Cube reverseCancelB;
  reverseCancelB.rotateBackCounterClockwise();
  reverseCancelB.rotateBackClockwise();
  assert(reverseCancelB == originalCube);
  std::cout << "PASS: Reverse cancellation verified (B' * B = I).\n";

  // Test 28: Left Prime alters state (L' != I) and cancels Left (L * L' = I)
  Cube testL;
  testL.rotateLeftClockwise();
  testL.rotateLeftCounterClockwise();
  assert(testL == originalCube);

  Cube onceTurnedLPrime;
  onceTurnedLPrime.rotateLeftCounterClockwise();
  assert(onceTurnedLPrime != originalCube);
  std::cout
      << "PASS: Left Prime (L') changes state and cancels L (L * L' = I).\n";

  // Test 29: Four consecutive Left Prime turns restore original state ((L')^4 =
  // I)
  Cube fourTurnLPrime;
  fourTurnLPrime.rotateLeftCounterClockwise();
  fourTurnLPrime.rotateLeftCounterClockwise();
  fourTurnLPrime.rotateLeftCounterClockwise();
  fourTurnLPrime.rotateLeftCounterClockwise();
  assert(fourTurnLPrime == originalCube);
  std::cout << "PASS: Four Left Prime turns restore every sticker position "
               "((L')^4 = I).\n";

  // Test 30: Reverse cancellation order (L' * L = I)
  Cube reverseCancelL;
  reverseCancelL.rotateLeftCounterClockwise();
  reverseCancelL.rotateLeftClockwise();
  assert(reverseCancelL == originalCube);
  std::cout << "PASS: Reverse cancellation verified (L' * L = I).\n";

  // Test 31: Right Prime alters state (R' != I) and cancels Right (R * R' = I)
  Cube testR;
  testR.rotateRightClockwise();
  testR.rotateRightCounterClockwise();
  assert(testR == originalCube);

  Cube onceTurnedRPrime;
  onceTurnedRPrime.rotateRightCounterClockwise();
  assert(onceTurnedRPrime != originalCube);
  std::cout
      << "PASS: Right Prime (R') changes state and cancels R (R * R' = I).\n";

  // Test 32: Four consecutive Right Prime turns restore original state ((R')^4
  // = I)
  Cube fourTurnRPrime;
  fourTurnRPrime.rotateRightCounterClockwise();
  fourTurnRPrime.rotateRightCounterClockwise();
  fourTurnRPrime.rotateRightCounterClockwise();
  fourTurnRPrime.rotateRightCounterClockwise();
  assert(fourTurnRPrime == originalCube);
  std::cout << "PASS: Four Right Prime turns restore every sticker position "
               "((R')^4 = I).\n";

  // Test 33: Reverse cancellation order (R' * R = I)
  Cube reverseCancelR;
  reverseCancelR.rotateRightCounterClockwise();
  reverseCancelR.rotateRightClockwise();
  assert(reverseCancelR == originalCube);
  std::cout << "PASS: Reverse cancellation verified (R' * R = I).\n";

  // =========================================================================
  // 9. Double (Half-Turn) Rotations: Up Double (U2) Tests
  // =========================================================================

  // Test 34: Up Double alters state (U2 != I)
  Cube onceTurnedU2;
  onceTurnedU2.rotateUpDouble();
  assert(onceTurnedU2 != originalCube);
  std::cout << "PASS: One Up Double (U2) turn changes the cube state.\n";

  // Test 35: Self-Inverse Property ((U2)^2 = I)
  Cube twoTurnU2;
  twoTurnU2.rotateUpDouble();
  twoTurnU2.rotateUpDouble();
  assert(twoTurnU2 == originalCube);
  std::cout << "PASS: Two Up Double turns restore every sticker position "
               "((U2)^2 = I).\n";

  // Test 36: Equivalence with two clockwise turns (U2 == U * U)
  Cube twoTurnUClockwise;
  twoTurnUClockwise.rotateUpClockwise();
  twoTurnUClockwise.rotateUpClockwise();
  assert(onceTurnedU2 == twoTurnUClockwise);
  std::cout << "PASS: Up Double is identical to two clockwise turns (U2 == U * U).\n";

  // Test 37: Equivalence with two counter-clockwise turns (U2 == U' * U')
  Cube twoTurnUCounterClockwise;
  twoTurnUCounterClockwise.rotateUpCounterClockwise();
  twoTurnUCounterClockwise.rotateUpCounterClockwise();
  assert(onceTurnedU2 == twoTurnUCounterClockwise);
  std::cout << "PASS: Up Double is identical to two prime turns (U2 == U' * U').\n";

  // Test 38: Down Double alters state (D2 != I)
  Cube onceTurnedD2;
  onceTurnedD2.rotateDownDouble();
  assert(onceTurnedD2 != originalCube);
  std::cout << "PASS: One Down Double (D2) turn changes the cube state.\n";

  // Test 39: Self-Inverse Property ((D2)^2 = I)
  Cube twoTurnD2;
  twoTurnD2.rotateDownDouble();
  twoTurnD2.rotateDownDouble();
  assert(twoTurnD2 == originalCube);
  std::cout << "PASS: Two Down Double turns restore every sticker position "
               "((D2)^2 = I).\n";

  // Test 40: Equivalence with two clockwise turns (D2 == D * D)
  Cube twoTurnDClockwise;
  twoTurnDClockwise.rotateDownClockwise();
  twoTurnDClockwise.rotateDownClockwise();
  assert(onceTurnedD2 == twoTurnDClockwise);
  std::cout << "PASS: Down Double is identical to two clockwise turns (D2 == D * D).\n";

  // Test 41: Equivalence with two counter-clockwise turns (D2 == D' * D')
  Cube twoTurnDCounterClockwise;
  twoTurnDCounterClockwise.rotateDownCounterClockwise();
  twoTurnDCounterClockwise.rotateDownCounterClockwise();
  assert(onceTurnedD2 == twoTurnDCounterClockwise);
  std::cout << "PASS: Down Double is identical to two prime turns (D2 == D' * D').\n";

  // Test 42: Front Double alters state (F2 != I)
  Cube onceTurnedF2;
  onceTurnedF2.rotateFrontDouble();
  assert(onceTurnedF2 != originalCube);
  std::cout << "PASS: One Front Double (F2) turn changes the cube state.\n";

  // Test 43: Self-Inverse Property ((F2)^2 = I)
  Cube twoTurnF2;
  twoTurnF2.rotateFrontDouble();
  twoTurnF2.rotateFrontDouble();
  assert(twoTurnF2 == originalCube);
  std::cout << "PASS: Two Front Double turns restore every sticker position "
               "((F2)^2 = I).\n";

  // Test 44: Equivalence with two clockwise turns (F2 == F * F)
  Cube twoTurnFClockwise;
  twoTurnFClockwise.rotateFrontClockwise();
  twoTurnFClockwise.rotateFrontClockwise();
  assert(onceTurnedF2 == twoTurnFClockwise);
  std::cout << "PASS: Front Double is identical to two clockwise turns (F2 == F * F).\n";

  // Test 45: Equivalence with two counter-clockwise turns (F2 == F' * F')
  Cube twoTurnFCounterClockwise;
  twoTurnFCounterClockwise.rotateFrontCounterClockwise();
  twoTurnFCounterClockwise.rotateFrontCounterClockwise();
  assert(onceTurnedF2 == twoTurnFCounterClockwise);
  std::cout << "PASS: Front Double is identical to two prime turns (F2 == F' * F').\n";

  // Test 46: Back Double alters state (B2 != I)
  Cube onceTurnedB2;
  onceTurnedB2.rotateBackDouble();
  assert(onceTurnedB2 != originalCube);
  std::cout << "PASS: One Back Double (B2) turn changes the cube state.\n";

  // Test 47: Self-Inverse Property ((B2)^2 = I)
  Cube twoTurnB2;
  twoTurnB2.rotateBackDouble();
  twoTurnB2.rotateBackDouble();
  assert(twoTurnB2 == originalCube);
  std::cout << "PASS: Two Back Double turns restore every sticker position "
               "((B2)^2 = I).\n";

  // Test 48: Equivalence with two clockwise turns (B2 == B * B)
  Cube twoTurnBClockwise;
  twoTurnBClockwise.rotateBackClockwise();
  twoTurnBClockwise.rotateBackClockwise();
  assert(onceTurnedB2 == twoTurnBClockwise);
  std::cout << "PASS: Back Double is identical to two clockwise turns (B2 == B * B).\n";

  // Test 49: Equivalence with two counter-clockwise turns (B2 == B' * B')
  Cube twoTurnBCounterClockwise;
  twoTurnBCounterClockwise.rotateBackCounterClockwise();
  twoTurnBCounterClockwise.rotateBackCounterClockwise();
  assert(onceTurnedB2 == twoTurnBCounterClockwise);
  std::cout << "PASS: Back Double is identical to two prime turns (B2 == B' * B').\n";

  // Test 50: Disjoint Face Commutativity (F2 * B2 == B2 * F2)
  Cube fbCube;
  fbCube.rotateFrontDouble();
  fbCube.rotateBackDouble();

  Cube bfCube;
  bfCube.rotateBackDouble();
  bfCube.rotateFrontDouble();

  assert(fbCube == bfCube);
  std::cout << "PASS: Disjoint opposite faces commute (F2 * B2 == B2 * F2).\n";

  return 0;
}
