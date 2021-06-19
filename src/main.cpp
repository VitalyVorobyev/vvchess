#include <iostream>

import attacks;

using att::MagicTables;

int main() {
    auto mt = MagicTables::instance();
    mt.do_nothing();

    return 0;
}
