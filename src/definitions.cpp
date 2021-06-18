module;
#include <cstdint>
#include <stdexcept>
#include <vector>
#include <optional>
#include <functional>

export module definitions;

export namespace def {

using Size = uint8_t;

constexpr extern Size BOARD_SIZE = 8;
constexpr extern Size TOTAL_SQUARES = BOARD_SIZE * BOARD_SIZE;

bool valid_index(Size idx) { return idx < BOARD_SIZE; }
bool valid_index(Size row, Size col) { return valid_index(row) && valid_index(col); }

enum class Color {white, black};
enum class Piece {pawn, bishop, knight, rook, queen, king};
using Bitboard = uint64_t;

class Square;
using SquareOpt = std::optional<Square>;
using SquareVec = std::vector<Square>;

class Square {
    const Size m_row;
    const Size m_col;
    const Size m_index;

    void check_if_valid() const {
        if (!valid_index(m_row)) throw std::runtime_error("Wrong row " + std::to_string(m_row));
        if (!valid_index(m_col)) throw std::runtime_error("Wrong col " + std::to_string(m_col));
    }

    SquareVec neibs(bool pred, std::function<SquareOpt(const Square&)> gett) const {
        if (!pred) return {};
        SquareVec vec{gett(*this).value()};
        while (true) {
            auto sq = gett(vec.back());
            if (!sq.has_value()) break;
            vec.push_back(sq.value());
        }
        return vec;
    }

    SquareOpt neib(bool pred, Size index) const {
        if (!pred) return std::nullopt;
        return {index};
    }

 public:
    Square() = delete;
    Square(Size index) :
            m_row(index >> 3),  // / BOARD_SIZE
            m_col(index  & 7),  // % BOARD_SIZE
            m_index(index) { check_if_valid();}

    Square(Size row, Size col) :
            m_row(row), m_col(col), m_index(col + BOARD_SIZE * row) {
        check_if_valid();
    }

    Size row() const {return m_row;}
    Size col() const {return m_col;}
    Size index() const {return m_index;}

    Size diagonal() const { return (m_row - m_col) & 15;}
    Size antiDiagonal() const { return (m_row + m_col) ^ 7;}

    bool has_lneib() const {return m_col != 0;}
    bool has_rneib() const {return m_col != BOARD_SIZE - 1;}
    bool has_bneib() const {return m_row != 0;}
    bool has_tneib() const {return m_row != BOARD_SIZE - 1;}

    bool has_ltneib() const { return has_lneib() && has_tneib();}
    bool has_lbneib() const { return has_lneib() && has_bneib();}
    bool has_rtneib() const { return has_rneib() && has_tneib();}
    bool has_rbneib() const { return has_rneib() && has_bneib();}

    SquareOpt lneib() const { return neib(has_lneib(), m_index - 1);}
    SquareOpt rneib() const { return neib(has_rneib(), m_index + 1);}
    SquareOpt tneib() const { return neib(has_tneib(), m_index + BOARD_SIZE);}
    SquareOpt bneib() const { return neib(has_bneib(), m_index - BOARD_SIZE);}

    SquareOpt ltneib() const { return neib(has_ltneib(), m_index + BOARD_SIZE - 1);}
    SquareOpt lbneib() const { return neib(has_lbneib(), m_index - BOARD_SIZE - 1);}
    SquareOpt rtneib() const { return neib(has_rtneib(), m_index + BOARD_SIZE + 1);}
    SquareOpt rbneib() const { return neib(has_rbneib(), m_index - BOARD_SIZE + 1);}

    SquareVec tneibs() const {return neibs(has_tneib(), [](const Square& sq) {return sq.tneib();});}
    SquareVec bneibs() const {return neibs(has_bneib(), [](const Square& sq) {return sq.bneib();});}
    SquareVec rneibs() const {return neibs(has_rneib(), [](const Square& sq) {return sq.rneib();});}
    SquareVec lneibs() const {return neibs(has_lneib(), [](const Square& sq) {return sq.lneib();});}

    SquareVec ltneibs() const {return neibs(has_ltneib(), [](const Square& sq) {return sq.ltneib();});}
    SquareVec rtneibs() const {return neibs(has_rtneib(), [](const Square& sq) {return sq.rtneib();});}
    SquareVec lbneibs() const {return neibs(has_lbneib(), [](const Square& sq) {return sq.lbneib();});}
    SquareVec rbneibs() const {return neibs(has_rbneib(), [](const Square& sq) {return sq.rbneib();});}
};

}

// export std::ostream& operator<<(std::ostream& os, const def::Color& c) {
//     if (c == def::Color::white) return os << "White";
//     return os << "Black";
// }
