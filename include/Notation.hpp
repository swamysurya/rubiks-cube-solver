#ifndef NOTATION_HPP
#define NOTATION_HPP

#include "Move.hpp"
#include <string>
#include <string_view>
#include <vector>

// =============================================================================
// Namespace: Notation
// =============================================================================
// Provides utilities for converting between WCA (World Cube Association)
// string notation and strongly typed Move enums.
namespace Notation {

// Parses a single WCA move token (e.g., "R", "U'", "F2") into its corresponding Move enum.
// - Uses std::string_view for zero dynamic heap allocation.
// - Throws std::invalid_argument if the token is invalid, empty, or malformed.
Move parseMove(std::string_view token);

// Converts a Move enum back to its canonical WCA notation string literal (e.g., Move::U_PRIME -> "U'").
// - Returns a string_view pointing to static compile-time storage (zero heap allocation).
// - Marked noexcept because converting a valid enum to a string literal cannot fail.
std::string_view moveToString(Move move) noexcept;

// Parses a space-separated sequence of WCA moves (e.g. "R U R' U'") into a vector of Move enums.
// - Robust against variable whitespace (leading/trailing spaces, multiple spaces, tabs, newlines).
// - Throws std::invalid_argument if any token in the algorithm sequence is malformed.
std::vector<Move> parseAlgorithm(std::string_view alg);

// Formats a sequence of Move enums back into standard space-separated WCA notation (e.g. "R U R' U'").
std::string formatAlgorithm(const std::vector<Move>& moves);

} // namespace Notation

#endif // NOTATION_HPP

