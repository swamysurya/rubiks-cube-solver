
#include "Cube.hpp"
#include <iostream>

//The Cube:: prefix means this constructor belongs to the Cube class.
Cube::Cube() {
    const std::array<Color, FaceCount> faceColors = {
        Color::White,   // Up
        Color::Yellow,  // Down
        Color::Red,     // Front
        Color::Orange,  // Back
        Color::Blue,    // Left
        Color::Green    // Right
    };


    for (std::size_t face = 0; face < FaceCount; ++face) {
        for (std::size_t sticker = 0; sticker < StickersPerFace; ++sticker) {
            stickers[face * StickersPerFace + sticker] = faceColors[face];
        }
    }
}


void Cube::print() const {
    for (std::size_t face = 0; face < FaceCount; ++face) {
        std::cout << "Face " << face << ":\n";

        for (std::size_t row = 0; row < 3; ++row) {
            for (std::size_t col = 0; col < 3; ++col) {
                const std::size_t index =
                    face * StickersPerFace + row * 3 + col;

                switch (stickers[index]) {
                    case Color::White:  std::cout << 'W'; break;
                    case Color::Yellow: std::cout << 'Y'; break;
                    case Color::Red:    std::cout << 'R'; break;
                    case Color::Orange: std::cout << 'O'; break;
                    case Color::Blue:   std::cout << 'B'; break;
                    case Color::Green:  std::cout << 'G'; break;
                }
                std::cout << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
}

Color Cube::getSticker(std::size_t index) const {
    return stickers.at(index);
}


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
