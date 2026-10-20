# Rubik's Cube Solver — Architecture

## 1. Initial Design

The application will use C++ classes to separate cube state and cube operations from the command-line interface.

## 2. Cube Representation

A standard 3×3×3 Rubik's Cube has six faces and nine sticker positions per face, giving 54 sticker positions.

The initial representation will use:
- `enum class Color` to represent sticker colors.
- `std::array` to store a fixed number of sticker values.
- A `Cube` class to encapsulate the cube state and operations.

## 3. Face Index Convention

| Index | Face | Move notation |
|---|---|---|
| 0 | Up | U |
| 1 | Down | D |
| 2 | Front | F |
| 3 | Back | B |
| 4 | Left | L |
| 5 | Right | R |

Each face has nine sticker positions, indexed from 0 to 8 in row-major order.

## 4. Design Principles

- Keep the cube representation fixed-size.
- Encapsulate the state inside the `Cube` class.
- Define face and sticker indexing consistently.
- Test cube operations independently from the command-line interface.
- Verify that every implemented move preserves a valid cube state.

## 5. Future Development

The initial model will support cube initialization and state inspection. Face rotations, move sequences, validation, and solving algorithms will be added incrementally and tested separately.