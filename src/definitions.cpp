module;
#include <cstdint>
// #include <ostream>
export module definitions;

export namespace def {
    enum class Color {WHITE, BLACK};
    using Bitboard = uint64_t;
}

// export std::ostream& operator<<(std::ostream& os, const def::Color& c) {
//     if (c == def::Color::WHITE) return os << "White";
//     return os << "Black";
// }
