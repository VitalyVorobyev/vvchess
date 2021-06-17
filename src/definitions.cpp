module;
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
export module definitions;

export namespace def {

using Size = uint8_t;

constexpr extern Size BOARD_SIZE = 8;
constexpr extern Size TOTAL_SQUARES = BOARD_SIZE * BOARD_SIZE;

// bool valid_index(Size idx) { return idx >= 0 && idx < BOARD_SIZE; }
bool valid_index(Size idx) { return idx < BOARD_SIZE; }
bool valid_index(Size row, Size col) { return valid_index(row) && valid_index(col); }

enum class Color {white, black};
enum class Piece {pawn, bishop, knight, rook, queen, king};
using Bitboard = uint64_t;

class Square {
    const Size m_row;
    const Size m_col;
    const Size m_index;

    void check_if_valid() const {
        if (!valid_index(m_row))
            throw std::runtime_error("Wrong row " + std::to_string(m_row));
        if (!valid_index(m_col))
            throw std::runtime_error("Wrong col " + std::to_string(m_col));
    }

    public:
        Square() = delete;
        Square(Size index) :
                m_row(index / BOARD_SIZE),
                m_col(index % BOARD_SIZE),
                m_index(index) { check_if_valid();}

        Square(Size row, Size col) : 
                m_row(row), m_col(col), m_index(col + BOARD_SIZE * row) {
            check_if_valid();
        }

        Size row() const {return m_row;}
        Size col() const {return m_col;}
        Size index() const {return m_index;}

        std::vector<Square> left_neibs() const {
            std::vector<Square> vec;
            for (Size col = m_col - 1; valid_index(col); --col) 
                vec.push_back({m_row, col});
            return vec;
        }

        std::vector<Square> top_neibs() const {
            std::vector<Square> vec;
            for (Size row = m_row + 1; valid_index(row); ++row) 
                vec.push_back({row, m_col});
            return vec;
        }

        std::vector<Square> bottom_neibs() const {
            std::vector<Square> vec;
            for (Size row = m_row - 1; valid_index(row); --row) 
                vec.push_back({row, m_col});
            return vec;
        }

        std::vector<Square> right_neibs() const {
            std::vector<Square> vec;
            for (Size col = m_col + 1; valid_index(col); ++col) 
                vec.push_back({m_row, col});
            return vec;
        }

        std::vector<Square> top_right_neibs() const {
            std::vector<Square> vec;
            for (Size col = m_col + 1, row = m_row + 1; valid_index(row, col); ++col, ++row) 
                vec.push_back({row, col});
            return vec;
        }

        std::vector<Square> top_left_neibs() const {
            std::vector<Square> vec;
            for (Size col = m_col - 1, row = m_row + 1; valid_index(row, col); --col, ++row) 
                vec.push_back({row, col});
            return vec;
        }

        std::vector<Square> bottom_left_neibs() const {
            std::vector<Square> vec;
            for (Size col = m_col - 1, row = m_row - 1; valid_index(row, col); --col, --row) 
                vec.push_back({row, col});
            return vec;
        }

        std::vector<Square> bottom_right_neibs() const {
            std::vector<Square> vec;
            for (Size col = m_col + 1, row = m_row - 1; valid_index(row, col); ++col, --row) 
                vec.push_back({row, col});
            return vec;
        }
};

}

// export std::ostream& operator<<(std::ostream& os, const def::Color& c) {
//     if (c == def::Color::white) return os << "White";
//     return os << "Black";
// }
