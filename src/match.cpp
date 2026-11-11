#include "orderbook/match.hpp"

namespace orderbook {

bool crosses(Price bid, Price ask) { return bid >= ask; }

}  // namespace orderbook