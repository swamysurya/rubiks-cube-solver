#include "Cube.hpp"
#include <iostream>

int main() {
    Cube cube;
     std::cout << "Cube solved: " << std::boolalpha << cube.isSolved() << '\n';
    return 0;
}