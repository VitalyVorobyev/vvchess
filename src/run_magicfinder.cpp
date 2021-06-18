#include <iostream>
#include <iomanip>
#include <functional>
#include <optional>
#include <fstream>

// import attacks;
import definitions;
import magicfinder;

// using findmagic::MagicFinder;
using def::Size;

void for_each_square(std::function<void(Size)> cb) {
    for (Size idx = 0; idx < def::TOTAL_SQUARES; ++idx) cb(idx);
}

int main() {
    constexpr int seed = 96;
    findmagic::MagicFinder mf(seed);

    auto rfile = std::ofstream("../data/rook_magic.txt", std::ios::out);
    if (!rfile.good()) throw std::runtime_error("Can't create rook magic file");
    rfile << std::hex;

    std::cout << "Rook magic\n";
    for_each_square([&mf, &rfile](Size idx) { rfile << mf.find_rook_magic({idx}) << ' ';});

    auto bfile = std::ofstream("../data/bishop_magic.txt", std::ios::out);
    if (!bfile.good()) throw std::runtime_error("Can't create bishop magic file");
    bfile << std::hex;

    std::cout << "Bishop magic\n";
    for_each_square([&mf, &bfile](Size idx) { bfile << mf.find_bishop_magic({idx}) << ' ';});

    // const att::MagicTables& mt = att::MagicTables::instance();
    // mt.do_nothing();

    return 0;
}
