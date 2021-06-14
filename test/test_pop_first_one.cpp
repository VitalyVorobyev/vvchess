#include "test_runner.h"
import definitions;
import magicfinder;

using def::Bitboard;
using def::TOTAL_SQUARES;
using findmagic::pop_first_bit;

void test_single_bit() {
    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        Bitboard b = (Bitboard(1) << i);
        size_t idx = pop_first_bit(b);
        
        ASSERT_EQUAL(b, Bitboard(0));
        ASSERT_EQUAL(i, idx);
    }
}

void test_two_bits() {
    for (size_t i = 1; i < TOTAL_SQUARES; ++i) {
        Bitboard b = (Bitboard(1) << i) + 1;
        size_t idx = pop_first_bit(b);
        
        ASSERT_EQUAL(b, Bitboard(1) << i);
        ASSERT_EQUAL(0u, idx);
    }
}

void test_all_bits() {
    Bitboard b(0xFFFFFFFFFFFFFFFF);
    ASSERT_EQUAL(b, Bitboard(-1));
    Bitboard b0 = b;

    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        size_t idx = pop_first_bit(b);
        b0 -= Bitboard(1) << idx;
        ASSERT_EQUAL(b, b0);
        ASSERT_EQUAL(i, idx);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, test_single_bit);
    RUN_TEST(tr, test_two_bits);
    RUN_TEST(tr, test_all_bits);
}
