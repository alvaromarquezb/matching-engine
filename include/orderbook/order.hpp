#pragma once
#include "orderbook/types.hpp"

namespace orderbook {

struct Order {
  OrderId id;
  Side side;
  Price price;
  Quantity quantity;
};

}  // namespace orderbook