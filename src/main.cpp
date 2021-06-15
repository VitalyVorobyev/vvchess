#include <iostream>
#include <iomanip>
#include <functional>
#include <optional>

import definitions;
import magicfinder;

using findmagic::MagicFinder;
using def::Bitboard;

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::white) return os << "White";
    return os << "Black";
}

void for_each_square(std::function<void(size_t, size_t)> cb) {
    for (size_t row = 0; row < def::BOARD_SIZE; ++row)
        for (size_t col = 0; col < def::BOARD_SIZE; ++col)
            cb(row, col);
}

void print_if_has_value(std::ostream& os, size_t row, size_t col, std::optional<Bitboard>& magic) {
    os << "row " << row << " col " << col << ": ";
    if (magic.has_value()) {
        os << "0x" << std::hex << magic.value() << '\n';
    } else {
        os << "No magic today" << '\n';
    }
}

int main() {
    MagicFinder mf(99);

    std::cout << "Rook magic\n";
    for_each_square([&mf](size_t row, size_t col) {
        auto magic = mf.find_rook_magic({row, col});
        print_if_has_value(std::cout, row, col, magic);
    });

    std::cout << "\nBishop magic\n";
    for_each_square([&mf](size_t row, size_t col) {
        auto magic = mf.find_bishop_magic({row, col});
        print_if_has_value(std::cout, row, col, magic);
    });

    return 0;
}
