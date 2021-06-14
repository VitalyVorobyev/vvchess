#include "test_runner.h"
import definitions;
import magicfinder;

using def::Bitboard;
using findmagic::bishop_mask;

void test_d4() {ASSERT_EQUAL(Bitboard(0x22140014224000), bishop_mask({4, 3}));}
void test_e4() {ASSERT_EQUAL(Bitboard(0x44280028440200), bishop_mask({4, 4}));}
void test_a8() {ASSERT_EQUAL(Bitboard( 0x2040810204000), bishop_mask({7, 0}));}
void test_h1() {ASSERT_EQUAL(Bitboard( 0x2040810204000), bishop_mask({0, 7}));}
void test_a1() {ASSERT_EQUAL(Bitboard(0x40201008040200), bishop_mask({0, 0}));}
void test_h8() {ASSERT_EQUAL(Bitboard(0x40201008040200), bishop_mask({7, 7}));}
void test_g7() {ASSERT_EQUAL(Bitboard(  0x201008040200), bishop_mask({6, 6}));}

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
