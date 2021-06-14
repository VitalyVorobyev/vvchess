#include "test_runner.h"
import definitions;
import magicfinder;

using def::Bitboard;
using def::TOTAL_SQUARES;
using findmagic::pop_first_bit;

void test_single_bit() {
    for (int i = 0; i < TOTAL_SQUARES; ++i) {
        Bitboard b = (1 << i);
        int idx = pop_first_bit(b);
        
        ASSERT_EQUAL(b, Bitboard(0));
        ASSERT_EQUAL(i, idx);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, test_single_bit);
}
