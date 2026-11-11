#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Cube.hpp"
#include "Move.hpp"
#include <cstddef>
#include <optional>
#include <vector>

// =============================================================================
// Namespace: Solver
// =============================================================================
// Provides algorithmic search routines to solve arbitrary Rubik's Cube states.
namespace Solver {

// Finds the optimal (shortest) solution sequence to restore a cube to solved state
// using Breadth-First Search (BFS).
//
// Parameters:
// - startCube: The initial (scrambled) cube configuration to solve.
// - maxDepth:  Maximum number of moves to explore (default: 4). Prevents out-of-memory.
//
// Returns:
// - A vector of Move enums representing the shortest sequence from start to solved state.
// - An empty vector if the cube is already in a solved state.
// - std::nullopt if no solution exists within maxDepth.
std::optional<std::vector<Move>> solveBfs(const Cube& startCube, std::size_t maxDepth = 4);

} // namespace Solver

#endif // SOLVER_HPP

