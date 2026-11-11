#include "orderbook/order_book.hpp"

namespace orderbook {

void OrderBook::add(const Order& order) {
  switch (order.side) {
    case Side::Buy:
      bids_[order.price].push_back(order);
      break;
    case Side::Sell:
      asks_[order.price].push_back(order);
      break;
  }
  ++order_count_;
}

std::optional<Price> OrderBook::best_bid() const {
  if (bids_.empty()) {
    return std::nullopt;
  }
  return bids_.begin()->first;
}

std::optional<Price> OrderBook::best_ask() const {
  if (asks_.empty()) {
    return std::nullopt;
  }
  return asks_.begin()->first;
}

std::size_t OrderBook::order_count() const { return order_count_; }

}  // namespace orderbook