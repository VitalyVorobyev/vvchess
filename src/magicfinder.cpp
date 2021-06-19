module;
#include <random>
#include <limits>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>

import definitions;
import bbtools;
export module magicfinder;

using def::Bitboard;
using def::Square;
using def::Size;

export namespace findmagic {

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

class MagicFinder {
    RandomBitboard m_rndm_bb;
    static constexpr size_t m_max_iter = 1e7;

    using BitboardTransformer = std::function<Bitboard(Bitboard)>;

    Bitboard find_magic(Bitboard mask, BitboardTransformer fcn) {
        auto [blockers, nones] = bbt::all_blockers(mask);

        std::vector<Bitboard> attacks(blockers.size());
        std::transform(blockers.begin(), blockers.end(), attacks.begin(), fcn);

        for (size_t iter = 0; iter < m_max_iter; ++iter) {
            Bitboard magic = m_rndm_bb.random_sparse_bitboard();
            const Bitboard folded = (mask * magic) & 0xFF00000000000000ULL;
            if (bbt::count_ones(folded) < 6) continue;  // TODO: why 6?
            std::vector<Bitboard> used(attacks.size(), 0);

            bool success = true;
            for (size_t idx = 0; idx < attacks.size(); ++idx) {
                size_t j = bbt::magic_trick(blockers[idx], magic, nones);
                if (used[j] == 0) used[j] = attacks[idx];
                else if (used[j] != attacks[idx]) {
                    success = false;
                    break;
                }
            }
            if (success) return magic;
        }

        return 0;
    }

 public:
    MagicFinder() : m_rndm_bb(std::random_device("mt19937")()) {}
    MagicFinder(size_t seed) : m_rndm_bb(seed) {}

    Bitboard find_rook_magic(Square s) {
        return find_magic(bbt::rook_mask(s), [s](Bitboard x) {return bbt::rook_attacks(s, x);});
    }

    Bitboard find_bishop_magic(Square s) {
        return find_magic(bbt::bishop_mask(s), [s](Bitboard x) {return bbt::bishop_attacks(s, x);});
    }
};

}
