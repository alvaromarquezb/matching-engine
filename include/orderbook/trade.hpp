#pragma once
#include "orderbook/types.hpp"

namespace orderbook {
struct Trade {
  OrderId buy_order_id;
  OrderId sell_order_id;
  Price price;
  Quantity quantity;

  bool operator==(const Trade&) const = default;
};

}  // namespace orderbook