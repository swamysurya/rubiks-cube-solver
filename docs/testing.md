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
```

