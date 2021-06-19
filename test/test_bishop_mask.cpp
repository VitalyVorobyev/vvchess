#include "gtest/gtest.h"

import definitions;
import bbtools;

using def::Bitboard;
using bbt::bishop_mask;

TEST(BishopMask, D4) {ASSERT_EQ(Bitboard(0x22140014224000), bishop_mask({4, 3}));}
TEST(BishopMask, E4) {ASSERT_EQ(Bitboard(0x44280028440200), bishop_mask({4, 4}));}
TEST(BishopMask, A8) {ASSERT_EQ(Bitboard( 0x2040810204000), bishop_mask({7, 0}));}
TEST(BishopMask, H1) {ASSERT_EQ(Bitboard( 0x2040810204000), bishop_mask({0, 7}));}
TEST(BishopMask, A1) {ASSERT_EQ(Bitboard(0x40201008040200), bishop_mask({0, 0}));}
TEST(BishopMask, H8) {ASSERT_EQ(Bitboard(0x40201008040200), bishop_mask({7, 7}));}
TEST(BishopMask, G7) {ASSERT_EQ(Bitboard(  0x201008040200), bishop_mask({6, 6}));}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
