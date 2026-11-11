#include "Solver.hpp"

#include <queue>
#include <unordered_set>

namespace Solver {

namespace {

// Internal search node bundling a cube configuration with the move path
// that produced it from the starting scramble.
struct SearchNode {
  Cube cube;
  std::vector<Move> path;
};

} // namespace

std::optional<std::vector<Move>> solveBfs(const Cube& startCube, std::size_t maxDepth) {
  // Base Case: The cube is already in a solved state (0 moves required).
  if (startCube.isSolved()) {
    return std::vector<Move>{};
  }

  // If maximum exploration depth is 0 and the cube isn't solved, no solution exists.
  if (maxDepth == 0) {
    return std::nullopt;
  }

  // FIFO Queue storing states to explore level by level.
  std::queue<SearchNode> frontier;

  // Hash set storing visited states to prevent infinite loops and duplicate exploration.
  std::unordered_set<Cube> visited;

  // Initialize search with the starting configuration.
  frontier.push({startCube, {}});
  visited.insert(startCube);

  while (!frontier.empty()) {
    SearchNode current = std::move(frontier.front());
    frontier.pop();

    // If the next level of moves would exceed maxDepth, do not expand further.
    if (current.path.size() >= maxDepth) {
      continue;
    }

    // Branch across all 18 standard WCA face turns.
    for (std::size_t i = 0; i < MoveCount; ++i) {
      const Move move = static_cast<Move>(i);

      Cube nextCube = current.cube;
      nextCube.apply(move);

      // Early Goal Check: Test if applying this move immediately solves the cube.
      if (nextCube.isSolved()) {
        std::vector<Move> solution = current.path;
        solution.push_back(move);
        return solution;
      }

      // If this state has not been seen yet, record it and enqueue for next level.
      if (!visited.contains(nextCube)) {
        visited.insert(nextCube);

        std::vector<Move> nextPath = current.path;
        nextPath.push_back(move);
        frontier.push({std::move(nextCube), std::move(nextPath)});
      }
    }
  }

  // No solution found within the allowed maximum depth.
  return std::nullopt;
}

} // namespace Solver

