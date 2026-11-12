#include "Cube.hpp"
#include "Notation.hpp"
#include "Scrambler.hpp"
#include "Solver.hpp"

#include <chrono>
#include <iostream>
#include <string>

namespace {

void printHeader() {
  std::cout << "\n======================================================\n";
  std::cout << "             RUBIK'S CUBE SOLVER (C++20)              \n";
  std::cout << "======================================================\n";
}

void printStatus(const Cube& cube) {
  std::cout << "\nCube Status: ";
  if (cube.isSolved()) {
    std::cout << "\033[32m[ SOLVED ]\033[0m\n";
  } else {
    std::cout << "\033[33m[ SCRAMBLED ]\033[0m\n";
  }
}

void printMenu(bool useColor) {
  std::cout << "\n-------------------- Menu --------------------\n";
  std::cout << " [1] Display Cube (2D Unfolded Net)\n";
  std::cout << " [2] Apply Custom Algorithm / Moves (e.g. \"R U R' U'\")\n";
  std::cout << " [3] Generate & Apply Shallow Scramble (1-4 moves)\n";
  std::cout << " [4] Generate & Apply Official Scramble (20 moves)\n";
  std::cout << " [5] Solve Cube with BFS Solver\n";
  std::cout << " [6] Reset Cube to Solved State\n";
  std::cout << " [7] Toggle Terminal Colors (Currently: " << (useColor ? "ON" : "OFF") << ")\n";
  std::cout << " [0] Exit Application\n";
  std::cout << "----------------------------------------------\n";
  std::cout << "Enter your choice: ";
}

} // namespace

int main() {
  Cube cube;
  bool useColor = true;
  std::string choice;

  printHeader();

  while (true) {
    printStatus(cube);
    printMenu(useColor);

    if (!std::getline(std::cin, choice)) {
      break;
    }

    if (choice == "0" || choice == "exit" || choice == "q") {
      std::cout << "\nThank you for using Rubik's Cube Solver. Goodbye!\n";
      break;
    }

    if (choice == "1") {
      std::cout << "\n=== Unfolded 2D Cube Net ===\n\n";
      cube.printNet(useColor);
    } else if (choice == "2") {
      std::cout << "\nEnter move sequence (e.g. \"R U R' U'\" or \"F2 D' L\"): ";
      std::string alg;
      if (std::getline(std::cin, alg) && !alg.empty()) {
        try {
          cube.apply(alg);
          std::cout << "\nApplied algorithm: " << alg << '\n';
        } catch (const std::invalid_argument& ex) {
          std::cout << "\n\033[31mError: " << ex.what() << "\033[0m\n";
        }
      }
    } else if (choice == "3") {
      std::cout << "Enter scramble length (1 to 4 moves) [default: 3]: ";
      std::string lenStr;
      std::size_t len = 3;
      if (std::getline(std::cin, lenStr) && !lenStr.empty()) {
        try {
          len = std::stoul(lenStr);
          if (len > 4) len = 4;
        } catch (...) {
          len = 3;
        }
      }
      const std::string scramble = Scrambler::generateString(len);
      cube.apply(scramble);
      std::cout << "\nGenerated Shallow Scramble (" << len << " moves): " << scramble << '\n';
      std::cout << "\n=== Cube State After Scramble ===\n\n";
      cube.printNet(useColor);
    } else if (choice == "4") {
      const std::string scramble = Scrambler::generateString(20);
      cube.apply(scramble);
      std::cout << "\nGenerated Official WCA Scramble (20 moves):\n" << scramble << '\n';
      std::cout << "\n=== Cube State After Scramble ===\n\n";
      cube.printNet(useColor);
    } else if (choice == "5") {
      if (cube.isSolved()) {
        std::cout << "\nCube is already solved! No moves needed.\n";
        continue;
      }

      std::cout << "\nSearching for optimal solution with BFS (maxDepth = 4)...\n";
      const auto startTime = std::chrono::steady_clock::now();
      const auto solution = Solver::solveBfs(cube, 4);
      const auto endTime = std::chrono::steady_clock::now();
      const auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

      if (solution.has_value()) {
        const std::string solutionStr = Notation::formatAlgorithm(*solution);
        std::cout << "\n\033[32m[ SOLUTION FOUND! ]\033[0m\n";
        std::cout << "Moves (" << solution->size() << " moves): " << solutionStr << '\n';
        std::cout << "Search Time: " << elapsedMs << " ms\n";

        std::cout << "\nApply solution to restore cube? (Y/n): ";
        std::string confirm;
        std::getline(std::cin, confirm);
        if (confirm.empty() || confirm == "y" || confirm == "Y") {
          cube.apply(*solution);
          std::cout << "\nCube restored to solved state!\n";
          cube.printNet(useColor);
        }
      } else {
        std::cout << "\n\033[33m[ NO SOLUTION FOUND WITHIN 4 MOVES ]\033[0m\n";
        std::cout << "Search Time: " << elapsedMs << " ms\n";
        std::cout << "This scramble requires more than 4 moves to solve.\n";
        std::cout << "(Pure BFS is bounded to depth 4 to prevent out-of-memory crashes).\n";
      }
    } else if (choice == "6") {
      cube = Cube{};
      std::cout << "\nCube reset to solved identity state.\n";
    } else if (choice == "7") {
      useColor = !useColor;
      std::cout << "\nTerminal colors toggled: " << (useColor ? "ON" : "OFF") << '\n';
    } else {
      std::cout << "\nInvalid choice. Please select from the menu options.\n";
    }
  }

  return 0;
}
