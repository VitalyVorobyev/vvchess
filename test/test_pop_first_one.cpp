#include "gtest/gtest.h"

import definitions;
import magicfinder;

using def::Bitboard;
using def::TOTAL_SQUARES;
using findmagic::pop_first_bit;

TEST(PopFirstBit, OneBit) {
    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        Bitboard b = (Bitboard(1) << i);
        size_t idx = pop_first_bit(b);
        
        ASSERT_EQ(b, Bitboard(0));
        ASSERT_EQ(i, idx);
    }
}

TEST(PopFirstBit, TwoBits) {
    for (size_t i = 1; i < TOTAL_SQUARES; ++i) {
        Bitboard b = (Bitboard(1) << i) + 1;
        size_t idx = pop_first_bit(b);
        
        ASSERT_EQ(b, Bitboard(1) << i);
        ASSERT_EQ(0u, idx);
    }
}

TEST(PopFirstBit, AllBits) {
    Bitboard b(0xFFFFFFFFFFFFFFFF);
    ASSERT_EQ(b, Bitboard(-1));
    Bitboard b0 = b;

    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        size_t idx = pop_first_bit(b);
        b0 -= Bitboard(1) << idx;
        ASSERT_EQ(b, b0);
        ASSERT_EQ(i, idx);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
