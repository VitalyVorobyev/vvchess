#include <iostream>
import definitions;
import magicfinder;

using findmagic::MagicFinder;

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::white) return os << "White";
    return os << "Black";
}


int main() {
    std::cout << "Hello, "
              << def::Color::black << " and " << def::Color::white
              << std::endl;
    MagicFinder mf;
    auto magic = mf.find_rook_magic({1, 3});
    if (magic.has_value()) {
        std::cout << magic.value() << std::endl;
    } else {
        std::cout << "No magic today" << std::endl;
    }
    return 0;
}
