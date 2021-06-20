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

    Bitboard apply(Bitboard occ) const {
        return attacks[((occ & mask) * magic) >> shift];
    }
};

using MagicArray = std::array<MagicForSquare, TOTAL_SQUARES>;

BBArray read_magic(const std::string& path) {
    BBArray bbarr;

    auto ifile = std::ifstream(path, std::ios::in);
    if (!ifile.good()) throw std::runtime_error("");

    auto gen = [&ifile]() {
        static Bitboard bb;
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
        auto rmagic = read_magic(magic_path + m_rmagic_file);
        for (Size index = 0; index < TOTAL_SQUARES; ++index) {
            MagicForSquare& mfsq = m_rmagic[index];

            mfsq.magic = rmagic[index];
            mfsq.mask = bbt::rook_mask({index});
            auto [blockers, bits] = bbt::all_blockers(mfsq.mask);
            mfsq.shift = TOTAL_SQUARES - bits;
            
            std::cout << std::dec << index 
                    //   << " " << bits
                    //   << " " << mfsq.shift
                      << std::endl;

            mfsq.attacks.resize(blockers.size());
            std::for_each(blockers.begin(), blockers.end(), [&mfsq, index](Bitboard bb) {
                mfsq.attacks[bbt::magic_hash(bb, mfsq.magic, mfsq.shift)] =
                    bbt::rook_attacks({index}, bb);
            });
        }
    }

    static std::unique_ptr<MagicTables> m_instance;

    MagicTables() {
        init_rook_magic();
    }

 public:
    static const MagicTables& instance() {
        if (m_instance == nullptr) m_instance = std::unique_ptr<MagicTables>(new MagicTables());
        return *m_instance;
    }

    const MagicForSquare& rmagic(Square sq) const {return m_rmagic[sq.index()];}
    const MagicForSquare& bmagic(Square sq) const {return m_bmagic[sq.index()];}
};

Bitboard rookAttacks(Bitboard occ, Square sq) {
    return MagicTables::instance().rmagic(sq).apply(occ);
}

Bitboard bishopAttacks(Bitboard occ, Square sq) {
    return MagicTables::instance().bmagic(sq).apply(occ);
}

Bitboard queenAttacks(Bitboard occ, Square sq) {
    return rookAttacks(occ, sq) | bishopAttacks(occ, sq);
}

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
