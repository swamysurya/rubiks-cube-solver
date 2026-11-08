#include "Cube.hpp"
#include <iostream>

// =============================================================================
// 1. Constructor
// =============================================================================
Cube::Cube() {
  const std::array<Color, FaceCount> faceColors = {
      Color::White,  // Face 0: Up
      Color::Yellow, // Face 1: Down
      Color::Red,    // Face 2: Front
      Color::Orange, // Face 3: Back
      Color::Blue,   // Face 4: Left
      Color::Green   // Face 5: Right
  };

  // Initialize each of the 54 stickers to its respective face color.
  for (std::size_t face = 0; face < FaceCount; ++face) {
    for (std::size_t sticker = 0; sticker < StickersPerFace; ++sticker) {
      stickers[face * StickersPerFace + sticker] = faceColors[face];
    }
  }
}

// =============================================================================
// 2. State Queries & Inspection (const methods)
// =============================================================================
/*
The isSolved() method determines if the Rubik's Cube is in a solved state
logic : iterate through each face of the cube and check if all the stickers on
that face are of the same color
*/
bool Cube::isSolved() const {
  for (std::size_t face = 0; face < FaceCount; ++face) {
    const std::size_t start = face * StickersPerFace;
    const Color faceColor = stickers[start];

    for (std::size_t i = 1; i < StickersPerFace; ++i) {
      if (stickers[start + i] != faceColor) {
        return false;
      }
    }
  }
  return true;
}
/*
The hasSameState() method compares the state of the current cube with another
cube
logic : compare the sticker array of the current cube with the sticker array
of the other cube
*/
bool Cube::hasSameState(const Cube &other) const {
  return stickers == other.stickers;
}

/*
The getSticker() method returns the color of the sticker at the given index
logic : return the sticker at the given index
*/
Color Cube::getSticker(std::size_t index) const { return stickers.at(index); }

/*
The print() method prints the current state of the cube
logic : iterate through each face of the cube and print the stickers
*/
void Cube::print() const {
  for (std::size_t face = 0; face < FaceCount; ++face) {
    std::cout << "Face " << face << ":\n";

    for (std::size_t row = 0; row < 3; ++row) {
      for (std::size_t col = 0; col < 3; ++col) {
        const std::size_t index = face * StickersPerFace + row * 3 + col;

        switch (stickers[index]) {
        case Color::White:
          std::cout << 'W';
          break;
        case Color::Yellow:
          std::cout << 'Y';
          break;
        case Color::Red:
          std::cout << 'R';
          break;
        case Color::Orange:
          std::cout << 'O';
          break;
        case Color::Blue:
          std::cout << 'B';
          break;
        case Color::Green:
          std::cout << 'G';
          break;
        }
        std::cout << ' ';
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }
}

// =============================================================================
// 3. Cube Rotations & Manipulations (mutating methods)
// =============================================================================

void Cube::rotateUpClockwise() {
  // Save original state before modifying stickers
  const auto old = stickers;

  // 1. Rotate the Up face (Face 0) itself clockwise
  rotateFaceClockwise(0);

  // 2. Shift the top row (row 0) of the 4 adjacent faces:
  // Move Front top row to Left top row
  stickers[36] = old[18];
  stickers[37] = old[19];
  stickers[38] = old[20];

  // Move Left top row to Back top row
  stickers[27] = old[36];
  stickers[28] = old[37];
  stickers[29] = old[38];

  // Move Back top row to Right top row
  stickers[45] = old[27];
  stickers[46] = old[28];
  stickers[47] = old[29];

  // Move Right top row to Front top row
  stickers[18] = old[45];
  stickers[19] = old[46];
  stickers[20] = old[47];
}

void Cube::rotateDownClockwise() {
  // Save original state before modifying stickers
  const auto old = stickers;

  // 1. Rotate the Down face (Face 1) itself clockwise
  rotateFaceClockwise(1);

  // 2. Shift the bottom row (row 2) of the 4 adjacent faces:
  // Move Left bottom row to Back bottom row
  stickers[33] = old[42];
  stickers[34] = old[43];
  stickers[35] = old[44];

  // Move Back bottom row to Right bottom row
  stickers[51] = old[33];
  stickers[52] = old[34];
  stickers[53] = old[35];

  // Move Right bottom row to Front bottom row
  stickers[24] = old[51];
  stickers[25] = old[52];
  stickers[26] = old[53];

  // Move Front bottom row to Left bottom row
  stickers[42] = old[24];
  stickers[43] = old[25];
  stickers[44] = old[26];
}

void Cube::rotateFrontClockwise() {
  // Save original state before modifying stickers
  const auto old = stickers;

  // 1. Rotate the Front face (Face 2) itself clockwise
  rotateFaceClockwise(2);

  // 2. Shift the 12 bordering rim stickers:
  // Move Up bottom row to Right left column
  stickers[45] = old[6];
  stickers[48] = old[7];
  stickers[51] = old[8];

  // Move Right left column to Down top row
  stickers[9] = old[45];
  stickers[10] = old[48];
  stickers[11] = old[51];

  // Move Down top row to Left right column
  stickers[38] = old[9];
  stickers[41] = old[10];
  stickers[44] = old[11];

  // Move Left right column to Up bottom row
  stickers[6] = old[44];
  stickers[7] = old[41];
  stickers[8] = old[38];
}

void Cube::rotateRightClockwise() {
  // Save original state before modifying stickers
  const auto old = stickers;

  // 1. Rotate the Right face (Face 5) itself clockwise
  rotateFaceClockwise(5);

  // 2. Shift the bordering columns:
  // Move Front right column to Up right column
  stickers[2] = old[20];
  stickers[5] = old[23];
  stickers[8] = old[26];

  // Move Up right column to Back left column (inverted)
  stickers[27] = old[8];
  stickers[30] = old[5];
  stickers[33] = old[2];

  // Move Back left column to Down right column (inverted)
  stickers[11] = old[33];
  stickers[14] = old[30];
  stickers[17] = old[27];

  // Move Down right column to Front right column
  stickers[20] = old[11];
  stickers[23] = old[14];
  stickers[26] = old[17];
}

void Cube::rotateLeftClockwise() {
  // Save original state before modifying stickers
  const auto old = stickers;

  // 1. Rotate the Left face (Face 4) itself clockwise
  rotateFaceClockwise(4);

  // 2. Shift the bordering columns:
  // Move Up left column to Front left column
  stickers[18] = old[0];
  stickers[21] = old[3];
  stickers[24] = old[6];

  // Move Front left column to Down left column
  stickers[9] = old[18];
  stickers[12] = old[21];
  stickers[15] = old[24];

  // Move Down left column to Back right column (inverted)
  stickers[29] = old[15];
  stickers[32] = old[12];
  stickers[35] = old[9];

  // Move Back right column to Up left column (inverted)
  stickers[0] = old[35];
  stickers[3] = old[32];
  stickers[6] = old[29];
}

void Cube::rotateBackClockwise() {
  // Save original state before modifying stickers
  const auto old = stickers;

  // 1. Rotate the Back face (Face 3) itself clockwise
  rotateFaceClockwise(3);

  // 2. Shift the bordering rows/columns:
  // Move Right right column to Up top row
  stickers[0] = old[47];
  stickers[1] = old[50];
  stickers[2] = old[53];

  // Move Up top row to Left left column (inverted)
  stickers[36] = old[2];
  stickers[39] = old[1];
  stickers[42] = old[0];

  // Move Left left column to Down bottom row
  stickers[15] = old[36];
  stickers[16] = old[39];
  stickers[17] = old[42];

  // Move Down bottom row to Right right column (inverted)
  stickers[47] = old[17];
  stickers[50] = old[16];
  stickers[53] = old[15];
}

// =============================================================================
// 4. Counter-Clockwise (Prime) Rotations (Group Inverses: X' = X^3)
// =============================================================================
// By the cyclic group property of 90-degree rotations:
//   X^4 = I  =>  X * X^3 = I  =>  X' = X^3
// Implementing prime moves via 3 clockwise rotations adheres to the DRY
// principle (Don't Repeat Yourself), eliminates duplicate coordinate math, and
// guarantees complete mathematical consistency.

void Cube::rotateUpCounterClockwise() {
  rotateUpClockwise();
  rotateUpClockwise();
  rotateUpClockwise();
}

void Cube::rotateDownCounterClockwise() {
  rotateDownClockwise();
  rotateDownClockwise();
  rotateDownClockwise();
}

void Cube::rotateFrontCounterClockwise() {
  rotateFrontClockwise();
  rotateFrontClockwise();
  rotateFrontClockwise();
}

void Cube::rotateFaceClockwise(std::size_t face) {
  const std::size_t start = face * StickersPerFace;
  const auto old = stickers;

  // Standard 3x3 matrix clockwise rotation: (row, col) -> (col, 2 - row)
  for (std::size_t row = 0; row < 3; ++row) {
    for (std::size_t col = 0; col < 3; ++col) {
      const std::size_t oldIndex = start + row * 3 + col;
      const std::size_t newIndex = start + col * 3 + (2 - row);
      stickers[newIndex] = old[oldIndex];
    }
  }
}
