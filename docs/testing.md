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

### Test 31: Right Prime Alters State ($R' \ne I$) and Cancels Right ($R \cdot R' = I$)
```cpp
Cube testR;
testR.rotateRightClockwise();
testR.rotateRightCounterClockwise();
assert(testR == originalCube);

Cube onceTurnedRPrime;
onceTurnedRPrime.rotateRightCounterClockwise();
assert(onceTurnedRPrime != originalCube);
```
- **Verifies**:
  - $R' \ne I$: Right prime move performs a real transformation.
  - $R \cdot R' = I$: Applying a clockwise Right turn followed by its counter-clockwise turn returns the cube to solved state.

### Test 32: Four Right Prime Turns Restore Original State ($(R')^4 = I$)
```cpp
Cube fourTurnRPrime;
fourTurnRPrime.rotateRightCounterClockwise();
fourTurnRPrime.rotateRightCounterClockwise();
fourTurnRPrime.rotateRightCounterClockwise();
fourTurnRPrime.rotateRightCounterClockwise();

assert(fourTurnRPrime == originalCube);
```
- **Verifies**: Four consecutive $R'$ turns restore all stickers, confirming cyclic order 4.

### Test 33: Reverse Cancellation Order ($R' \cdot R = I$)
```cpp
Cube reverseCancelR;
reverseCancelR.rotateRightCounterClockwise();
reverseCancelR.rotateRightClockwise();

assert(reverseCancelR == originalCube);
```
- **Verifies**: Cancellation holds in reverse ($R' \cdot R = I$).

### Test 34: One Up Double Turn Changes State ($U2 \ne I$)
```cpp
Cube onceTurnedU2;
onceTurnedU2.rotateUpDouble();
assert(onceTurnedU2 != originalCube);
```
- **Verifies**: A 180-degree double turn modifies the cube state.

### Test 35: Self-Inverse Involution Property ($(U2)^2 = I$)
```cpp
Cube twoTurnU2;
twoTurnU2.rotateUpDouble();
twoTurnU2.rotateUpDouble();
assert(twoTurnU2 == originalCube);
```
- **Verifies**: Applying $U2$ twice restores identity, proving $U2$ is an involution ($(U2)^2 = I$).

### Test 36: Equivalence with Two Clockwise Turns ($U2 \equiv U \cdot U$)
```cpp
Cube twoTurnUClockwise;
twoTurnUClockwise.rotateUpClockwise();
twoTurnUClockwise.rotateUpClockwise();
assert(onceTurnedU2 == twoTurnUClockwise);
```
- **Verifies**: $U2$ produces the exact same permutation as two $90^\circ$ clockwise turns.

### Test 37: Equivalence with Two Prime Turns ($U2 \equiv U' \cdot U'$)
```cpp
Cube twoTurnUCounterClockwise;
twoTurnUCounterClockwise.rotateUpCounterClockwise();
twoTurnUCounterClockwise.rotateUpCounterClockwise();
assert(onceTurnedU2 == twoTurnUCounterClockwise);
```
- **Verifies**: Direction invariance: turning $+180^\circ$ and $-180^\circ$ are identical in $\mathbb{Z}_4$.

### Test 38: One Down Double Turn Changes State ($D2 \ne I$)
```cpp
Cube onceTurnedD2;
onceTurnedD2.rotateDownDouble();
assert(onceTurnedD2 != originalCube);
```
- **Verifies**: A 180-degree Down double turn modifies the cube state.

### Test 39: Self-Inverse Involution Property ($(D2)^2 = I$)
```cpp
Cube twoTurnD2;
twoTurnD2.rotateDownDouble();
twoTurnD2.rotateDownDouble();
assert(twoTurnD2 == originalCube);
```
- **Verifies**: Applying $D2$ twice restores identity ($(D2)^2 = I$).

### Test 40: Equivalence with Two Clockwise Turns ($D2 \equiv D \cdot D$)
```cpp
Cube twoTurnDClockwise;
twoTurnDClockwise.rotateDownClockwise();
twoTurnDClockwise.rotateDownClockwise();
assert(onceTurnedD2 == twoTurnDClockwise);
```
- **Verifies**: $D2$ produces the exact same permutation as two $90^\circ$ clockwise Down turns.

### Test 41: Equivalence with Two Prime Turns ($D2 \equiv D' \cdot D'$)
```cpp
Cube twoTurnDCounterClockwise;
twoTurnDCounterClockwise.rotateDownCounterClockwise();
twoTurnDCounterClockwise.rotateDownCounterClockwise();
assert(onceTurnedD2 == twoTurnDCounterClockwise);
```
- **Verifies**: Direction invariance: $D \cdot D \equiv D' \cdot D'$.

### Test 42–45: Front Double ($F2$) Invariants
```cpp
// 1. Alteration: F2 != I
// 2. Self-Inverse: (F2)^2 == I
// 3. Equivalence: F2 == F * F
// 4. Prime Equivalence: F2 == F' * F'
```
- **Verifies**: Front Double modifies state, restores state after 2 turns, and matches $F \cdot F$ and $F' \cdot F'$.

### Test 46–49: Back Double ($B2$) Invariants
```cpp
// 1. Alteration: B2 != I
// 2. Self-Inverse: (B2)^2 == I
// 3. Equivalence: B2 == B * B
// 4. Prime Equivalence: B2 == B' * B'
```
- **Verifies**: Back Double modifies state, restores state after 2 turns, and matches $B \cdot B$ and $B' \cdot B'$.

### Test 50: Disjoint Opposite Face Commutativity ($F2 \cdot B2 = B2 \cdot F2$)
```cpp
Cube fbCube;
fbCube.rotateFrontDouble();
fbCube.rotateBackDouble();

Cube bfCube;
bfCube.rotateBackDouble();
bfCube.rotateFrontDouble();

assert(fbCube == bfCube);
```
- **Verifies**: Because Front and Back share zero stickers, their operations commute.

### Test 51–54: Left Double ($L2$) Invariants
```cpp
// 1. Alteration: L2 != I
// 2. Self-Inverse: (L2)^2 == I
// 3. Equivalence: L2 == L * L
// 4. Prime Equivalence: L2 == L' * L'
```
- **Verifies**: Left Double modifies state, restores state after 2 turns, and matches $L \cdot L$ and $L' \cdot L'$.

### Test 55–58: Right Double ($R2$) Invariants
```cpp
// 1. Alteration: R2 != I
// 2. Self-Inverse: (R2)^2 == I
// 3. Equivalence: R2 == R * R
// 4. Prime Equivalence: R2 == R' * R'
```
- **Verifies**: Right Double modifies state, restores state after 2 turns, and matches $R \cdot R$ and $R' \cdot R'$.

### Test 59: Disjoint Opposite Face Commutativity ($L2 \cdot R2 = R2 \cdot L2$)
```cpp
Cube lrCube;
lrCube.rotateLeftDouble();
lrCube.rotateRightDouble();

Cube rlCube;
rlCube.rotateRightDouble();
rlCube.rotateLeftDouble();

assert(lrCube == rlCube);
```
- **Verifies**: Because Left and Right share zero stickers, their operations commute.

### Tests 60–62: General Move Dispatcher (`Cube::apply(Move)`)
```cpp
// Test 60: apply(Move::U) == rotateUpClockwise()
// Test 61: apply(Move::F_PRIME) == rotateFrontCounterClockwise()
// Test 62: apply(Move::R2) == rotateRightDouble()
```
- **Verifies**: `Cube::apply(Move)` correctly routes clock, prime, and double moves to their respective member functions.

### Test 63: The 6-Cycle "Sexy Move" Invariant ($(R \; U \; R' \; U')^6 = I$)
```cpp
Cube sexyMoveCube;
for (int i = 0; i < 6; ++i) {
  sexyMoveCube.apply(Move::R);
  sexyMoveCube.apply(Move::U);
  sexyMoveCube.apply(Move::R_PRIME);
  sexyMoveCube.apply(Move::U_PRIME);
}
assert(sexyMoveCube == originalCube);
```
- **Verifies**: Repeating $(R \; U \; R' \; U')$ exactly 6 times restores the solved cube state, verifying group cyclic order.

### Test 64: Token Parsing for All 18 WCA Moves
```cpp
assert(Notation::parseMove("U") == Move::U);
assert(Notation::parseMove("U'") == Move::U_PRIME);
assert(Notation::parseMove("U2") == Move::U2);
// ... verifies D, D', D2, F, F', F2, B, B', B2, L, L', L2, R, R', R2
```
- **Verifies**: `Notation::parseMove` correctly maps every valid WCA string token to its corresponding `Move` enum.

### Test 65: Bijective Round-Trip Formatting (`moveToString`)
```cpp
for (std::size_t i = 0; i < MoveCount; ++i) {
  const Move m = static_cast<Move>(i);
  const std::string_view str = Notation::moveToString(m);
  assert(!str.empty());
  assert(Notation::parseMove(str) == m);
}
```
- **Verifies**: For all 18 moves, `parseMove(moveToString(m)) == m`, proving the mapping is an exact bijection (one-to-one and invertible).

### Test 66: Error Handling for Malformed Move Tokens
```cpp
// Throws std::invalid_argument for unrecognized face "X"
// Throws std::invalid_argument for invalid modifier "U3"
// Throws std::invalid_argument for empty string ""
// Throws std::invalid_argument for overly long token "R2Prime"
```
- **Verifies**: `Notation::parseMove` safely rejects invalid faces, unsupported modifiers, empty strings, and long tokens by throwing `std::invalid_argument`.

### Test 67: Algorithm Parsing with Arbitrary Whitespace
```cpp
const auto parsedMoves = Notation::parseAlgorithm("  R   U  R'   U'  \n F2  \t D2 ");
assert(parsedMoves.size() == 6);
```
- **Verifies**: `Notation::parseAlgorithm` cleanly extracts tokens separated by variable spaces, tabs, and newlines without heap allocations during scanning.

### Test 68: Round-Trip Canonical Formatting (`formatAlgorithm`)
```cpp
const std::string formatted = Notation::formatAlgorithm(parsedMoves);
assert(formatted == "R U R' U' F2 D2");
assert(Notation::parseAlgorithm(formatted) == parsedMoves);
```
- **Verifies**: `Notation::formatAlgorithm` produces canonical space-separated WCA notation without leading or trailing spaces, proving `parse(format(moves)) == moves`.

### Test 69: Batch Move Sequence Execution (`Cube::apply(vector<Move>)`)
```cpp
Cube vectorCube;
vectorCube.apply(parsedMoves);
assert(vectorCube == directCube);
```
- **Verifies**: Tier 2 `Cube::apply(const std::vector<Move>&)` sequentially applies all moves, producing an identical state to manual member function calls.

### Test 70: String Facade Execution (`Cube::apply(string_view)`)
```cpp
Cube stringCube;
stringCube.apply("R U R' U' F2 D2");
assert(stringCube == vectorCube);
```
- **Verifies**: Tier 3 `Cube::apply(std::string_view)` delegates cleanly to Tier 2, producing identical states from raw algorithm text.

### Test 71: The Sexy Move 6-Cycle via Facade ($(R \; U \; R' \; U')^6 = I$)
```cpp
Cube sexyStringCube;
for (int i = 0; i < 6; ++i) {
  sexyStringCube.apply("R U R' U'");
}
assert(sexyStringCube == originalCube);
```
- **Verifies**: Repeating the 4-move string algorithm 6 times restores the solved cube state.

### Test 72: T-Permutation PLL Involution ($(T\text{-Perm})^2 = I$)
```cpp
Cube tPermCube;
constexpr std::string_view tPerm = "R U R' U' R' F R2 U' R' U' R U R' F'";
tPermCube.apply(tPerm);
assert(tPermCube != originalCube); // First application scrambles
tPermCube.apply(tPerm);
assert(tPermCube == originalCube); // Second application restores identity
```
- **Verifies**: The 14-move T-Permutation consists of two disjoint 2-cycles (corner swap and edge swap). Its group order is $\operatorname{lcm}(2, 2) = 2$, so applying it twice restores the identity cube state.

### Test 73: Algorithm Exception Handling for Malformed Tokens
```cpp
// Throws std::invalid_argument when parsing "R U INVALID U'"
```
- **Verifies**: `Notation::parseAlgorithm` fails fast and throws `std::invalid_argument` if any token in a multi-move sequence is malformed.

### Test 74: Hash Determinism for Identical States
```cpp
Cube hashCube1;
Cube hashCube2;
assert(std::hash<Cube>{}(hashCube1) == std::hash<Cube>{}(hashCube2));
```
- **Verifies**: `std::hash<Cube>` is deterministic. Two independently created cubes with identical sticker layouts always yield the exact same 64-bit hash code.

### Test 75: Hash Sensitivity (Collision Avoidance Across Different States)
```cpp
Cube turnedCube;
turnedCube.rotateUpClockwise();
assert(std::hash<Cube>{}(turnedCube) != std::hash<Cube>{}(hashCube1));
```
- **Verifies**: Altering even a single face rotation produces a completely different hash value via Golden Ratio bit scrambling, preventing hash collisions in the solver search space.

### Test 76: Container Integration with `std::unordered_set<Cube>`
```cpp
std::unordered_set<Cube> visitedCubes;
visitedCubes.insert(hashCube1);
assert(visitedCubes.size() == 1);

// Inserting duplicate state does not increase set size
visitedCubes.insert(hashCube2);
assert(visitedCubes.size() == 1);

// Inserting new state increments set size to 2
visitedCubes.insert(turnedCube);
assert(visitedCubes.size() == 2);
assert(visitedCubes.contains(turnedCube));
```
- **Verifies**: `Cube` seamlessly functions as a key in standard hash-based containers (`std::unordered_set`), enabling $O(1)$ duplicate rejection and fast visited-state tracking.

### Test 77: `solveBfs` on Already-Solved Cube (0-Move Base Case)
```cpp
Cube alreadySolvedCube;
auto solvedResult = Solver::solveBfs(alreadySolvedCube);
assert(solvedResult.has_value());
assert(solvedResult->empty());
```
- **Verifies**: Base-case short-circuit returns `has_value() == true` with an empty vector (0 moves needed) immediately without allocating search structures.

### Test 78: `solveBfs` Single-Move Scramble Inversion ($F \to F'$)
```cpp
Cube singleMoveCube;
singleMoveCube.apply(Move::F);
auto singleMoveSolution = Solver::solveBfs(singleMoveCube);
assert(singleMoveSolution.has_value());
assert(singleMoveSolution->size() == 1);
assert(singleMoveSolution->front() == Move::F_PRIME);
singleMoveCube.apply(*singleMoveSolution);
assert(singleMoveCube.isSolved());
```
- **Verifies**: Optimal depth-1 inversion: the BFS engine correctly identifies `F'` as the single inverse move and applying it restores `isSolved() == true`.

### Test 79: `solveBfs` Multi-Move Scramble & Optimal Shortest Path
```cpp
Cube multiMoveCube;
multiMoveCube.apply("R U R'");
auto multiMoveSolution = Solver::solveBfs(multiMoveCube, 4);
assert(multiMoveSolution.has_value());
assert(multiMoveSolution->size() == 3);
multiMoveCube.apply(*multiMoveSolution);
assert(multiMoveCube.isSolved());
```
- **Verifies**: Finds optimal 3-move sequence for $R \cdot U \cdot R'$, proving multi-level FIFO branch traversal and verifying that applying the sequence returns the cube to the solved state.

### Test 80: `solveBfs` Depth Exceeded Returns `std::nullopt`
```cpp
Cube deepScrambleCube;
deepScrambleCube.apply("R U R' U' F"); // 5 moves deep
auto shallowResult = Solver::solveBfs(deepScrambleCube, 3);
assert(!shallowResult.has_value());
```
- **Verifies**: When the shortest solution exceeds `maxDepth`, the solver gracefully terminates and returns `std::nullopt` rather than looping indefinitely or exhausting memory.

### Test 81: `solveBfs` Depth Zero Invariant
```cpp
Cube unsolvedDepthZero;
unsolvedDepthZero.apply(Move::U);
auto zeroDepthResult = Solver::solveBfs(unsolvedDepthZero, 0);
assert(!zeroDepthResult.has_value());
```
- **Verifies**: Guard clause ensures `maxDepth = 0` on an unsolved cube returns `std::nullopt` immediately without generating search nodes.

### Test 82: Scrambler Move Length Accuracy
```cpp
const auto scramble20 = Scrambler::generate(20, 12345);
assert(scramble20.size() == 20);
const auto scrambleShallow = Scrambler::generate(4, 12345);
assert(scrambleShallow.size() == 4);
const auto scrambleZero = Scrambler::generate(0);
assert(scrambleZero.empty());
```
- **Verifies**: `Scrambler::generate` yields vectors with the exact requested number of moves for boundary cases (0 moves, shallow 4-move scrambles, and full 20-move scrambles).

### Test 83: Scrambler Non-Consecutive Face Invariant
```cpp
for (std::size_t i = 1; i < scramble20.size(); ++i) {
    const std::size_t prevFace = static_cast<std::size_t>(scramble20[i - 1]) / 3;
    const std::size_t currFace = static_cast<std::size_t>(scramble20[i]) / 3;
    assert(prevFace != currFace);
}
```
- **Verifies**: Enforces the WCA regulation that no two consecutive turns may operate on the exact same face, preventing immediate cancellations or redundant rotations.

### Test 84: Scrambler Determinism with Explicit Seeds
```cpp
const auto seededTest1 = Scrambler::generate(15, 98765);
const auto seededTest2 = Scrambler::generate(15, 98765);
assert(seededTest1 == seededTest2);
```
- **Verifies**: Passing an explicit random seed configures the Mersenne Twister engine (`std::mt19937`) deterministically, ensuring reproducible test cases.

### Test 85: Scrambler WCA String Generation & Round-Trip
```cpp
const std::string scrambleStr = Scrambler::generateString(20, 42);
const std::vector<Move> parsedScrambleMoves = Notation::parseAlgorithm(scrambleStr);
assert(parsedScrambleMoves.size() == 20);
assert(parsedScrambleMoves == Scrambler::generate(20, 42));
```
- **Verifies**: `Scrambler::generateString` formats legal WCA strings that accurately parse back through `Notation::parseAlgorithm` without data loss.

### Test 86: 2D Net Visualizer (`Cube::printNet`) Stability
```cpp
Cube netCube;
netCube.apply(scrambleShallow);
netCube.printNet(false);
```
- **Verifies**: `Cube::printNet` renders the 6-face cross layout without exceptions, buffer overruns, or index crashes.

### Test 87: `solveIddfs` on Already-Solved Cube (0-Move Base Case)
```cpp
Cube iddfsSolvedCube;
auto iddfsSolvedRes = Solver::solveIddfs(iddfsSolvedCube, 4);
assert(iddfsSolvedRes.has_value());
assert(iddfsSolvedRes->empty());
```
- **Verifies**: Base-case short circuit returns an empty move vector for already-solved cubes without recursion.

### Test 88: `solveIddfs` 1-Move Scramble Inversion ($R \to R'$)
```cpp
Cube iddfsSingleCube;
iddfsSingleCube.apply(Move::R);
auto iddfsSingleSolution = Solver::solveIddfs(iddfsSingleCube, 4);
assert(iddfsSingleSolution.has_value() && iddfsSingleSolution->size() == 1);
assert(iddfsSingleSolution->front() == Move::R_PRIME);
iddfsSingleCube.apply(*iddfsSingleSolution);
assert(iddfsSingleCube.isSolved());
```
- **Verifies**: Depth-1 DFS inversion discovers the exact inverse move and restores the cube.

### Test 89: `solveIddfs` 3-Move Optimal Sequence
```cpp
Cube iddfsThreeCube;
iddfsThreeCube.apply("U F R");
auto iddfsThreeSolution = Solver::solveIddfs(iddfsThreeCube, 4);
assert(iddfsThreeSolution.has_value() && iddfsThreeSolution->size() == 3);
iddfsThreeCube.apply(*iddfsThreeSolution);
assert(iddfsThreeCube.isSolved());
```
- **Verifies**: Iterative deepening explores depths 1, 2, and 3, finding the optimal 3-move sequence for multi-axis scrambles.

### Test 90: `solveIddfs` Solves 5-Move Scramble Beyond BFS Limit
```cpp
Cube iddfsDeepCube;
iddfsDeepCube.apply("R U R' U' F"); // 5 moves deep
auto iddfsDeepSolution = Solver::solveIddfs(iddfsDeepCube, 5);
assert(iddfsDeepSolution.has_value() && iddfsDeepSolution->size() == 5);
iddfsDeepCube.apply(*iddfsDeepSolution);
assert(iddfsDeepCube.isSolved());
```
- **Verifies**: Solves a 5-move scramble that breaks past the BFS 4-move memory boundary with $O(d)$ linear memory.

### Test 91: `solveIddfs` Bounded Search Rejection
```cpp
Cube iddfsExceedCube;
iddfsExceedCube.apply("R U R' U' F"); // 5 moves deep
auto iddfsExceeded = Solver::solveIddfs(iddfsExceedCube, 3);
assert(!iddfsExceeded.has_value());
```
- **Verifies**: Returns `std::nullopt` when a scramble requires more moves than `maxDepth`.

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
PASS: Right Prime (R') changes state and cancels R (R * R' = I).
PASS: Four Right Prime turns restore every sticker position ((R')^4 = I).
PASS: Reverse cancellation verified (R' * R = I).
PASS: One Up Double (U2) turn changes the cube state.
PASS: Two Up Double turns restore every sticker position ((U2)^2 = I).
PASS: Up Double is identical to two clockwise turns (U2 == U * U).
PASS: Up Double is identical to two prime turns (U2 == U' * U').
PASS: One Down Double (D2) turn changes the cube state.
PASS: Two Down Double turns restore every sticker position ((D2)^2 = I).
PASS: Down Double is identical to two clockwise turns (D2 == D * D).
PASS: Down Double is identical to two prime turns (D2 == D' * D').
PASS: One Front Double (F2) turn changes the cube state.
PASS: Two Front Double turns restore every sticker position ((F2)^2 = I).
PASS: Front Double is identical to two clockwise turns (F2 == F * F).
PASS: Front Double is identical to two prime turns (F2 == F' * F').
PASS: One Back Double (B2) turn changes the cube state.
PASS: Two Back Double turns restore every sticker position ((B2)^2 = I).
PASS: Back Double is identical to two clockwise turns (B2 == B * B).
PASS: Back Double is identical to two prime turns (B2 == B' * B').
PASS: Disjoint opposite faces commute (F2 * B2 == B2 * F2).
PASS: One Left Double (L2) turn changes the cube state.
PASS: Two Left Double turns restore every sticker position ((L2)^2 = I).
PASS: Left Double is identical to two clockwise turns (L2 == L * L).
PASS: Left Double is identical to two prime turns (L2 == L' * L').
PASS: One Right Double (R2) turn changes the cube state.
PASS: Two Right Double turns restore every sticker position ((R2)^2 = I).
PASS: Right Double is identical to two clockwise turns (R2 == R * R).
PASS: Right Double is identical to two prime turns (R2 == R' * R').
PASS: Disjoint opposite faces commute (L2 * R2 == R2 * L2).
PASS: apply(Move::U) produces identical state to rotateUpClockwise().
PASS: apply(Move::F_PRIME) produces identical state to rotateFrontCounterClockwise().
PASS: apply(Move::R2) produces identical state to rotateRightDouble().
PASS: Six repetitions of (R U R' U') restore identity ((R U R' U')^6 = I).
PASS: parseMove correctly parses all 18 WCA move tokens.
PASS: moveToString correctly formats all 18 moves and round-trips.
PASS: parseMove throws std::invalid_argument on malformed tokens.
PASS: parseAlgorithm correctly parses sequences with variable whitespace.
PASS: formatAlgorithm produces canonical string and round-trips.
PASS: apply(const std::vector<Move>&) correctly matches individual rotations.
PASS: apply(std::string_view) produces identical state to vector apply.
PASS: Six repetitions of apply("R U R' U'") restore identity ((R U R' U')^6 = I).
PASS: Two repetitions of T-Permutation restore identity ((T-Perm)^2 = I).
PASS: parseAlgorithm throws std::invalid_argument on malformed algorithm string.
PASS: std::hash<Cube> is deterministic (identical states yield identical hashes).
PASS: std::hash<Cube> is sensitive (different states yield different hashes).
PASS: std::unordered_set<Cube> successfully stores states and rejects duplicates in O(1).
PASS: solveBfs returns empty move vector (0 moves) on already-solved cube.
PASS: solveBfs finds optimal 1-move solution (F') for F turn and restores solved state.
PASS: solveBfs finds optimal 3-move solution for 'R U R'' scramble and restores solved state.
PASS: solveBfs returns std::nullopt when scramble requires more moves than maxDepth.
PASS: solveBfs returns std::nullopt immediately when maxDepth is 0 for unsolved cube.
PASS: Scrambler::generate produces exact requested scramble lengths (0, 4, 20).
PASS: Scrambler strictly prevents consecutive moves on identical faces.
PASS: Scrambler is deterministic when initialized with identical seeds.
PASS: Scrambler::generateString round-trips accurately through Notation::parseAlgorithm.
PASS: Cube::printNet renders 2D net cleanly without error.
PASS: solveIddfs returns empty move vector (0 moves) on already-solved cube.
PASS: solveIddfs finds optimal 1-move solution (R') for R turn and restores solved state.
PASS: solveIddfs finds optimal 3-move solution for 'U F R' scramble.
PASS: solveIddfs successfully solves 5-move scramble with zero memory overhead.
PASS: solveIddfs returns std::nullopt when scramble exceeds allowed depth limit.
```

---

## 4. Modern C++ Test Syntax Guide: Working with `std::optional` in Tests

When writing assertions for functions that return modern C++ wrapper types (like `std::optional<std::vector<Move>>`), specific operators and idiomatic syntax patterns are used.

### 4.1 The `assert(...)` Macro
* Defined in `<cassert>`.
* Evaluates a boolean expression:
  * If `true`: execution proceeds silently.
  * If `false`: immediately aborts the program and prints the exact line number, file, and failing condition.
* The logical NOT operator (`!`) tests negative conditions:
  ```cpp
  assert(!singleMoveCube.isSolved()); // Asserts that the cube is NOT solved
  ```

### 4.2 Type Deduction with `auto`
```cpp
auto singleMoveSolution = Solver::solveBfs(singleMoveCube);
```
* Replaces the verbose type declaration `std::optional<std::vector<Move>>`.
* The compiler automatically deduces the exact type from the function signature, keeping tests clean while maintaining full compile-time type safety.

### 4.3 Namespace Scope Resolution (`::`)
```cpp
Solver::solveBfs(singleMoveCube);
```
* The double colon (`::`) identifies that `solveBfs` is declared inside `namespace Solver`, preventing naming collisions with other global functions.

### 4.4 Checking Presence with `.has_value()`
`std::optional` acts as a type-safe container that either holds a value or is empty (`std::nullopt`).
```text
           ┌───────────────────────────────┐
           │    std::optional (The Box)    │
           └───────────────┬───────────────┘
                           │
           ┌───────────────┴───────────────┐
           ▼                               ▼
  [ Box contains a Value ]        [ Box is Empty ]
    .has_value() == true           .has_value() == false
    "Solution discovered!"         "Search failed / nullopt"
```
* **Why check first?** Attempting to access an empty optional directly throws a `std::bad_optional_access` exception.
* Verifying success: `assert(singleMoveSolution.has_value());`
* Verifying expected failure: `assert(!shallowResult.has_value());`

### 4.5 Reaching Inside with the Arrow Operator (`->`)
The arrow operator (`->`) is formed by two characters: `-` (minus) and `>` (greater-than).
It visually represents **pointing into the wrapper box** to invoke methods on the object inside:

```text
singleMoveSolution ──( Reach inside )──▶ std::vector ──▶ .size()
        │                                    ▲
        └───────────────── -> ───────────────┘
```

* `singleMoveSolution` is the `std::optional` box. The box itself does not have a `.size()` or `.empty()` method.
* `singleMoveSolution->empty()` reaches into the box to invoke `std::vector::empty()`.
* `singleMoveSolution->size()` invokes `std::vector::size()`.
* `singleMoveSolution->front()` invokes `std::vector::front()`.

| Syntax | Target of Method Call | Valid? |
|---|---|:---:|
| `solution.has_value()` | Calls method on the `std::optional` wrapper itself | ✔ |
| `solution.size()` | Fails: `std::optional` has no `.size()` | ❌ |
| `solution->size()` | Points through wrapper to call `.size()` on `std::vector` | ✔ |
| `solution.value().size()` | Verbose equivalent of `solution->size()` | ✔ |

### 4.6 Retrieving the First Element with `.front()`
```cpp
assert(singleMoveSolution->front() == Move::F_PRIME);
```
* On `std::vector`, `.front()` returns a reference to the very first element (index `0`).
* It is the idiomatic, expressive equivalent of `(*singleMoveSolution)[0]`, reading cleanly in test assertions.

### 4.7 Unwrapping with the Dereference Operator (`*`)
```cpp
singleMoveCube.apply(*singleMoveSolution);
```
#### Why is the asterisk (`*`) required?
Look at the type requirement of `Cube::apply`:
```cpp
void Cube::apply(const std::vector<Move>& sequence);
```
* `Cube::apply` expects a bare **`std::vector<Move>`**.
* `singleMoveSolution` is of type **`std::optional<std::vector<Move>>`**.
* Passing `singleMoveSolution` directly causes a compiler error (`no matching function call`).
* The asterisk (`*`) is the **dereference operator**; it acts as a "box opener", unwrapping the `std::optional` and extracting the underlying `std::vector<Move>` so it can be passed to `Cube::apply`.
* `*singleMoveSolution` is the idiomatic shorthand for `singleMoveSolution.value()`.

