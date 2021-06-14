#include "test_runner.h"
#include <array>
import definitions;
import magicfinder;

using def::Bitboard;
using def::TOTAL_SQUARES;
using findmagic::count_ones;

void test_single_bit() {
    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        ASSERT_EQUAL(1u, count_ones(Bitboard(1) << i));
    }
}

void test_two_bits() {
    for (size_t i = 1; i < TOTAL_SQUARES; ++i) {
        ASSERT_EQUAL(2u, count_ones((Bitboard(1) << i) + 1));
    }
}

void test_all_bits() {
    Bitboard b(0xFFFFFFFFFFFFFFFF);
    ASSERT_EQUAL(b, Bitboard(-1));

    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        ASSERT_EQUAL(count_ones(b), TOTAL_SQUARES - i);
        b -= Bitboard(1) << i;
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, test_single_bit);
    RUN_TEST(tr, test_two_bits);
    RUN_TEST(tr, test_all_bits);
}
