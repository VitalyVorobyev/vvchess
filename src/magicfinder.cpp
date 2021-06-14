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

namespace findmagic {

bool valid_index(int index) { return index >= 0 && index < 64;}

Bitboard bishop_mask(Square s) {
    Bitboard result = 0;
    for (int delta : {7, 9, -7, -9}) {
        for (int index = s.index() + delta; valid_index(index); index += delta)
            result |= (Bitboard(1) << index);
    }
    return result;
}

Bitboard rook_mask(Square s) {
    Bitboard result = 0;
    for (int index = s.index() + 8; index < 64; index += 8) result |= (Bitboard(1) << index);
    for (int index = s.index() - 8; index >= 0; index -= 8) result |= (Bitboard(1) << index);
    for (int idx = 0; idx < 8; ++idx) if (idx != s.col()) {
        result |= (Bitboard(1) << (s.index() - s.col() + idx));
    }
    return result;
}

Bitboard rook_att(Square s, Bitboard block) {
    Bitboard result = 0;
    
    for (int delta : {8, -8}) {
        for (int index = s.index() + delta; valid_index(index); index += delta) {
            result += (Bitboard(1) << index);
            if (block & (Bitboard(1) << index)) break;
        }
    }

    const int index0 = s.index() - s.col();
    for (int idx = s.col() + 1; idx < 8; ++idx) {
        result |= (Bitboard(1) << (index0 + idx));
        if (block & (Bitboard(1) << (index0 + idx))) break;
    }

    for (int idx = s.col() - 1; idx >= 0; --idx) {
        result |= (Bitboard(1) << (index0 + idx));
        if (block & (Bitboard(1) << (index0 + idx))) break;
    }

    return result;
}

Bitboard bishop_att(Square s, Bitboard block) {
    Bitboard result = 0;

    for (int delta : {7, 9, -7, -9}) {
        for (int index = s.index() + delta; valid_index(index); index += delta) {
            result += (Bitboard(1) << index);
            if (block & (Bitboard(1) << index)) break;
        }
    }
    
    return result;
}

export size_t count_ones(Bitboard b) {
    size_t r = 0;
    while (b) {
        b &= b - 1;
        ++r;
    }
    return r;
}

constexpr std::array<int, 64> rook_bits = {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};

constexpr std::array<int, 64> bishop_bits = {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

constexpr std::array<int, 64> BitTable = {
    63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
    51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
    26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
    58, 20, 37, 17, 36, 8
};

export size_t pop_first_bit(Bitboard &b) {
    const Bitboard bb = b ^ (b - 1);
    b &= (b - 1);
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

int magic_trick(Bitboard b, Bitboard magic, int bits) {
    return static_cast<int>((b * magic) >> (64 - bits));
}

export class MagicFinder {
    RandomBitboard m_rndm_bb;
    static constexpr size_t m_max_iter = 1e7;
    
    using BitboardTransformer = std::function<Bitboard(Bitboard)>;

    std::optional<Bitboard> find_magic(Bitboard mask, size_t bits, BitboardTransformer fcn) {
        const size_t nones = count_ones(mask);
        const size_t size = (1 << nones);

        // Consider changing to std::array<Bitboard, 4096>
        std::vector<int> seed(size);
        std::iota(seed.begin(), seed.end(), 0);
        std::vector<Bitboard> a(size), b(size);

        std::transform(seed.begin(), seed.end(), b.begin(),
            [nones, mask](int x) {return index_to_bitboard(x, nones, mask);});

        std::transform(b.begin(), b.end(), a.begin(), fcn);

        for (size_t iter = 0; iter < m_max_iter; ++iter) {
            Bitboard magic = m_rndm_bb.random_sparse_bitboard();
            const Bitboard folded = (mask * magic) & 0xFF00000000000000ULL;
            if (count_ones(folded) < 6) continue;
            std::vector<Bitboard> used(size, 0);

            bool success = true;
            for (size_t idx = 0; idx < a.size(); ++idx) {
                int j = magic_trick(b[idx], magic, bits);
                if (used[j] == 0) used[j] = a[idx];
                else if (used[j] != a[idx]) {
                    success = false;
                    break;
                }
            }
            if (success) return magic;
        }

        return std::nullopt;
    }

 public:
    MagicFinder() : m_rndm_bb(std::random_device()()) {}
    MagicFinder(size_t seed) : m_rndm_bb(seed) {}

    std::optional<Bitboard> find_rook_magic(Square s) {
        return find_magic(rook_mask(s), rook_bits.at(s.index()),
            [s](Bitboard x) {return rook_att(s, x);});
    }

    std::optional<Bitboard> find_bishop_magic(Square s) {
        return find_magic(bishop_mask(s), bishop_bits.at(s.index()),
            [s](Bitboard x) {return bishop_att(s, x);});
    }
};

}
