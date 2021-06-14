import definitions;
#include <iostream>

std::ostream& operator<<(std::ostream& os, const def::Color& c) {
    if (c == def::Color::WHITE) return os << "White";
    return os << "Black";
}

int main() {
    std::cout << "Hello, "
              << def::Color::BLACK << " and "
              << def::Color::WHITE
              << std::endl;
    return 0;
}
