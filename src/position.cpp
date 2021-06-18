module;

import definitions;
export module position;

using def::Bitboard;
using def::Square;

struct Pieces {
    Bitboard powns;
    Bitboard king;
    Bitboard queen;
    Bitboard bishops;
    Bitboard knights;
};

export class Position {
    Pieces m_blacks;
    Pieces m_whites;
    Bitboard m_occuped;

 public:
    Position() {}

};
