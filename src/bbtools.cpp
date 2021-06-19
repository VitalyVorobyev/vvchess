module;

#include <cstdint>
#include <array>
#include <vector>
#include <algorithm>

import definitions;

export module bbtools;

using def::BOARD_SIZE;
using def::valid_index;
using def::Bitboard;
using def::Square;
using def::Size;

export namespace bbt {

bool internal_colrow(Size row) {return row > 0 && row < BOARD_SIZE - 1;}
bool internal_colrow(Size row, Size col) {return internal_colrow(row) && internal_colrow(col);}

Bitboard bishop_mask(Square s) {
    Bitboard result(0);
    auto updater = [&result](const std::vector<Square>& neibs) {
        if (neibs.empty()) return;
        std::for_each(neibs.begin(), neibs.end() - 1, [&result](const Square& sq) {
            result |= (Bitboard(1) << sq.index());
        });
    };

    updater(s.rtneibs());
    updater(s.ltneibs());
    updater(s.lbneibs());
    updater(s.rbneibs());

    return result;
}

Bitboard rook_mask(Square s) {
    Bitboard result = 0;

    auto updater = [&result](const std::vector<Square>& neibs) {
        if (neibs.empty()) return;
        std::for_each(neibs.begin(), neibs.end() - 1, [&result](const Square& sq) {
            result |= (Bitboard(1) << sq.index());
        });
    };

    updater(s.lneibs());
    updater(s.rneibs());
    updater(s.tneibs());
    updater(s.bneibs());

    return result;
}

Bitboard rook_attacks(Square s, Bitboard block) {
    Bitboard result = 0;

    auto updater = [&result, block](const std::vector<Square>& neibs) {
        for (auto it = neibs.begin(); it != neibs.end(); ++it) {
            Bitboard bb = Bitboard(1) << it->index();
            result |= bb;
            if (block & bb) break;
        }
    };

    updater(s.lneibs());
    updater(s.rneibs());
    updater(s.tneibs());
    updater(s.bneibs());

    return result;
}

Bitboard bishop_attacks(Square s, Bitboard block) {
    Bitboard result = 0;

    auto updater = [&result, block](const std::vector<Square>& neibs) {
        for (auto it = neibs.begin(); it != neibs.end(); ++it) {
            Bitboard bb = Bitboard(1) << it->index();
            result |= bb;
            if (block & bb) break;
        }
    };

    updater(s.rtneibs());
    updater(s.ltneibs());
    updater(s.lbneibs());
    updater(s.rbneibs());
    
    return result;
}

Size count_ones(Bitboard b) {
    Size r = 0;
    while (b) {
        b &= b - 1;
        ++r;
    }
    return r;
}

constexpr std::array<Size, 64> BitTable = {
    63, 30,  3, 32, 25, 41, 22, 33,
    15, 50, 42, 13, 11, 53, 19, 34,
    61, 29,  2, 51, 21, 43, 45, 10,
    18, 47,  1, 54,  9, 57,  0, 35,
    62, 31, 40,  4, 49,  5, 52, 26,
    60,  6, 23, 44, 46, 27, 56, 16,
     7, 39, 48, 24, 59, 14, 12, 55,
    38, 28, 58, 20, 37, 17, 36,  8
};

Size pop_first_bit(Bitboard &b) {
    const Bitboard bb = b ^ (b - 1);
    b &= b - 1;
    uint32_t fold = static_cast<uint32_t>((bb & 0xffffffff) ^ (bb >> 32));
    return BitTable.at((fold * 0x783a9b23) >> 26);
}

Bitboard index_to_bitboard(size_t index, Size bits, Bitboard b) {
    Bitboard result = 0;
    for(Size i = 0; i < bits; ++i) {
        Size j = pop_first_bit(b);
        if (index & (1 << i)) result |= (Bitboard(1) << j);
    }
    return result;
}

std::pair<std::vector<Bitboard>, Size> all_blockers(Bitboard mask) {
    const Size nones = count_ones(mask);
    std::vector<Bitboard> blockers(1 << nones);
    std::generate(blockers.begin(), blockers.end(), [nones, mask]() {
        static size_t idx = 0;
        return index_to_bitboard(idx++, nones, mask);
    });
    
    return {blockers, nones};
}

size_t magic_trick(Bitboard b, Bitboard magic, Size shift) {
    return static_cast<size_t>((b * magic) >> shift);
}

}  // namespace bbt
