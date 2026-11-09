# Testing & CTest — Learning Notes

## 1. Testing Philosophy
- Code should not merely compile; its correctness must be proven with automated assertions.
- **Invariants**: A physical or mathematical property that must always hold true for a valid state.
- **Regression Testing**: Ensuring that adding new moves (e.g. $U$ or $R$) doesn't break previously verified moves (like $F$).

---

## 2. Automated Test Suite (`tests/CubeTests.cpp`)

Our test suite uses `<cassert>` and tests five fundamental cube properties:

### Test 1: New Cube is Solved
```cpp
Cube cube;
assert(cube.isSolved());
```
- **Verifies**: The default constructor leaves every face with matching colors.

### Test 2: Uniform Face Colors
```cpp
for (std::size_t face = 0; face < Cube::FaceCount; ++face) {
    const std::size_t start = face * Cube::StickersPerFace;
    const Color expectedColor = cube.getSticker(start);

    for (std::size_t i = 1; i < Cube::StickersPerFace; ++i) {
        assert(cube.getSticker(start + i) == expectedColor);
    }
}
```
- **Verifies**: On each of the 6 faces, all 9 stickers match the face's initial color.

### Test 3: Total Color Distribution (Conservation of Stickers)
```cpp
for (std::size_t colorIndex = 0; colorIndex < 6; ++colorIndex) {
    const Color expectedColor = cube.getSticker(colorIndex * Cube::StickersPerFace);
    std::size_t count = 0;
    for (std::size_t i = 0; i < Cube::StickerCount; ++i) {
        if (cube.getSticker(i) == expectedColor) ++count;
    }
    assert(count == Cube::StickersPerFace); // Must equal 9
}
```
- **Verifies**: Exactly 9 stickers of each color exist across the entire 54-sticker cube.

### Test 4: Four Front Turns Restore the Cube ($F^4 = I$)
```cpp
Cube originalCube;
Cube fourTurnCube;

fourTurnCube.rotateFrontClockwise();
fourTurnCube.rotateFrontClockwise();
fourTurnCube.rotateFrontClockwise();
fourTurnCube.rotateFrontClockwise();

assert(fourTurnCube.hasSameState(originalCube));
```
- **Verifies**: A 90-degree clockwise rotation repeated 4 times ($360^\circ$) restores every sticker to its original position (order of move = 4).

### Test 5: One Front Turn Changes State ($F \ne I$)
```cpp
Cube onceTurnedCube;
onceTurnedCube.rotateFrontClockwise();

assert(!onceTurnedCube.hasSameState(originalCube));
```
- **Verifies**: A single move actually alters the cube state and is not a no-op.

### Test 6: One Up Turn Changes State ($U \ne I$)
```cpp
Cube onceTurnedUp;
onceTurnedUp.rotateUpClockwise();

assert(!onceTurnedUp.hasSameState(originalCube));
```
- **Verifies**: An Up face rotation changes the cube state and shifts the top rows.

### Test 7: Four Up Turns Restore the Cube ($U^4 = I$)
```cpp
Cube fourTurnUp;
fourTurnUp.rotateUpClockwise();
fourTurnUp.rotateUpClockwise();
fourTurnUp.rotateUpClockwise();
fourTurnUp.rotateUpClockwise();

assert(fourTurnUp.hasSameState(originalCube));
```
- **Verifies**: Repeating the Up rotation 4 times restores all stickers to their original positions.

### Test 8: One Right Turn Changes State ($R \ne I$)
```cpp
Cube onceTurnedRight;
onceTurnedRight.rotateRightClockwise();

assert(!onceTurnedRight.hasSameState(originalCube));
```
- **Verifies**: A Right face rotation changes the cube state and shifts vertical columns.

### Test 9: Four Right Turns Restore the Cube ($R^4 = I$)
```cpp
Cube fourTurnRight;
fourTurnRight.rotateRightClockwise();
fourTurnRight.rotateRightClockwise();
fourTurnRight.rotateRightClockwise();
fourTurnRight.rotateRightClockwise();

assert(fourTurnRight.hasSameState(originalCube));
```
- **Verifies**: Repeating the Right rotation 4 times restores all stickers to their original positions.

### Test 10: One Left Turn Changes State ($L \ne I$)
```cpp
Cube onceTurnedLeft;
onceTurnedLeft.rotateLeftClockwise();

assert(!onceTurnedLeft.hasSameState(originalCube));
```
- **Verifies**: A Left face rotation changes the cube state and shifts vertical columns downwards on the front face.

### Test 11: Four Left Turns Restore the Cube ($L^4 = I$)
```cpp
Cube fourTurnLeft;
fourTurnLeft.rotateLeftClockwise();
fourTurnLeft.rotateLeftClockwise();
fourTurnLeft.rotateLeftClockwise();
fourTurnLeft.rotateLeftClockwise();

assert(fourTurnLeft.hasSameState(originalCube));
```
- **Verifies**: Repeating the Left rotation 4 times restores all stickers to their original positions.

### Test 12: One Down Turn Changes State ($D \ne I$)
```cpp
Cube onceTurnedDown;
onceTurnedDown.rotateDownClockwise();

assert(!onceTurnedDown.hasSameState(originalCube));
```
- **Verifies**: A Down face rotation alters the cube state and shifts the bottom rows across adjacent faces.

### Test 13: Four Down Turns Restore the Cube ($D^4 = I$)
```cpp
Cube fourTurnDown;
fourTurnDown.rotateDownClockwise();
fourTurnDown.rotateDownClockwise();
fourTurnDown.rotateDownClockwise();
fourTurnDown.rotateDownClockwise();

assert(fourTurnDown.hasSameState(originalCube));
```
- **Verifies**: Repeating the Down rotation 4 times restores all stickers to their original positions.

### Test 14: One Back Turn Changes State ($B \ne I$, tested with `operator!=`)
```cpp
Cube onceTurnedBack;
onceTurnedBack.rotateBackClockwise();

assert(onceTurnedBack != originalCube);
```
- **Verifies**: A Back face rotation alters the cube state and proves C++20 `operator!=` correctly identifies state divergence.

### Test 15: Four Back Turns Restore the Cube ($B^4 = I$, tested with `operator==`)
```cpp
Cube fourTurnBack;
fourTurnBack.rotateBackClockwise();
fourTurnBack.rotateBackClockwise();
fourTurnBack.rotateBackClockwise();
fourTurnBack.rotateBackClockwise();

assert(fourTurnBack == originalCube);
```
- **Verifies**: Repeating the Back rotation 4 times restores all stickers, and C++20 `operator==` confirms equality.

### Test 16: Up Prime Alters State ($U' \ne I$) and Cancels Up ($U \cdot U' = I$)
```cpp
Cube testU;
testU.rotateUpClockwise();
testU.rotateUpCounterClockwise();
assert(testU == originalCube);

Cube onceTurnedUPrime;
onceTurnedUPrime.rotateUpCounterClockwise();
assert(onceTurnedUPrime != originalCube);
```
- **Verifies**:
  - $U' \ne I$: An Up prime move performs a real transformation.
  - $U \cdot U' = I$: Applying a clockwise turn followed by its counter-clockwise turn returns the cube to its exact initial state.

### Test 17: Four Up Prime Turns Restore Original State ($(U')^4 = I$)
```cpp
Cube fourTurnUPrime;
fourTurnUPrime.rotateUpCounterClockwise();
fourTurnUPrime.rotateUpCounterClockwise();
fourTurnUPrime.rotateUpCounterClockwise();
fourTurnUPrime.rotateUpCounterClockwise();

assert(fourTurnUPrime == originalCube);
```
- **Verifies**: Four consecutive prime turns restore all stickers, proving the cyclic group order of 4 for inverses.

### Test 18: Reverse Cancellation Order ($U' \cdot U = I$)
```cpp
Cube reverseCancelU;
reverseCancelU.rotateUpCounterClockwise();
reverseCancelU.rotateUpClockwise();

assert(reverseCancelU == originalCube);
```
- **Verifies**: Cancellation holds commutatively for inverse pairs ($U' \cdot U = I$).

### Test 19: Down Prime Alters State ($D' \ne I$) and Cancels Down ($D \cdot D' = I$)
```cpp
Cube testD;
testD.rotateDownClockwise();
testD.rotateDownCounterClockwise();
assert(testD == originalCube);

Cube onceTurnedDPrime;
onceTurnedDPrime.rotateDownCounterClockwise();
assert(onceTurnedDPrime != originalCube);
```
- **Verifies**:
  - $D' \ne I$: Down prime move performs a real transformation.
  - $D \cdot D' = I$: Applying a clockwise Down turn followed by its counter-clockwise turn returns the cube to solved state.

### Test 20: Four Down Prime Turns Restore Original State ($(D')^4 = I$)
```cpp
Cube fourTurnDPrime;
fourTurnDPrime.rotateDownCounterClockwise();
fourTurnDPrime.rotateDownCounterClockwise();
fourTurnDPrime.rotateDownCounterClockwise();
fourTurnDPrime.rotateDownCounterClockwise();

assert(fourTurnDPrime == originalCube);
```
- **Verifies**: Four consecutive $D'$ turns restore all stickers, confirming cyclic order 4.

### Test 21: Reverse Cancellation Order ($D' \cdot D = I$)
```cpp
Cube reverseCancelD;
reverseCancelD.rotateDownCounterClockwise();
reverseCancelD.rotateDownClockwise();

assert(reverseCancelD == originalCube);
```
- **Verifies**: Cancellation holds in reverse ($D' \cdot D = I$).

### Test 22: Front Prime Alters State ($F' \ne I$) and Cancels Front ($F \cdot F' = I$)
```cpp
Cube testF;
testF.rotateFrontClockwise();
testF.rotateFrontCounterClockwise();
assert(testF == originalCube);

Cube onceTurnedFPrime;
onceTurnedFPrime.rotateFrontCounterClockwise();
assert(onceTurnedFPrime != originalCube);
```
- **Verifies**:
  - $F' \ne I$: Front prime move performs a real transformation.
  - $F \cdot F' = I$: Applying a clockwise Front turn followed by its counter-clockwise turn returns the cube to solved state.

### Test 23: Four Front Prime Turns Restore Original State ($(F')^4 = I$)
```cpp
Cube fourTurnFPrime;
fourTurnFPrime.rotateFrontCounterClockwise();
fourTurnFPrime.rotateFrontCounterClockwise();
fourTurnFPrime.rotateFrontCounterClockwise();
fourTurnFPrime.rotateFrontCounterClockwise();

assert(fourTurnFPrime == originalCube);
```
- **Verifies**: Four consecutive $F'$ turns restore all stickers, confirming cyclic order 4.

### Test 24: Reverse Cancellation Order ($F' \cdot F = I$)
```cpp
Cube reverseCancelF;
reverseCancelF.rotateFrontCounterClockwise();
reverseCancelF.rotateFrontClockwise();

assert(reverseCancelF == originalCube);
```
- **Verifies**: Cancellation holds in reverse ($F' \cdot F = I$).

### Test 25: Back Prime Alters State ($B' \ne I$) and Cancels Back ($B \cdot B' = I$)
```cpp
Cube testB;
testB.rotateBackClockwise();
testB.rotateBackCounterClockwise();
assert(testB == originalCube);

Cube onceTurnedBPrime;
onceTurnedBPrime.rotateBackCounterClockwise();
assert(onceTurnedBPrime != originalCube);
```
- **Verifies**:
  - $B' \ne I$: Back prime move performs a real transformation.
  - $B \cdot B' = I$: Applying a clockwise Back turn followed by its counter-clockwise turn returns the cube to solved state.

### Test 26: Four Back Prime Turns Restore Original State ($(B')^4 = I$)
```cpp
Cube fourTurnBPrime;
fourTurnBPrime.rotateBackCounterClockwise();
fourTurnBPrime.rotateBackCounterClockwise();
fourTurnBPrime.rotateBackCounterClockwise();
fourTurnBPrime.rotateBackCounterClockwise();

assert(fourTurnBPrime == originalCube);
```
- **Verifies**: Four consecutive $B'$ turns restore all stickers, confirming cyclic order 4.

### Test 27: Reverse Cancellation Order ($B' \cdot B = I$)
```cpp
Cube reverseCancelB;
reverseCancelB.rotateBackCounterClockwise();
reverseCancelB.rotateBackClockwise();

assert(reverseCancelB == originalCube);
```
- **Verifies**: Cancellation holds in reverse ($B' \cdot B = I$).

### Test 28: Left Prime Alters State ($L' \ne I$) and Cancels Left ($L \cdot L' = I$)
```cpp
Cube testL;
testL.rotateLeftClockwise();
testL.rotateLeftCounterClockwise();
assert(testL == originalCube);

Cube onceTurnedLPrime;
onceTurnedLPrime.rotateLeftCounterClockwise();
assert(onceTurnedLPrime != originalCube);
```
- **Verifies**:
  - $L' \ne I$: Left prime move performs a real transformation.
  - $L \cdot L' = I$: Applying a clockwise Left turn followed by its counter-clockwise turn returns the cube to solved state.

### Test 29: Four Left Prime Turns Restore Original State ($(L')^4 = I$)
```cpp
Cube fourTurnLPrime;
fourTurnLPrime.rotateLeftCounterClockwise();
fourTurnLPrime.rotateLeftCounterClockwise();
fourTurnLPrime.rotateLeftCounterClockwise();
fourTurnLPrime.rotateLeftCounterClockwise();

assert(fourTurnLPrime == originalCube);
```
- **Verifies**: Four consecutive $L'$ turns restore all stickers, confirming cyclic order 4.

### Test 30: Reverse Cancellation Order ($L' \cdot L = I$)
```cpp
Cube reverseCancelL;
reverseCancelL.rotateLeftCounterClockwise();
reverseCancelL.rotateLeftClockwise();

assert(reverseCancelL == originalCube);
```
- **Verifies**: Cancellation holds in reverse ($L' \cdot L = I$).

---

## 3. Running Tests with CTest
CTest is CMake's automated test execution framework.

```powershell
# Run all registered tests via CTest
ctest --test-dir build --output-on-failure

# Alternatively, run the test binary directly
.\build\cube_tests.exe
```

Expected output:
```text
PASS: A newly created cube is solved.
PASS: Every face has a uniform color.
PASS: Each face color appears nine times.
PASS: One Front turn changes the cube state.
PASS: Four Front turns restore every sticker position.
PASS: One Up turn changes the cube state.
PASS: Four Up turns restore every sticker position.
PASS: One Right turn changes the cube state.
PASS: Four Right turns restore every sticker position.
PASS: One Left turn changes the cube state.
PASS: Four Left turns restore every sticker position.
PASS: One Down turn changes the cube state.
PASS: Four Down turns restore every sticker position.
PASS: One Back turn changes the cube state (verified with operator!=).
PASS: Four Back turns restore every sticker position (verified with operator==).
PASS: Up Prime (U') changes state and cancels U (U * U' = I).
PASS: Four Up Prime turns restore every sticker position ((U')^4 = I).
PASS: Reverse cancellation verified (U' * U = I).
PASS: Down Prime (D') changes state and cancels D (D * D' = I).
PASS: Four Down Prime turns restore every sticker position ((D')^4 = I).
PASS: Reverse cancellation verified (D' * D = I).
PASS: Front Prime (F') changes state and cancels F (F * F' = I).
PASS: Four Front Prime turns restore every sticker position ((F')^4 = I).
PASS: Reverse cancellation verified (F' * F = I).
PASS: Back Prime (B') changes state and cancels B (B * B' = I).
PASS: Four Back Prime turns restore every sticker position ((B')^4 = I).
PASS: Reverse cancellation verified (B' * B = I).
PASS: Left Prime (L') changes state and cancels L (L * L' = I).
PASS: Four Left Prime turns restore every sticker position ((L')^4 = I).
PASS: Reverse cancellation verified (L' * L = I).
```

