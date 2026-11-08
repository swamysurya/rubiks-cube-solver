# Rubik's Cube Code & Domain Logic — Learning Notes

## 1. Architecture & Codebase Layout

### The 5 Modular Layers
```text
 [ User / Command-Line Interface (main.cpp) ]
                     │
                     ▼
 [ Notation & Scramble Layer (Notation.hpp / Scrambler.hpp) ]
   - Parses inputs like "R U R' U'"
   - Generates random 20-move scrambles
                     │
                     ▼
 [ Core Cube Model (Cube.hpp / Cube.cpp) ]
   - 54-sticker flat array representation
   - Face turns (U, D, F, B, L, R and inverses)
   - Solved-state detection (isSolved())
                     ▲
                     │ (queries state & branches moves)
                     ▼
 [ Solver Engine (Solver.hpp / Solver.cpp) ]
   - Search Algorithms (BFS, IDDFS, or Two-Phase / Kociemba)
   - Finds solution sequences to restore solved state
```

### Directory Responsibilities
- `include/`: Header files (`.hpp`) containing types, constants, and function declarations. Separates *interface* from *implementation*.
- `src/`: Source files (`.cpp`) implementing the classes and main program.
- `tests/`: Automated unit tests verifying domain logic.
- `docs/`: Technical specifications, design notes, and learning logs.
- `build/`: Out-of-source compilation artifacts (git-ignored).

---

## 2. Cube Representation & Data Structures

### Scoped Enumeration (`enum class Color`)
```cpp
enum class Color { White, Yellow, Red, Orange, Blue, Green };
```
- `enum class` provides strong type safety (cannot be implicitly converted to integers).

### Fixed-Size Array (`std::array`)
```cpp
static constexpr std::size_t FaceCount = 6;
static constexpr std::size_t StickersPerFace = 9;
static constexpr std::size_t StickerCount = FaceCount * StickersPerFace; // 54

std::array<Color, StickerCount> stickers;
```
- **Flat array advantage**: Cache-friendly, contiguous memory, fixed size, minimal copying overhead during high-speed tree search.

### Face Ordering and Index Ranges
| Face Index | Face Name | Notation | Default Color | Index Range |
| :---: | :---: | :---: | :---: | :---: |
| **0** | Up | **U** | White | 0 – 8 |
| **1** | Down | **D** | Yellow | 9 – 17 |
| **2** | Front | **F** | Red | 18 – 26 |
| **3** | Back | **B** | Orange | 27 – 35 |
| **4** | Left | **L** | Blue | 36 – 44 |
| **5** | Right | **R** | Green | 45 – 53 |

---

## 3. Coordinate & Indexing Mathematics

### 2D Unfolded Net View
```text
                     +------------+
                     |  UP (0)    |
                     |  0   1   2 |
                     |  3   4   5 |
                     |  6   7   8 |
      +------------+ +------------+ +------------+ +------------+
      |  LEFT (4)  | | FRONT (2)  | | RIGHT (5)  | |  BACK (3)  |
      | 36  37  38 | | 18  19  20 | | 45  46  47 | | 27  28  29 |
      | 39  40  41 | | 21  22  23 | | 48  49  50 | | 30  31  32 |
      | 42  43  44 | | 24  25  26 | | 51  52  53 | | 33  34  35 |
      +------------+ +------------+ +------------+ +------------+
                     |  DOWN (1)  |
                     |  9  10  11 |
                     | 12  13  14 |
                     | 15  16  17 |
                     +------------+
```

### Formula for Sticker Indices
For any given `face` ($0 \le \text{face} < 6$), `row` ($0 \le \text{row} < 3$), and `col` ($0 \le \text{col} < 3$):
- **Local Face Offset**: $\text{localIndex} = \text{row} \times 3 + \text{col}$
- **Global Index**: $\text{globalIndex} = (\text{face} \times 9) + (\text{row} \times 3) + \text{col}$

---

## 4. Cube Rotations — The Front Clockwise Move ($F$)

A physical face rotation consists of **two distinct operations**:
1. Rotating the 9 stickers on the face itself by $90^\circ$ clockwise.
2. Cycling the 12 stickers on the adjacent rim faces.

### Operation 1: 3×3 Face Grid Rotation
Formula mapping clockwise: $(r, c) \to (c, 2 - r)$

```text
Old 3x3 Grid:       Rotated Clockwise:
0  1  2             6  3  0
3  4  5    ───>     7  4  1
6  7  8             8  5  2
```

In code (`rotateFaceClockwise(std::size_t face)`):
```cpp
const std::size_t start = face * StickersPerFace;
const auto old = stickers;

for (std::size_t row = 0; row < 3; ++row) {
    for (std::size_t col = 0; col < 3; ++col) {
        const std::size_t oldIndex = start + row * 3 + col;
        const std::size_t newIndex = start + col * 3 + (2 - row);
        stickers[newIndex] = old[oldIndex];
    }
}
```
*Notice: The center sticker at offset 4 ($r=1, c=1$) maps to $(1, 2-1) = 4$, remaining stationary.*

### Operation 2: Adjacent Rim Permutations for $F$ Turn (Front)
When the Front face turns clockwise, the bordering rows/columns on adjacent faces shift in a 4-cycle:
- **Up (`U`) bottom row** $\to$ **Right (`R`) left column**:
  - `stickers[45] = old[6]`
  - `stickers[48] = old[7]`
  - `stickers[51] = old[8]`
- **Right (`R`) left column** $\to$ **Down (`D`) top row**:
  - `stickers[9]  = old[45]`
  - `stickers[10] = old[48]`
  - `stickers[11] = old[51]`
- **Down (`D`) top row** $\to$ **Left (`L`) right column**:
  - `stickers[38] = old[9]`
  - `stickers[41] = old[10]`
  - `stickers[44] = old[11]`
- **Left (`L`) right column** $\to$ **Up (`U`) bottom row**:
  - `stickers[6] = old[44]`
  - `stickers[7] = old[41]`
  - `stickers[8] = old[38]`

### Operation 3: Adjacent Rim Permutations for $U$ Turn (Up)
When looking down at the Up face, a clockwise turn shifts the top row (row 0) across all 4 surrounding faces in order:
- **Front (`F`) top row** $\to$ **Left (`L`) top row**:
  - `stickers[36] = old[18]`
  - `stickers[37] = old[19]`
  - `stickers[38] = old[20]`
- **Left (`L`) top row** $\to$ **Back (`B`) top row**:
  - `stickers[27] = old[36]`
  - `stickers[28] = old[37]`
  - `stickers[29] = old[38]`
- **Back (`B`) top row** $\to$ **Right (`R`) top row**:
  - `stickers[45] = old[27]`
  - `stickers[46] = old[28]`
  - `stickers[47] = old[29]`
- **Right (`R`) top row** $\to$ **Front (`F`) top row**:
  - `stickers[18] = old[45]`
  - `stickers[19] = old[46]`
  - `stickers[20] = old[47]`

### Operation 4: Adjacent Rim Permutations for $R$ Turn (Right)
When looking at the Right face, turning it clockwise rotates columns on the 4 bordering faces:
- **Front (`F`) right column** $\to$ **Up (`U`) right column**:
  - `stickers[2] = old[20]`
  - `stickers[5] = old[23]`
  - `stickers[8] = old[26]`
- **Up (`U`) right column** $\to$ **Back (`B`) left column (inverted)**:
  - `stickers[27] = old[8]`
  - `stickers[30] = old[5]`
  - `stickers[33] = old[2]`
- **Back (`B`) left column** $\to$ **Down (`D`) right column (inverted)**:
  - `stickers[11] = old[33]`
  - `stickers[14] = old[30]`
  - `stickers[17] = old[27]`
- **Down (`D`) right column** $\to$ **Front (`F`) right column**:
  - `stickers[20] = old[11]`
  - `stickers[23] = old[14]`
  - `stickers[26] = old[17]`

### Operation 5: Adjacent Rim Permutations for $L$ Turn (Left)
When looking at the Left face, turning it clockwise shifts vertical columns on the 4 bordering faces:
- **Up (`U`) left column** $\to$ **Front (`F`) left column**:
  - `stickers[18] = old[0]`
  - `stickers[21] = old[3]`
  - `stickers[24] = old[6]`
- **Front (`F`) left column** $\to$ **Down (`D`) left column**:
  - `stickers[9]  = old[18]`
  - `stickers[12] = old[21]`
  - `stickers[15] = old[24]`
- **Down (`D`) left column** $\to$ **Back (`B`) right column (inverted)**:
  - `stickers[29] = old[15]`
  - `stickers[32] = old[12]`
  - `stickers[35] = old[9]`
- **Back (`B`) right column** $\to$ **Up (`U`) left column (inverted)**:
  - `stickers[0]  = old[35]`
  - `stickers[3]  = old[32]`
  - `stickers[6]  = old[29]`

### Operation 6: Adjacent Rim Permutations for $D$ Turn (Down)
When looking at the Down face, turning it clockwise shifts the bottom row (row 2) across the 4 bordering faces:
- **Left (`L`) bottom row** $\to$ **Back (`B`) bottom row**:
  - `stickers[33] = old[42]`
  - `stickers[34] = old[43]`
  - `stickers[35] = old[44]`
- **Back (`B`) bottom row** $\to$ **Right (`R`) bottom row**:
  - `stickers[51] = old[33]`
  - `stickers[52] = old[34]`
  - `stickers[53] = old[35]`
- **Right (`R`) bottom row** $\to$ **Front (`F`) bottom row**:
  - `stickers[24] = old[51]`
  - `stickers[25] = old[52]`
  - `stickers[26] = old[53]`
- **Front (`F`) bottom row** $\to$ **Left (`L`) bottom row**:
  - `stickers[42] = old[24]`
  - `stickers[43] = old[25]`
  - `stickers[44] = old[26]`

### Operation 7: Adjacent Rim Permutations for $B$ Turn (Back)
When looking at the Back face, turning it clockwise shifts bordering rows/columns across 4 faces:
- **Right (`R`) right column** $\to$ **Up (`U`) top row**:
  - `stickers[0] = old[47]`
  - `stickers[1] = old[50]`
  - `stickers[2] = old[53]`
- **Up (`U`) top row** $\to$ **Left (`L`) left column (inverted)**:
  - `stickers[36] = old[2]`
  - `stickers[39] = old[1]`
  - `stickers[42] = old[0]`
- **Left (`L`) left column** $\to$ **Down (`D`) bottom row**:
  - `stickers[15] = old[36]`
  - `stickers[16] = old[39]`
  - `stickers[17] = old[42]`
- **Down (`D`) bottom row** $\to$ **Right (`R`) right column (inverted)**:
  - `stickers[47] = old[17]`
  - `stickers[50] = old[16]`
  - `stickers[53] = old[15]`

---

## 5. State Inspection and Helpers

- **`bool operator==(const Cube& other) const = default;` (C++20)**:
  - Defaulted equality comparison. Compares all 54 stickers member-wise.
  - Automatically generates `operator!=` for free.
- **`getSticker(index)`**: Uses `stickers.at(index)` for safe bounds-checked access (`std::out_of_range`).
- **`isSolved()`**: Verifies that each face $f \in [0, 5]$ has all 8 remaining stickers matching its first sticker:
  ```cpp
  bool Cube::isSolved() const {
      for (std::size_t face = 0; face < FaceCount; ++face) {
          const std::size_t start = face * StickersPerFace;
          const Color faceColor = stickers[start];
          for (std::size_t i = 1; i < StickersPerFace; ++i) {
              if (stickers[start + i] != faceColor) return false;
          }
      }
      return true;
  }
  ```
- **`hasSameState(const Cube& other)`**: Compares arrays directly (`stickers == other.stickers`).
- **`print()`**: Formats each face into a 3×3 grid using single characters (`W`, `Y`, `R`, `O`, `B`, `G`).

---

## 6. Counter-Clockwise (Prime) Rotations & Group Inverses

### The Group Theory Inverse Property
In the Rubik's Cube rotation group, every 90° face rotation $X \in \{U, D, F, B, L, R\}$ is an element of order 4:
$$X^4 = I \quad (\text{Identity State})$$

Multiplying both sides by the group inverse $X^{-1}$ (denoted as $X'$ or "X-prime" in WCA notation):
$$X^{-1} \cdot X^4 = X^{-1} \cdot I$$
$$X^3 = X'$$

Thus:
$$\mathbf{X' = X^3}$$

### DRY Engineering Principle (Don't Repeat Yourself)
Instead of hand-coding another set of complex coordinate transformations in reverse order (which risks index typos and duplicates code), we implement each counter-clockwise turn by calling its clockwise counterpart 3 times:

```cpp
void Cube::rotateUpCounterClockwise() {
  rotateUpClockwise();
  rotateUpClockwise();
  rotateUpClockwise();
}
```

### Mathematical Invariants & Cancellation
Prime turns satisfy two foundational invariants:
1. **Inverse Cancellation**:
   $$X \cdot X' = I \quad \text{and} \quad X' \cdot X = I$$
   Executing a face move followed by its inverse returns the cube strictly to its previous state.
2. **Order 4 Invariant**:
   $$(X')^4 = I$$
   Four consecutive counter-clockwise turns restore the original state.


