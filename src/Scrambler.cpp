#include "Scrambler.hpp"
#include "Notation.hpp"
#include <random>

namespace Scrambler {

namespace {

// Returns the opposite (commuting) face index.
// In our standard numbering:
// - Up (0) <-> Down (1)      (0 ^ 1 == 1, 1 ^ 1 == 0)
// - Front (2) <-> Back (3)   (2 ^ 1 == 3, 3 ^ 1 == 2)
// - Left (4) <-> Right (5)   (4 ^ 1 == 5, 5 ^ 1 == 4)
constexpr std::size_t oppositeFace(std::size_t face) noexcept {
  return face ^ 1;
}

} // namespace

std::vector<Move> generate(std::size_t length, unsigned int seed) {
  std::vector<Move> scramble;
  if (length == 0) {
    return scramble;
  }
  scramble.reserve(length);

  // Initialize pseudorandom engine
  std::mt19937 rng(seed != 0 ? seed : std::random_device{}());
  std::uniform_int_distribution<std::size_t> faceDist(0, 5);
  std::uniform_int_distribution<std::size_t> modifierDist(0, 2);

  // Track the last two chosen faces to prevent cancellations
  int lastFace = -1;
  int secondLastFace = -1;

  for (std::size_t i = 0; i < length; ++i) {
    std::size_t face = 0;

    // Loop until we draw a face that does not cancel with preceding moves
    while (true) {
      face = faceDist(rng);

      // Rule 1: Cannot turn the exact same face consecutively (e.g. R followed by R')
      if (static_cast<int>(face) == lastFace) {
        continue;
      }

      // Rule 2: Cannot turn the same face separated only by its commuting opposite face
      // (e.g. R L R is redundant because R and L commute: R L R == R2 L)
      if (lastFace != -1 && secondLastFace != -1 &&
          lastFace == static_cast<int>(oppositeFace(face)) &&
          secondLastFace == static_cast<int>(face)) {
        continue;
      }

      break;
    }

    // Pick move variation: 0 = Clockwise, 1 = Prime, 2 = Double
    const std::size_t modifier = modifierDist(rng);
    const Move move = static_cast<Move>(face * 3 + modifier);

    scramble.push_back(move);

    secondLastFace = lastFace;
    lastFace = static_cast<int>(face);
  }

  return scramble;
}

std::string generateString(std::size_t length, unsigned int seed) {
  const std::vector<Move> moves = generate(length, seed);
  return Notation::formatAlgorithm(moves);
}

} // namespace Scrambler

