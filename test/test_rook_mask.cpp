#include "test_runner.h"
import definitions;
import magicfinder;

using def::Bitboard;
using findmagic::rook_mask;

void test_d4() {ASSERT_EQUAL(Bitboard(   0x8087608080800), rook_mask({4, 3}));}
void test_e4() {ASSERT_EQUAL(Bitboard(  0x10106e10101000), rook_mask({4, 4}));}
void test_a8() {ASSERT_EQUAL(Bitboard(0x7e01010101010100), rook_mask({7, 0}));}
void test_h1() {ASSERT_EQUAL(Bitboard(  0x8080808080807e), rook_mask({0, 7}));}
void test_a1() {ASSERT_EQUAL(Bitboard(   0x101010101017e), rook_mask({0, 0}));}
void test_h8() {ASSERT_EQUAL(Bitboard(0x7e80808080808000), rook_mask({7, 7}));}
void test_g7() {ASSERT_EQUAL(Bitboard(  0x3e404040404000), rook_mask({6, 6}));}

int main() {
    TestRunner tr;
    RUN_TEST(tr, test_d4);
    RUN_TEST(tr, test_e4);
    RUN_TEST(tr, test_a8);
    RUN_TEST(tr, test_a1);
    RUN_TEST(tr, test_h8);
    RUN_TEST(tr, test_h1);
    RUN_TEST(tr, test_g7);
}
