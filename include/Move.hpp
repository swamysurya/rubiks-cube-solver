#ifndef MOVE_HPP
#define MOVE_HPP

#include <cstddef>
#include <cstdint>

// =============================================================================
// Strongly typed enum representing all 18 standard WCA face moves.
// =============================================================================
// Underlying type is std::uint8_t:
// - Consumes exactly 1 byte per move (cache-friendly).
// - Enables compact storage in move sequences and solver search nodes.

enum class Move : std::uint8_t {
  // Up Face (0)
  U,
  U_PRIME,
  U2,

  // Down Face (1)
  D,
  D_PRIME,
  D2,

  // Front Face (2)
  F,
  F_PRIME,
  F2,

  // Back Face (3)
  B,
  B_PRIME,
  B2,

  // Left Face (4)
  L,
  L_PRIME,
  L2,

  // Right Face (5)
  R,
  R_PRIME,
  R2
};

// Total number of discrete face turns in standard 3x3 Rubik's Cube metric (HTM:
// Half Turn Metric)
inline constexpr std::size_t MoveCount = 18;

#endif // MOVE_HPP
