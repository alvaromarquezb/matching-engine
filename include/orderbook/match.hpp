#pragma once
#include <cstdint>

namespace orderbook {

using Price = std::int64_t;

// returns true if the bidding price (bid) and the asking price (ask) cross, 
// which means they allow executing a trade operation.
bool crosses(Price bid, Price ask);

} //namespace orderbook

