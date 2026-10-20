
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
    for (std::size_t i = 0; i < StickerCount; ++i) {
        switch (stickers[i]) {
            case Color::White:  std::cout << 'W'; break;
            case Color::Yellow: std::cout << 'Y'; break;
            case Color::Red:    std::cout << 'R'; break;
            case Color::Orange: std::cout << 'O'; break;
            case Color::Blue:   std::cout << 'B'; break;
            case Color::Green:  std::cout << 'G'; break;
        }

        if ((i + 1) % StickersPerFace == 0) {
            std::cout << '\n';
        } else {
            std::cout << ' ';
        }
    }
}

