
//These prevent the header from being included multiple times in a way that causes duplicate declarations in the same translation unit.
#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <cstddef>

enum class Color {
    White,
    Yellow,
    Red,
    Orange,
    Blue,
    Green
};

class Cube {
public:
    // std::size_t is an unsigned integer type commonly used for sizes and indexing.
    static constexpr std::size_t FaceCount = 6;
    static constexpr std::size_t StickersPerFace = 9;
    static constexpr std::size_t StickerCount =
        FaceCount * StickersPerFace;

    Cube();

    void print() const;

    Color getSticker(std::size_t index) const;
    
    bool isSolved() const;  

private:
    // Creates a fixed-size collection of 54 colors. It is not dynamically resized.
    std::array<Color, StickerCount> stickers;
};

#endif
