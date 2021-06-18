#include "gtest/gtest.h"

import definitions;
import magicfinder;

using def::Bitboard;
using findmagic::rook_mask;

TEST(RookMask, D4) {ASSERT_EQ(Bitboard(   0x8087608080800), rook_mask({4, 3}));}
TEST(RookMask, E4) {ASSERT_EQ(Bitboard(  0x10106e10101000), rook_mask({4, 4}));}
TEST(RookMask, A8) {ASSERT_EQ(Bitboard(0x7e01010101010100), rook_mask({7, 0}));}
TEST(RookMask, H1) {ASSERT_EQ(Bitboard(  0x8080808080807e), rook_mask({0, 7}));}
TEST(RookMask, A1) {ASSERT_EQ(Bitboard(   0x101010101017e), rook_mask({0, 0}));}
TEST(RookMask, H8) {ASSERT_EQ(Bitboard(0x7e80808080808000), rook_mask({7, 7}));}
TEST(RookMask, G7) {ASSERT_EQ(Bitboard(  0x3e404040404000), rook_mask({6, 6}));}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
