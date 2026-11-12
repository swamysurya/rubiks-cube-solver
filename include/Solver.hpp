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

// Finds the optimal (shortest) solution sequence using Iterative Deepening Depth-First
// Search (IDDFS) with move-pruning rules.
//
// Combines the optimality guarantee of BFS with the minimal memory footprint of DFS (O(d)).
// Solves deeper scrambles (up to depth 6-7) without risking out-of-memory crashes.
//
// Parameters:
// - startCube: The initial (scrambled) cube configuration to solve.
// - maxDepth:  Maximum depth to search iteratively (default: 6).
//
// Returns:
// - A vector of Move enums representing the shortest sequence from start to solved state.
// - An empty vector if the cube is already in a solved state.
// - std::nullopt if no solution exists within maxDepth.
std::optional<std::vector<Move>> solveIddfs(const Cube& startCube, std::size_t maxDepth = 6);

} // namespace Solver

#endif // SOLVER_HPP

