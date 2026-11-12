#include "Cube.hpp"
#include "Notation.hpp"
#include "Scrambler.hpp"
#include "Solver.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <unordered_set>

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

  // =========================================================================
  // 12. Algorithm Parsing, Formatting & Execution Tests
  // =========================================================================

  // Test 67: parseAlgorithm parses standard sequence with messy whitespace
  const auto parsedMoves =
      Notation::parseAlgorithm("  R   U  R'   U'  \n F2  \t D2 ");
  assert(parsedMoves.size() == 6);
  assert(parsedMoves[0] == Move::R);
  assert(parsedMoves[1] == Move::U);
  assert(parsedMoves[2] == Move::R_PRIME);
  assert(parsedMoves[3] == Move::U_PRIME);
  assert(parsedMoves[4] == Move::F2);
  assert(parsedMoves[5] == Move::D2);
  std::cout << "PASS: parseAlgorithm correctly parses sequences with variable "
               "whitespace.\n";

  // Test 68: formatAlgorithm produces canonical WCA string and round-trips
  const std::string formattedAlg = Notation::formatAlgorithm(parsedMoves);
  assert(formattedAlg == "R U R' U' F2 D2");
  assert(Notation::parseAlgorithm(formattedAlg) == parsedMoves);
  std::cout
      << "PASS: formatAlgorithm produces canonical string and round-trips.\n";

  // Test 69: apply(const std::vector<Move>&) matches individual member
  // rotations
  Cube directCube;
  directCube.rotateRightClockwise();
  directCube.rotateUpClockwise();
  directCube.rotateRightCounterClockwise();
  directCube.rotateUpCounterClockwise();
  directCube.rotateFrontDouble();
  directCube.rotateDownDouble();

  Cube vectorCube;
  vectorCube.apply(parsedMoves);
  assert(vectorCube == directCube);
  std::cout << "PASS: apply(const std::vector<Move>&) correctly matches "
               "individual rotations.\n";

  // Test 70: apply(std::string_view) matches vector application
  Cube stringCube;
  stringCube.apply("R U R' U' F2 D2");
  assert(stringCube == vectorCube);
  std::cout << "PASS: apply(std::string_view) produces identical state to "
               "vector apply.\n";

  // Test 71: The Sexy Move 6-Cycle via string algorithm: (R U R' U')^6 =
  // Identity
  Cube sexyStringCube;
  for (int i = 0; i < 6; ++i) {
    sexyStringCube.apply("R U R' U'");
  }
  assert(sexyStringCube == originalCube);
  std::cout << "PASS: Six repetitions of apply(\"R U R' U'\") restore identity "
               "((R U R' U')^6 = I).\n";

  // Test 72: T-Permutation Involution: (T-Perm)^2 = Identity
  // The classic PLL T-Permutation swaps 2 corners (UFR <-> UBR) and 2 edges (UR
  // <-> UL). Being a product of two disjoint 2-cycles, its group order is
  // lcm(2, 2) = 2.
  Cube tPermCube;
  constexpr std::string_view tPerm = "R U R' U' R' F R2 U' R' U' R U R' F'";
  tPermCube.apply(tPerm);
  assert(tPermCube != originalCube);
  tPermCube.apply(tPerm);
  assert(tPermCube == originalCube);
  std::cout << "PASS: Two repetitions of T-Permutation restore identity "
               "((T-Perm)^2 = I).\n";

  // Test 73: parseAlgorithm throws std::invalid_argument on malformed algorithm
  // strings
  bool caughtInvalidInAlg = false;
  try {
    Notation::parseAlgorithm("R U INVALID U'");
  } catch (const std::invalid_argument &) {
    caughtInvalidInAlg = true;
  }
  assert(caughtInvalidInAlg);
  std::cout << "PASS: parseAlgorithm throws std::invalid_argument on malformed "
               "algorithm string.\n";

  // =========================================================================
  // 13. Cube State Hashing & Unordered Container Tests
  // =========================================================================

  // Test 74: Hash Determinism (identical cube states produce identical hashes)
  Cube hashCube1;
  Cube hashCube2;
  const std::size_t hash1 = std::hash<Cube>{}(hashCube1);
  const std::size_t hash2 = std::hash<Cube>{}(hashCube2);
  assert(hash1 == hash2);
  std::cout << "PASS: std::hash<Cube> is deterministic (identical states yield identical hashes).\n";

  // Test 75: Hash Sensitivity (different cube states produce different hashes)
  Cube turnedCube;
  turnedCube.rotateUpClockwise();
  const std::size_t turnedHash = std::hash<Cube>{}(turnedCube);
  assert(turnedHash != hash1);
  std::cout << "PASS: std::hash<Cube> is sensitive (different states yield different hashes).\n";

  // Test 76: std::unordered_set<Cube> integration & O(1) duplicate rejection
  std::unordered_set<Cube> visitedCubes;
  visitedCubes.insert(hashCube1);
  assert(visitedCubes.size() == 1);
  assert(visitedCubes.contains(hashCube1));

  // Inserting duplicate state: size must NOT increase
  visitedCubes.insert(hashCube2);
  assert(visitedCubes.size() == 1);

  // Inserting new state: size increments to 2
  visitedCubes.insert(turnedCube);
  assert(visitedCubes.size() == 2);
  assert(visitedCubes.contains(turnedCube));
  std::cout << "PASS: std::unordered_set<Cube> successfully stores states and rejects duplicates in O(1).\n";

  // =========================================================================
  // 14. BFS Solver Engine Tests
  // =========================================================================

  // Test 77: solveBfs returns empty vector (0 moves) when cube is already solved
  Cube alreadySolvedCube;
  auto solvedResult = Solver::solveBfs(alreadySolvedCube);
  assert(solvedResult.has_value());
  assert(solvedResult->empty());
  std::cout << "PASS: solveBfs returns empty move vector (0 moves) on already-solved cube.\n";

  // Test 78: solveBfs solves single-move scramble (F) with 1 move (F')
  Cube singleMoveCube;
  singleMoveCube.apply(Move::F);
  assert(!singleMoveCube.isSolved());
  auto singleMoveSolution = Solver::solveBfs(singleMoveCube);
  assert(singleMoveSolution.has_value());
  assert(singleMoveSolution->size() == 1);
  assert(singleMoveSolution->front() == Move::F_PRIME);
  singleMoveCube.apply(*singleMoveSolution);
  assert(singleMoveCube.isSolved());
  std::cout << "PASS: solveBfs finds optimal 1-move solution (F') for F turn and restores solved state.\n";

  // Test 79: solveBfs solves multi-move scramble (R U R') with 3-move optimal sequence
  Cube multiMoveCube;
  multiMoveCube.apply("R U R'");
  assert(!multiMoveCube.isSolved());
  auto multiMoveSolution = Solver::solveBfs(multiMoveCube, 4);
  assert(multiMoveSolution.has_value());
  assert(multiMoveSolution->size() == 3);
  multiMoveCube.apply(*multiMoveSolution);
  assert(multiMoveCube.isSolved());
  std::cout << "PASS: solveBfs finds optimal 3-move solution for 'R U R'' scramble and restores solved state.\n";

  // Test 80: solveBfs returns std::nullopt when scramble depth exceeds maxDepth
  Cube deepScrambleCube;
  deepScrambleCube.apply("R U R' U' F"); // 5 moves deep
  auto shallowResult = Solver::solveBfs(deepScrambleCube, 3);
  assert(!shallowResult.has_value());
  std::cout << "PASS: solveBfs returns std::nullopt when scramble requires more moves than maxDepth.\n";

  // Test 81: solveBfs returns std::nullopt when maxDepth = 0 on an unsolved cube
  Cube unsolvedDepthZero;
  unsolvedDepthZero.apply(Move::U);
  auto zeroDepthResult = Solver::solveBfs(unsolvedDepthZero, 0);
  assert(!zeroDepthResult.has_value());
  std::cout << "PASS: solveBfs returns std::nullopt immediately when maxDepth is 0 for unsolved cube.\n";

  // =========================================================================
  // 15. Random Scrambler & Net Visualizer Tests
  // =========================================================================

  // Test 82: Scrambler::generate returns requested number of moves
  const auto scramble20 = Scrambler::generate(20, 12345);
  assert(scramble20.size() == 20);
  const auto scrambleShallow = Scrambler::generate(4, 12345);
  assert(scrambleShallow.size() == 4);
  const auto scrambleZero = Scrambler::generate(0);
  assert(scrambleZero.empty());
  std::cout << "PASS: Scrambler::generate produces exact requested scramble lengths (0, 4, 20).\n";

  // Test 83: Scrambler never generates consecutive moves on the same face
  for (std::size_t i = 1; i < scramble20.size(); ++i) {
    const std::size_t prevFace = static_cast<std::size_t>(scramble20[i - 1]) / 3;
    const std::size_t currFace = static_cast<std::size_t>(scramble20[i]) / 3;
    assert(prevFace != currFace);
  }
  std::cout << "PASS: Scrambler strictly prevents consecutive moves on identical faces.\n";

  // Test 84: Scrambler::generate is deterministic given an explicit seed
  const auto seededTest1 = Scrambler::generate(15, 98765);
  const auto seededTest2 = Scrambler::generate(15, 98765);
  assert(seededTest1 == seededTest2);
  std::cout << "PASS: Scrambler is deterministic when initialized with identical seeds.\n";

  // Test 85: Scrambler::generateString produces valid WCA string that round-trips
  const std::string scrambleStr = Scrambler::generateString(20, 42);
  assert(!scrambleStr.empty());
  const std::vector<Move> parsedScrambleMoves = Notation::parseAlgorithm(scrambleStr);
  assert(parsedScrambleMoves.size() == 20);
  const std::vector<Move> directMoves = Scrambler::generate(20, 42);
  assert(parsedScrambleMoves == directMoves);
  std::cout << "PASS: Scrambler::generateString round-trips accurately through Notation::parseAlgorithm.\n";

  // Test 86: Cube::printNet executes cleanly without throwing
  Cube netCube;
  netCube.apply(scrambleShallow);
  netCube.printNet(false); // Non-color mode
  std::cout << "PASS: Cube::printNet renders 2D net cleanly without error.\n";

  return 0;
}
