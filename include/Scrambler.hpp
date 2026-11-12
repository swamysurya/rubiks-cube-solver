#ifndef SCRAMBLER_HPP
#define SCRAMBLER_HPP

#include "Move.hpp"
#include <cstddef>
#include <string>
#include <vector>

// =============================================================================
// Namespace: Scrambler
// =============================================================================
// Generates official-compliant random Rubik's Cube scrambles.
// Prevents redundant moves (same face consecutively) and opposite-face cancellations.
namespace Scrambler {

// Generates a sequence of random Move enums of the requested length.
//
// Parameters:
// - length: Number of moves to generate (default: 20, standard WCA competition length).
// - seed: Optional random seed for deterministic/reproducible generation (0 uses random_device).
//
// Returns:
// - A std::vector<Move> containing non-canceling random turns.
std::vector<Move> generate(std::size_t length = 20, unsigned int seed = 0);

// Generates a random scramble and formats it directly as a standard WCA string
// (e.g. "R U2 F' L B2 D").
std::string generateString(std::size_t length = 20, unsigned int seed = 0);

} // namespace Scrambler

#endif // SCRAMBLER_HPP

