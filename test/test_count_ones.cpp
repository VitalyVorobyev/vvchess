#include "gtest/gtest.h"
#include <array>
import definitions;
import magicfinder;

using def::Bitboard;
using def::TOTAL_SQUARES;
using findmagic::count_ones;

TEST(CountOnes, OneBit) {
    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        ASSERT_EQ(1u, count_ones(Bitboard(1) << i));
    }
}

TEST(CountOnes, TwoBits) {
    for (size_t i = 1; i < TOTAL_SQUARES; ++i) {
        ASSERT_EQ(2u, count_ones((Bitboard(1) << i) + 1));
    }
}

TEST(CountOnes, AllBits) {
    Bitboard b(0xFFFFFFFFFFFFFFFF);
    ASSERT_EQ(b, Bitboard(-1));

    for (size_t i = 0; i < TOTAL_SQUARES; ++i) {
        ASSERT_EQ(count_ones(b), TOTAL_SQUARES - i);
        b -= Bitboard(1) << i;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
