#include <iostream>

import attacks;

using att::MagicTables;

int main() {
    auto rm = MagicTables::instance().rmagic({0});

    std::cout << std::hex
        << rm.magic << '\n' << rm.mask << '\n' << rm.shift
        << std::endl;

    return 0;
}
