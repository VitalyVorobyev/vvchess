module;
#include <cstdint>
#include <iostream>
export module definitions;

export namespace def {

constexpr extern int BOARD_SIZE = 8;
constexpr extern int TOTAL_SQUARES = BOARD_SIZE * BOARD_SIZE;

enum class Color {white, black};
enum class Piece {pawn, bishop, knight, rook, queen, king};
using Bitboard = uint64_t;

class Square {
    const uint8_t m_row;
    const uint8_t m_col;
    const uint8_t m_index;
    public:
        Square(uint8_t row, uint8_t col) : 
            m_row(row), m_col(col), m_index(col + BOARD_SIZE * row) {}

        uint8_t row() const {return m_row;}
        uint8_t col() const {return m_col;}
        uint8_t index() const {return m_index;}
};

}

// export std::ostream& operator<<(std::ostream& os, const def::Color& c) {
//     if (c == def::Color::white) return os << "White";
//     return os << "Black";
// }
