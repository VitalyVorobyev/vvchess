#include <iostream>
#include <iomanip>
#include <functional>
#include <optional>
#include <fstream>
#include <string>

import definitions;
import magicfinder;

using findmagic::MagicFinder;
using def::Bitboard;
using def::Size;

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::white) return os << "White";
    return os << "Black";
}

void for_each_square(std::function<void(Size, Size)> cb) {
    for (Size row = 0; row < def::BOARD_SIZE; ++row)
        for (Size col = 0; col < def::BOARD_SIZE; ++col)
            cb(row, col);
}

void print_if_has_value(std::ostream& os, size_t row, size_t col, std::optional<Bitboard>& magic) {
    os << row << " " << col << " ";
    if (magic.has_value()) {
        os << "0x" << std::hex << magic.value() << '\n';
    } else {
        os << "No magic today" << '\n';
    }
}

int main() {
    constexpr int seed = 97;
    MagicFinder mf(seed);

    auto rfile = std::ofstream("../data/rook_magic" + std::to_string(seed) + ".txt");
    if (!rfile.good()) throw std::runtime_error("Can't create rook magic file");

    std::cout << "Rook magic\n";
    for_each_square([&mf](Size row, Size col) {
        auto magic = mf.find_rook_magic({row, col});
        print_if_has_value(rfile, row, col, magic);
    });

    auto bfile = std::ofstream("../data/bishop_magic" + std::to_string(seed) + ".txt");
    if (!bfile.good()) throw std::runtime_error("Can't create bishop magic file");

    std::cout << "\nBishop magic\n";
    for_each_square([&mf](Size row, Size col) {
        auto magic = mf.find_bishop_magic({row, col});
        print_if_has_value(bfile, row, col, magic);
    });

    return 0;
}
