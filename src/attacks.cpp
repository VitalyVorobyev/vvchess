module;

#include <string>
#include <array>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <iostream>

import definitions;
import bbtools;
export module attacks;

using def::Bitboard;
using def::Square;
using def::Size;
using def::TOTAL_SQUARES;

export namespace att {

constexpr Bitboard row4(0x00000000FF000000);
constexpr Bitboard row5(0x000000FF00000000);

Bitboard pushTop(const Bitboard& bb) { return bb << 8;}
Bitboard pushBot(const Bitboard& bb) { return bb >> 8;}

using BBArray = std::array<Bitboard, TOTAL_SQUARES>;

struct MagicForSquare {
    std::vector<Bitboard> attacks;
    Bitboard mask;
    Bitboard magic;
    Size shift;
};

using MagicArray = std::array<MagicForSquare, TOTAL_SQUARES>;

BBArray read_magic(const std::string& path) {
    BBArray bbarr;

    auto ifile = std::ifstream(path, std::ios::in);
    if (!ifile.good()) throw std::runtime_error("");

    Bitboard bb;
    auto gen = [&ifile, &bb]() {
        ifile >> std::hex >> bb;
        return bb;
    };

    std::generate(bbarr.begin(), bbarr.end(), gen);
    return bbarr;
}

class MagicTables {
    static const std::string magic_path;
    static const std::string m_rmagic_file;
    static const std::string m_bmagic_file;

    MagicArray m_bmagic;
    MagicArray m_rmagic;

    void init_rook_magic() {
        // auto rmagic = read_magic(magic_path + m_rmagic_file);

    }

    static std::unique_ptr<MagicTables> m_instance;

    MagicTables() {
        auto bmagic = read_magic(magic_path + m_bmagic_file);
        auto rmagic = read_magic(magic_path + m_rmagic_file);

        std::cout << std::hex;
        for (size_t i = 0; i < 10; ++i) {
            std::cout << bmagic[i] << " " << rmagic[i] << std::endl;
        }
    }

 public:
    static const MagicTables& instance() {
        if (m_instance == nullptr) m_instance = std::unique_ptr<MagicTables>(new MagicTables());
        return *m_instance;
    }

    void do_nothing() const {}
};

std::unique_ptr<MagicTables> MagicTables::m_instance = nullptr;
const std::string MagicTables::magic_path = "../data/";
const std::string MagicTables::m_rmagic_file = "rook_magic.txt";
const std::string MagicTables::m_bmagic_file = "bishop_magic.txt";

// Pawns
Bitboard wSinglePush(Bitboard powns, Bitboard empty) {
    return pushTop(powns) & empty;
}

Bitboard wDoublePush(Bitboard powns, Bitboard empty) {
    return pushTop(wSinglePush(powns, empty)) & empty & row4;
}

Bitboard bSinglePush(Bitboard powns, Bitboard empty) {
    return pushBot(powns) & empty;
}

Bitboard bDoublePush(Bitboard powns, Bitboard empty) {
    return pushBot(wSinglePush(powns, empty)) & empty & row5;
}

// Bishop
// Bitboard bishopAttacks(Bitboard occ, Square sq) {
//     return 0;
// }

}  // namespace att
