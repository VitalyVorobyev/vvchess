#include <iostream>
#include <iomanip>

import definitions;
import magicfinder;

using findmagic::MagicFinder;
using def::Bitboard;

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::white) return os << "White";
    return os << "Black";
}

int main() {
    MagicFinder mf;

    std::cout << "Rook magic\n";
    for (size_t row = 0; row < def::BOARD_SIZE; ++row) {
        for (size_t col = 0; col < def::BOARD_SIZE; ++col) {
            auto magic = mf.find_rook_magic({1, 3});
            std::cout << "row " << row << " col " << col << ": ";
            if (magic.has_value()) {
                std::cout << "0x" << std::hex << magic.value() << '\n';
            } else {
                std::cout << "No magic today" << '\n';
            }
        }
    }

    std::cout << "\nBishop magic\n";
    for (size_t row = 0; row < def::BOARD_SIZE; ++row) {
        for (size_t col = 0; col < def::BOARD_SIZE; ++col) {
            auto magic = mf.find_bishop_magic({1, 3});
            std::cout << "row " << row << " col " << col << ": ";
            if (magic.has_value()) {
                std::cout << "0x" << std::hex << magic.value() << '\n';
            } else {
                std::cout << "No magic today" << '\n';
            }
        }
    }

    return 0;
}
