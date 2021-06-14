module;
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <vector>
export module definitions;

export namespace def {

constexpr extern size_t BOARD_SIZE = 8;
constexpr extern size_t TOTAL_SQUARES = BOARD_SIZE * BOARD_SIZE;

bool valid_index(size_t idx) { return idx < BOARD_SIZE; }

enum class Color {white, black};
enum class Piece {pawn, bishop, knight, rook, queen, king};
using Bitboard = uint64_t;

class Square {
    const size_t m_row;
    const size_t m_col;
    const size_t m_index;

    void check_if_valid() const {
        if (!valid_index(m_row))
            throw std::runtime_error("Wrong row " + std::to_string(m_row));
        if (!valid_index(m_col))
            throw std::runtime_error("Wrong col " + std::to_string(m_col));
    }

    public:
        Square() = delete;
        Square(size_t index) :
                m_row(index / BOARD_SIZE),
                m_col(index % BOARD_SIZE),
                m_index(index) { check_if_valid();}

        Square(size_t row, size_t col) : 
                m_row(row), m_col(col), m_index(col + BOARD_SIZE * row) {
            check_if_valid();
        }

        size_t row() const {return m_row;}
        size_t col() const {return m_col;}
        size_t index() const {return m_index;}

        bool at_border() const {
            return m_row == 0u || m_row == BOARD_SIZE - 1 || m_col == 0u || m_col == BOARD_SIZE - 1;
        }

        std::vector<Square> left_neibs() const {
            std::vector<Square> vec;
            for (uint8_t col = m_col - 1; col < BOARD_SIZE; --col) 
                vec.push_back({m_row, col});
            return vec;
        }

        std::vector<Square> top_neibs() const {
            std::vector<Square> vec;
            for (uint8_t row = m_row + 1; row < BOARD_SIZE; ++row) 
                vec.push_back({row, m_col});
            return vec;
        }

        std::vector<Square> bottom_neibs() const {
            std::vector<Square> vec;
            for (uint8_t row = m_row - 1; row < BOARD_SIZE; --row) 
                vec.push_back({row, m_col});
            return vec;
        }

        std::vector<Square> right_neibs() const {
            std::vector<Square> vec;
            for (uint8_t col = m_col + 1; col < BOARD_SIZE; ++col) 
                vec.push_back({m_row, col});
            return vec;
        }

        std::vector<Square> top_right_neibs() const {
            std::vector<Square> vec;
            for (size_t col = m_col + 1, row = m_row + 1;
                    col < BOARD_SIZE && row < BOARD_SIZE; ++col, ++row) 
                vec.push_back({row, col});
            return vec;
        }

        std::vector<Square> top_left_neibs() const {
            std::vector<Square> vec;
            for (size_t col = m_col - 1, row = m_row + 1;
                    col < BOARD_SIZE && row < BOARD_SIZE; --col, ++row) 
                vec.push_back({row, col});
            return vec;
        }

        std::vector<Square> bottom_left_neibs() const {
            std::vector<Square> vec;
            for (size_t col = m_col - 1, row = m_row - 1;
                    col < BOARD_SIZE && row < BOARD_SIZE; --col, --row) 
                vec.push_back({row, col});
            return vec;
        }

        std::vector<Square> bottom_right_neibs() const {
            std::vector<Square> vec;
            for (size_t col = m_col + 1, row = m_row - 1;
                    col < BOARD_SIZE && row < BOARD_SIZE; ++col, --row) 
                vec.push_back({row, col});
            return vec;
        }
};

}

// export std::ostream& operator<<(std::ostream& os, const def::Color& c) {
//     if (c == def::Color::white) return os << "White";
//     return os << "Black";
// }
