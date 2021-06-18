#include <iostream>
#include <iomanip>
#include <functional>
#include <optional>
#include <fstream>
#include <sstream>

import definitions;
import magicfinder;

using findmagic::MagicFinder;
using def::Bitboard;
using def::Size;

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::white) return os << "White";
    return os << "Black";
}

void for_each_rowcol(std::function<void(Size, Size)> cb) {
    for (Size row = 0; row < def::BOARD_SIZE; ++row)
        for (Size col = 0; col < def::BOARD_SIZE; ++col)
            cb(row, col);
}

void for_each_square(std::function<void(Size)> cb) {
    for (Size idx = 0; idx < def::TOTAL_SQUARES; ++idx) cb(idx);
}

void print_if_has_value(std::ostream& os, size_t row, size_t col, std::optional<Bitboard> magic) {
    os << row << " " << col << " ";
    if (magic.has_value()) {
        os << "0x" << std::hex << magic.value() << '\n';
    } else {
        os << "No magic today" << '\n';
    }
}

void print_if_has_value(std::ostream& os, size_t idx, std::optional<Bitboard> magic) {
    os << idx << " ";
    if (magic.has_value()) {
        os << "0x" << std::hex << magic.value() << std::dec << '\n';
    } else {
        os << "No magic today" << '\n';
    }
}

int main() {
    constexpr int seed = 96;
    MagicFinder mf(seed);

    // std::ostringstream os;
    // os << "../data/rook_magic" << seed << ".txt";

    auto rfile = std::ofstream("../data/rook_magic.txt", std::ios::out);
    if (!rfile.good()) throw std::runtime_error("Can't create rook magic file");

    std::cout << "Rook magic\n";
    for_each_square([&mf, &rfile](Size idx) {
        print_if_has_value(rfile, idx, mf.find_rook_magic({idx}));
    });

    auto bfile = std::ofstream("../data/bishop_magic.txt", std::ios::out);
    if (!bfile.good()) throw std::runtime_error("Can't create bishop magic file");

    std::cout << "Bishop magic\n";
    for_each_square([&mf, &bfile](Size idx) {
        print_if_has_value(bfile, idx, mf.find_bishop_magic({idx}));
    });

    return 0;
}
