#include <iostream>

#include "orderbook/match.hpp"

int main() {
  std::cout << "Matching engine v0.1\n";

  std::cout << std::boolalpha;
  std::cout << "crosses(10100, 10050) = " << orderbook::crosses(10100, 10050)
            << "\n";
  std::cout << "crosses(10000, 10050) = " << orderbook::crosses(10000, 10050)
            << "\n";

  return 0;
}