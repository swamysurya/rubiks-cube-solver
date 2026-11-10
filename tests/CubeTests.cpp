#include "Cube.hpp"
#include "Notation.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

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
  std::cout
      << "PASS: Up Double is identical to two clockwise turns (U2 == U * U).\n";

  // Test 37: Equivalence with two counter-clockwise turns (U2 == U' * U')
  Cube twoTurnUCounterClockwise;
  twoTurnUCounterClockwise.rotateUpCounterClockwise();
  twoTurnUCounterClockwise.rotateUpCounterClockwise();
  assert(onceTurnedU2 == twoTurnUCounterClockwise);
  std::cout
      << "PASS: Up Double is identical to two prime turns (U2 == U' * U').\n";

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
  std::cout << "PASS: Down Double is identical to two clockwise turns (D2 == D "
               "* D).\n";

  // Test 41: Equivalence with two counter-clockwise turns (D2 == D' * D')
  Cube twoTurnDCounterClockwise;
  twoTurnDCounterClockwise.rotateDownCounterClockwise();
  twoTurnDCounterClockwise.rotateDownCounterClockwise();
  assert(onceTurnedD2 == twoTurnDCounterClockwise);
  std::cout
      << "PASS: Down Double is identical to two prime turns (D2 == D' * D').\n";

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
  std::cout << "PASS: Front Double is identical to two clockwise turns (F2 == "
               "F * F).\n";

  // Test 45: Equivalence with two counter-clockwise turns (F2 == F' * F')
  Cube twoTurnFCounterClockwise;
  twoTurnFCounterClockwise.rotateFrontCounterClockwise();
  twoTurnFCounterClockwise.rotateFrontCounterClockwise();
  assert(onceTurnedF2 == twoTurnFCounterClockwise);
  std::cout << "PASS: Front Double is identical to two prime turns (F2 == F' * "
               "F').\n";

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
  std::cout << "PASS: Back Double is identical to two clockwise turns (B2 == B "
               "* B).\n";

  // Test 49: Equivalence with two counter-clockwise turns (B2 == B' * B')
  Cube twoTurnBCounterClockwise;
  twoTurnBCounterClockwise.rotateBackCounterClockwise();
  twoTurnBCounterClockwise.rotateBackCounterClockwise();
  assert(onceTurnedB2 == twoTurnBCounterClockwise);
  std::cout
      << "PASS: Back Double is identical to two prime turns (B2 == B' * B').\n";

  // Test 50: Disjoint Face Commutativity (F2 * B2 == B2 * F2)
  Cube fbCube;
  fbCube.rotateFrontDouble();
  fbCube.rotateBackDouble();

  Cube bfCube;
  bfCube.rotateBackDouble();
  bfCube.rotateFrontDouble();

  assert(fbCube == bfCube);
  std::cout << "PASS: Disjoint opposite faces commute (F2 * B2 == B2 * F2).\n";

  // Test 51: Left Double alters state (L2 != I)
  Cube onceTurnedL2;
  onceTurnedL2.rotateLeftDouble();
  assert(onceTurnedL2 != originalCube);
  std::cout << "PASS: One Left Double (L2) turn changes the cube state.\n";

  // Test 52: Self-Inverse Property ((L2)^2 = I)
  Cube twoTurnL2;
  twoTurnL2.rotateLeftDouble();
  twoTurnL2.rotateLeftDouble();
  assert(twoTurnL2 == originalCube);
  std::cout << "PASS: Two Left Double turns restore every sticker position "
               "((L2)^2 = I).\n";

  // Test 53: Equivalence with two clockwise turns (L2 == L * L)
  Cube twoTurnLClockwise;
  twoTurnLClockwise.rotateLeftClockwise();
  twoTurnLClockwise.rotateLeftClockwise();
  assert(onceTurnedL2 == twoTurnLClockwise);
  std::cout << "PASS: Left Double is identical to two clockwise turns (L2 == L "
               "* L).\n";

  // Test 54: Equivalence with two counter-clockwise turns (L2 == L' * L')
  Cube twoTurnLCounterClockwise;
  twoTurnLCounterClockwise.rotateLeftCounterClockwise();
  twoTurnLCounterClockwise.rotateLeftCounterClockwise();
  assert(onceTurnedL2 == twoTurnLCounterClockwise);
  std::cout
      << "PASS: Left Double is identical to two prime turns (L2 == L' * L').\n";

  // Test 55: Right Double alters state (R2 != I)
  Cube onceTurnedR2;
  onceTurnedR2.rotateRightDouble();
  assert(onceTurnedR2 != originalCube);
  std::cout << "PASS: One Right Double (R2) turn changes the cube state.\n";

  // Test 56: Self-Inverse Property ((R2)^2 = I)
  Cube twoTurnR2;
  twoTurnR2.rotateRightDouble();
  twoTurnR2.rotateRightDouble();
  assert(twoTurnR2 == originalCube);
  std::cout << "PASS: Two Right Double turns restore every sticker position "
               "((R2)^2 = I).\n";

  // Test 57: Equivalence with two clockwise turns (R2 == R * R)
  Cube twoTurnRClockwise;
  twoTurnRClockwise.rotateRightClockwise();
  twoTurnRClockwise.rotateRightClockwise();
  assert(onceTurnedR2 == twoTurnRClockwise);
  std::cout << "PASS: Right Double is identical to two clockwise turns (R2 == "
               "R * R).\n";

  // Test 58: Equivalence with two counter-clockwise turns (R2 == R' * R')
  Cube twoTurnRCounterClockwise;
  twoTurnRCounterClockwise.rotateRightCounterClockwise();
  twoTurnRCounterClockwise.rotateRightCounterClockwise();
  assert(onceTurnedR2 == twoTurnRCounterClockwise);
  std::cout << "PASS: Right Double is identical to two prime turns (R2 == R' * "
               "R').\n";

  // Test 59: Disjoint Face Commutativity (L2 * R2 == R2 * L2)
  Cube lrCube;
  lrCube.rotateLeftDouble();
  lrCube.rotateRightDouble();

  Cube rlCube;
  rlCube.rotateRightDouble();
  rlCube.rotateLeftDouble();

  assert(lrCube == rlCube);
  std::cout << "PASS: Disjoint opposite faces commute (L2 * R2 == R2 * L2).\n";

  // =========================================================================
  // 10. Move Dispatcher & WCA Trigger Tests
  // =========================================================================

  // Test 60: apply(Move::U) matches rotateUpClockwise()
  Cube applyU;
  applyU.apply(Move::U);
  Cube directU;
  directU.rotateUpClockwise();
  assert(applyU == directU);
  std::cout << "PASS: apply(Move::U) produces identical state to "
               "rotateUpClockwise().\n";

  // Test 61: apply(Move::F_PRIME) matches rotateFrontCounterClockwise()
  Cube applyFPrime;
  applyFPrime.apply(Move::F_PRIME);
  Cube directFPrime;
  directFPrime.rotateFrontCounterClockwise();
  assert(applyFPrime == directFPrime);
  std::cout << "PASS: apply(Move::F_PRIME) produces identical state to "
               "rotateFrontCounterClockwise().\n";

  // Test 62: apply(Move::R2) matches rotateRightDouble()
  Cube applyR2;
  applyR2.apply(Move::R2);
  Cube directR2;
  directR2.rotateRightDouble();
  assert(applyR2 == directR2);
  std::cout << "PASS: apply(Move::R2) produces identical state to "
               "rotateRightDouble().\n";

  // Test 63: The 6-Cycle "Sexy Move" Invariant: (R U R' U')^6 = Identity
  Cube sexyMoveCube;
  for (int i = 0; i < 6; ++i) {
    sexyMoveCube.apply(Move::R);
    sexyMoveCube.apply(Move::U);
    sexyMoveCube.apply(Move::R_PRIME);
    sexyMoveCube.apply(Move::U_PRIME);
  }
  assert(sexyMoveCube == originalCube);
  std::cout << "PASS: Six repetitions of (R U R' U') restore identity ((R U R' "
               "U')^6 = I).\n";

  // =========================================================================
  // 11. WCA Move Notation Parser & Formatter Tests
  // =========================================================================

  // Test 64: parseMove correctly parses all 18 standard WCA tokens
  assert(Notation::parseMove("U") == Move::U);
  assert(Notation::parseMove("U'") == Move::U_PRIME);
  assert(Notation::parseMove("U2") == Move::U2);

  assert(Notation::parseMove("D") == Move::D);
  assert(Notation::parseMove("D'") == Move::D_PRIME);
  assert(Notation::parseMove("D2") == Move::D2);

  assert(Notation::parseMove("F") == Move::F);
  assert(Notation::parseMove("F'") == Move::F_PRIME);
  assert(Notation::parseMove("F2") == Move::F2);

  assert(Notation::parseMove("B") == Move::B);
  assert(Notation::parseMove("B'") == Move::B_PRIME);
  assert(Notation::parseMove("B2") == Move::B2);

  assert(Notation::parseMove("L") == Move::L);
  assert(Notation::parseMove("L'") == Move::L_PRIME);
  assert(Notation::parseMove("L2") == Move::L2);

  assert(Notation::parseMove("R") == Move::R);
  assert(Notation::parseMove("R'") == Move::R_PRIME);
  assert(Notation::parseMove("R2") == Move::R2);
  std::cout << "PASS: parseMove correctly parses all 18 WCA move tokens.\n";

  // Test 65: moveToString produces exact WCA notation and round-trips
  for (std::size_t i = 0; i < MoveCount; ++i) {
    const Move m = static_cast<Move>(i);
    const std::string_view str = Notation::moveToString(m);
    assert(!str.empty());
    assert(Notation::parseMove(str) == m);
  }
  std::cout
      << "PASS: moveToString correctly formats all 18 moves and round-trips.\n";

  // Test 66: parseMove throws std::invalid_argument on malformed inputs
  bool caughtInvalidFace = false;
  try {
    Notation::parseMove("X");
  } catch (const std::invalid_argument &) {
    caughtInvalidFace = true;
  }
  assert(caughtInvalidFace);

  bool caughtInvalidModifier = false;
  try {
    Notation::parseMove("U3");
  } catch (const std::invalid_argument &) {
    caughtInvalidModifier = true;
  }
  assert(caughtInvalidModifier);

  bool caughtEmptyToken = false;
  try {
    Notation::parseMove("");
  } catch (const std::invalid_argument &) {
    caughtEmptyToken = true;
  }
  assert(caughtEmptyToken);

  bool caughtLongToken = false;
  try {
    Notation::parseMove("R2Prime");
  } catch (const std::invalid_argument &) {
    caughtLongToken = true;
  }
  assert(caughtLongToken);
  std::cout
      << "PASS: parseMove throws std::invalid_argument on malformed tokens.\n";

  return 0;
}
