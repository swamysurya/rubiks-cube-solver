# Rubik's Cube Solver — Learning Notes Index

All project learning notes have been organized into dedicated, topic-specific markdown files:

---

## 📚 Documentation Index

1. 📂 **[Git & Version Control Notes](git.md)**
   - Conventional commit message format (`feat`, `fix`, `docs`, `build`, `test`, `chore`)
   - Feature branching workflow standard practice (`feat/<feature-name>`)
   - Essential repository inspection commands (`status`, `diff`, `diff --cached`, `push`)
   - Release tagging and Semantic Versioning (`git tag -a v0.1.0`)
   - Productive Git aliases configuration (`st`, `co`, `cob`, `cm`, `lg`)
   - PowerShell terminal utilities

2. 📂 **[CMake & Build System Notes](cmake.md)**
   - Build-system generator concepts (CMake vs. compiler vs. make)
   - `CMakeLists.txt` full walkthrough (C++20 standard, warnings, include directories)
   - Why two separate executables exist (`rubiks_solver` vs `cube_tests`)
   - Build commands and Windows environment troubleshooting

3. 📂 **[Testing & CTest Notes](testing.md)**
   - Testing invariants and regression prevention
   - Complete breakdown of all 5 assertions in `CubeTests.cpp`
   - CTest execution and expected output

4. 📂 **[Rubik's Cube Code & Domain Logic Notes](cube-logic.md)**
   - 5-layer software architecture diagram
   - 54-sticker flat array representation (`std::array<Color, 54>`)
   - Unfolded 2D net diagram and global index formula: `face * 9 + row * 3 + col`
   - Face rotation matrix formula $(r, c) \to (c, 2 - r)$ and adjacent rim permutations for all 6 faces ($F, U, R, L, D, B$)
   - Inspection methods (`isSolved()`, `.at()` bounds safety, `print()`, C++20 `operator==`)
   - Counter-clockwise (prime) turns via the DRY principle ($X' = X^3$)
   - Deep-dive into Identity state ($I$), official WCA move notation, and group cancellation proofs ($X \cdot X' = I$)
