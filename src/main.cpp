#include "Cube.hpp"
#include <iostream>

int main() {
  Cube cube;
  std::cout << "Cube solved: " << std::boolalpha << cube.isSolved() << '\n';

  std::cout << "=== Initial Cube State ===\n";
  cube.print();
  return 0;
}