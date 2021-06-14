#include <iostream>
#include <iomanip>

import definitions;
import magicfinder;

using findmagic::MagicFinder;
using def::Bitboard;
// using findmagic::pop_first_bit;

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::white) return os << "White";
    return os << "Black";
}


int main() {
    std::cout << "Hello, "
              << def::Color::black << " and " << def::Color::white
              << std::endl;
    MagicFinder mf;
    // auto magic = mf.find_rook_magic({1, 3});
    // if (magic.has_value()) {
    //     std::cout << magic.value() << std::endl;
    // } else {
    //     std::cout << "No magic today" << std::endl;
    // }

    // Bitboard b(4);
    Bitboard b = (Bitboard(1) << 1) + 1;
    std::cout << std::hex << b << std::endl;
    // int j = pop_first_bit(b);
    // std::cout << j << ": " << std::hex << b << std::endl;

    return 0;
}
