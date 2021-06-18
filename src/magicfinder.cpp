module;
#include <random>
#include <limits>
#include <array>
#include <vector>
#include <algorithm>
#include <optional>
#include <numeric>
#include <functional>

import definitions;
export module magicfinder;

using def::Bitboard;
using def::Square;
using def::BOARD_SIZE;
using def::Size;
using def::valid_index;

export namespace findmagic {

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

size_t count_ones(Bitboard b) {
    size_t r = 0;
    while (b) {
        b &= b - 1;
        ++r;
    }
    return r;
}

constexpr std::array<int, 64> BitTable = {
    63, 30,  3, 32, 25, 41, 22, 33,
    15, 50, 42, 13, 11, 53, 19, 34,
    61, 29,  2, 51, 21, 43, 45, 10,
    18, 47,  1, 54,  9, 57,  0, 35,
    62, 31, 40,  4, 49,  5, 52, 26,
    60,  6, 23, 44, 46, 27, 56, 16,
     7, 39, 48, 24, 59, 14, 12, 55,
    38, 28, 58, 20, 37, 17, 36,  8
};

size_t pop_first_bit(Bitboard &b) {
    const Bitboard bb = b ^ (b - 1);
    b &= b - 1;
    uint32_t fold = static_cast<uint32_t>((bb & 0xffffffff) ^ (bb >> 32));
    return BitTable.at((fold * 0x783a9b23) >> 26);
}

Bitboard index_to_bitboard(size_t index, size_t bits, Bitboard b) {
    Bitboard result = 0;
    for(size_t i = 0; i < bits; ++i) {
        size_t j = pop_first_bit(b);
        if (index & (1 << i)) result |= (Bitboard(1) << j);
    }
    return result;
}

class RandomBitboard {
    std::mt19937_64 m_gen;
    std::uniform_int_distribution<Bitboard> m_distrib;

 public:
    RandomBitboard(size_t seed) :
        m_gen(seed),
        m_distrib(0, std::numeric_limits<Bitboard>::max()) {}

    Bitboard random_bitboard() {
        return m_distrib(m_gen);
    }

    Bitboard random_sparse_bitboard() {
        return random_bitboard() & random_bitboard() & random_bitboard();
    }
};

size_t magic_trick(Bitboard b, Bitboard magic, int bits) {
    return static_cast<size_t>((b * magic) >> (64 - bits));
}

class MagicFinder {
    RandomBitboard m_rndm_bb;
    static constexpr size_t m_max_iter = 1e7;

    using BitboardTransformer = std::function<Bitboard(Bitboard)>;

    std::optional<Bitboard> find_magic(Bitboard mask, BitboardTransformer fcn) {
        const size_t nones = count_ones(mask);
        const size_t size = (1 << nones);

        // Consider changing to std::array<Bitboard, 4096>
        std::vector<int> seed(size);
        std::iota(seed.begin(), seed.end(), 0);
        std::vector<Bitboard> attacks(size), blockers(size);

        std::transform(seed.begin(), seed.end(), blockers.begin(),
            [nones, mask](int x) {return index_to_bitboard(x, nones, mask);});

        std::transform(blockers.begin(), blockers.end(), attacks.begin(), fcn);

        for (size_t iter = 0; iter < m_max_iter; ++iter) {
            Bitboard magic = m_rndm_bb.random_sparse_bitboard();
            const Bitboard folded = (mask * magic) & 0xFF00000000000000ULL;
            if (count_ones(folded) < 6) continue;  // TODO: why 6?
            std::vector<Bitboard> used(size, 0);

            bool success = true;
            for (size_t idx = 0; idx < attacks.size(); ++idx) {
                size_t j = magic_trick(blockers[idx], magic, nones);
                if (used[j] == 0) used[j] = attacks[idx];
                else if (used[j] != attacks[idx]) {
                    success = false;
                    break;
                }
            }
            if (success) return magic;
        }

        return std::nullopt;
    }

 public:
    MagicFinder() : m_rndm_bb(std::random_device("mt19937")()) {}
    MagicFinder(size_t seed) : m_rndm_bb(seed) {}

    std::optional<Bitboard> find_rook_magic(Square s) {
        return find_magic(rook_mask(s), [s](Bitboard x) {return rook_attacks(s, x);});
    }

    std::optional<Bitboard> find_bishop_magic(Square s) {
        return find_magic(bishop_mask(s), [s](Bitboard x) {return bishop_attacks(s, x);});
    }
};

}
