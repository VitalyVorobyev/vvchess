module;

import definitions;
export module attacks;

using def::Bitboard;
using def::Square;

export namespace att {

constexpr Bitboard row4(0x00000000FF000000);
constexpr Bitboard row5(0x000000FF00000000);

Bitboard pushTop(const Bitboard& bb) { return bb << 8;}
Bitboard pushBot(const Bitboard& bb) { return bb >> 8;}

class PownMoves {
 public:
    Bitboard wSinglePush(Bitboard powns, Bitboard empty) const {
        return pushTop(powns) & empty;
    }
    Bitboard wDoublePush(Bitboard powns, Bitboard empty) const {
        return pushTop(wSinglePush(powns, empty)) & empty & row4;
    }
    Bitboard bSinglePush(Bitboard powns, Bitboard empty) const {
        return pushBot(powns) & empty;
    }
    Bitboard bDoublePush(Bitboard powns, Bitboard empty) const {
        return pushBot(wSinglePush(powns, empty)) & empty & row5;
    }
};

}  // namespace att
