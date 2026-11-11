#pragma once
#include <cstdint>

#include "orderbook/types.hpp"

namespace orderbook {

// returns true if the bidding price (bid) and the asking price (ask) cross,
// which means they allow executing a trade operation.
bool crosses(Price bid, Price ask);

}  // namespace orderbook
