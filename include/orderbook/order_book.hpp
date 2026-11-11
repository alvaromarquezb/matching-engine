#pragma once
#include <cstddef>
#include <deque>
#include <functional>
#include <map>
#include <optional>

#include "orderbook/order.hpp"

namespace orderbook {
class OrderBook {
 public:
  // Adds a resting order to its side of the book, does not match (yet)
  void add(const Order& order);
  // Returns the highest buying price or std::nullopt if there are no buy orders
  std::optional<Price> best_bid() const;
  // Returns the lowest asking price or std::nullopt if there are no sell orders
  std::optional<Price> best_ask() const;
  // Returns the number of orders
  std::size_t order_count() const;

 private:
  std::map<Price, std::deque<Order>, std::greater<Price>> bids_;
  std::map<Price, std::deque<Order>> asks_;
  std::size_t order_count_ = 0;
};
}  // namespace orderbook