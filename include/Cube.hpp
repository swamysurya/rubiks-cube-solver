// Header guards prevent this header file from being included multiple times in
// the same translation unit, which would cause duplicate declaration compiler
// errors.
#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <cstddef>
#include <functional>
#include <string_view>
#include <vector>

#include "Move.hpp"

// =============================================================================
// Scoped Enumeration: Color
// =============================================================================
// Using 'enum class' provides strong type safety:
// - Colors cannot be implicitly converted to or compared with integers.
// - Each color corresponds to one of the six physical faces in a solved cube.
enum class Color {
  White,  // Face 0: Up (U)
  Yellow, // Face 1: Down (D)
  Red,    // Face 2: Front (F)
  Orange, // Face 3: Back (B)
  Blue,   // Face 4: Left (L)
  Green   // Face 5: Right (R)
};

// =============================================================================
// Class: Cube
// =============================================================================
// Represents a standard 3x3x3 Rubik's Cube.
// Encapsulates all 54 sticker states and provides methods to inspect, display,
// and rotate faces.
class Cube {
public:
  // -------------------------------------------------------------------------
  // 1. Compile-Time Constants
  // -------------------------------------------------------------------------
  // - FaceCount: A cube has exactly 6 faces.
  // - StickersPerFace: Each 3x3 face contains 9 stickers.
  // - StickerCount: 6 faces * 9 stickers = 54 total stickers.
  // - 'static constexpr' evaluates values at compile time across all Cube
  // instances.
  // - 'std::size_t' is an unsigned integer guaranteed to hold valid array sizes
  // and indices.
  static constexpr std::size_t FaceCount = 6;
  static constexpr std::size_t StickersPerFace = 9;
  static constexpr std::size_t StickerCount = FaceCount * StickersPerFace;

  // -------------------------------------------------------------------------
  // 2. Constructors
  // -------------------------------------------------------------------------
  // Initializes the cube in a standard solved state where all 9 stickers
  // on each face have that face's uniform color.
  Cube();

  // -------------------------------------------------------------------------
  // 3. State Queries & Inspection (const methods - do not modify state)
  // -------------------------------------------------------------------------
  // Checks whether the cube is currently in a solved state.
  // Returns true if every face has all 9 stickers sharing the exact same color.
  bool isSolved() const;

  // C++20 Defaulted Equality Operator:
  // Automatically generates member-wise equality (stickers == other.stickers)
  // and automatically synthesizes operator!= for free.
  bool operator==(const Cube &other) const = default;

  // Compares this cube's 54 stickers with another cube's 54 stickers.
  // Returns true if every single sticker has an identical color at the same
  // index.
  bool hasSameState(const Cube &other) const;

  // Returns the color of the sticker at the specified 0-based global index (0
  // to 53). Uses bounds checking (.at()) to prevent reading outside array
  // limits.
  Color getSticker(std::size_t index) const;

  // Prints all 6 faces to stdout as formatted 3x3 character grids (W, Y, R, O,
  // B, G).
  void print() const;

  // Prints the cube as an unfolded 2D cross layout:
  //         [Up]
  //  [Left] [Front] [Right] [Back]
  //        [Down]
  // Supports optional ANSI background color rendering for rich terminal display.
  void printNet(bool useColor = true) const;

  // -------------------------------------------------------------------------
  // 4. Cube Rotations & Manipulations (mutating methods - modify state in
  // place)
  // -------------------------------------------------------------------------
  // Rotates the Up face (Face 0, White) clockwise by 90 degrees.
  // Also shifts the top rows (row 0) of the 4 adjacent faces: Front -> Left ->
  // Back -> Right -> Front.
  void rotateUpClockwise();

  // Rotates the Down face (Face 1, Yellow) clockwise by 90 degrees.
  // Also shifts the bottom rows (row 2) of the 4 adjacent faces: Left -> Back
  // -> Right -> Front -> Left.
  void rotateDownClockwise();

  // Rotates the Front face (Face 2, Red) clockwise by 90 degrees.
  // Also shifts the adjacent border stickers across Up, Right, Down, and Left
  // faces.
  void rotateFrontClockwise();

  // Rotates the Back face (Face 3, Orange) clockwise by 90 degrees.
  // Also shifts the bordering rows/columns: Right -> Up (inverted) -> Left ->
  // Down (inverted) -> Right.
  void rotateBackClockwise();

  // Rotates the Right face (Face 5, Green) clockwise by 90 degrees.
  // Also shifts the bordering columns: Front -> Up -> Back (inverted) -> Down
  // (inverted) -> Front.
  void rotateRightClockwise();

  // Rotates the Left face (Face 4, Blue) clockwise by 90 degrees.
  // Also shifts the bordering columns: Up -> Front -> Down -> Back (inverted)
  // -> Up (inverted).
  void rotateLeftClockwise();

  // -------------------------------------------------------------------------
  // 5. Counter-Clockwise (Prime) Rotations (90 degrees counter-clockwise)
  // -------------------------------------------------------------------------
  // In Rubik's Cube group theory, each face rotation X has order 4 (X^4 =
  // Identity). The algebraic inverse X' (counter-clockwise) is equivalent to 3
  // clockwise turns: X' = X^3. Furthermore, X * X' = Identity (inverse
  // cancellation).

  // Rotates the Up face (Face 0, White) counter-clockwise (U')
  void rotateUpCounterClockwise();

  // Rotates the Down face (Face 1, Yellow) counter-clockwise (D')
  void rotateDownCounterClockwise();

  // Rotates the Front face (Face 2, Red) counter-clockwise (F')
  void rotateFrontCounterClockwise();

  // Rotates the Back face (Face 3, Orange) counter-clockwise (B')
  void rotateBackCounterClockwise();

  // Rotates the Left face (Face 4, Blue) counter-clockwise (L')
  void rotateLeftCounterClockwise();

  // Rotates the Right face (Face 5, Green) counter-clockwise (R')
  void rotateRightCounterClockwise();

  // -------------------------------------------------------------------------
  // 6. Double (Half-Turn) Rotations (180 degrees)
  // -------------------------------------------------------------------------
  // In WCA notation, a double turn (denoted with '2', e.g. U2) turns the face
  // 180 degrees. Because 180 = -180 (mod 360), direction does not matter.
  // Double moves are their own inverse (involutions): (X2)^2 = Identity.

  // Rotates the Up face (Face 0, White) 180 degrees (U2)
  void rotateUpDouble();

  // Rotates the Down face (Face 1, Yellow) 180 degrees (D2)
  void rotateDownDouble();

  // Rotates the Front face (Face 2, Red) 180 degrees (F2)
  void rotateFrontDouble();

  // Rotates the Back face (Face 3, Orange) 180 degrees (B2)
  void rotateBackDouble();

  // Rotates the Left face (Face 4, Blue) 180 degrees (L2)
  void rotateLeftDouble();

  // Rotates the Right face (Face 5, Green) 180 degrees (R2)
  void rotateRightDouble();

  // -------------------------------------------------------------------------
  // 7. Move Application & Dispatcher
  // -------------------------------------------------------------------------
  // Applies any standard WCA move (Clockwise, Prime, or Double) to the cube.
  void apply(Move move);

  // Applies an ordered sequence of standard WCA moves to the cube.
  void apply(const std::vector<Move> &moves);

  // Parses and executes a space-separated WCA algorithm string (e.g. "R U R'
  // U'"). Throws std::invalid_argument if any token in the algorithm string is
  // malformed.
  void apply(std::string_view algorithm);

  // Helper: Rotates the internal 3x3 grid of a specific face (0 to 5) clockwise
  // by 90 degrees. Applies the 2D coordinate transformation: (row, col) ->
  // (col, 2 - row).
  void rotateFaceClockwise(std::size_t face);

private:
  // -------------------------------------------------------------------------
  // 5. Private Internal State
  // -------------------------------------------------------------------------
  // Flat, fixed-size collection of exactly 54 sticker colors.
  // - Fixed compile-time size: Zero dynamic heap allocation, zero memory leaks.
  // - Contiguous memory layout: Cache-friendly and fast to copy during solver
  // search.
  // - Encapsulated in 'private': Callers cannot arbitrarily alter sticker
  // colors directly.
  std::array<Color, StickerCount> stickers;
};

// =============================================================================
// Standard Library Specialization: std::hash<Cube>
// =============================================================================
// Enables Cube instances to be used as keys in unordered hash-based containers
// such as std::unordered_set<Cube> and std::unordered_map<Cube, T>.
//
// Uses the Golden Ratio hash combining formula to combine all 54 stickers into
// a single high-entropy 64-bit hash code with O(1) performance and zero heap allocations.
namespace std {
template <>
struct hash<Cube> {
  std::size_t operator()(const Cube& cube) const noexcept {
    std::size_t seed = 0;
    for (std::size_t i = 0; i < Cube::StickerCount; ++i) {
      const auto val = static_cast<std::size_t>(cube.getSticker(i));
      seed ^= val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};
} // namespace std

#endif // CUBE_HPP
