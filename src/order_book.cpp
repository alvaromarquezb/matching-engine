#include "orderbook/order_book.hpp"

#include <algorithm>

#include "orderbook/match.hpp"

namespace orderbook {

std::vector<Trade> OrderBook::add(const Order& order) {
  Order incoming = order;
  std::vector<Trade> trades;

  switch (order.side) {
    case Side::Buy:
      while (incoming.quantity > 0 && !asks_.empty() &&
             crosses(incoming.price, asks_.begin()->first)) {
        auto best = asks_.begin();
        auto& level = best->second;
        Order& resting = level.front();
        Quantity fill_quantity = std::min(incoming.quantity, resting.quantity);

        trades.push_back(
            {incoming.id, resting.id, resting.price, fill_quantity});
        incoming.quantity -= fill_quantity;
        resting.quantity -= fill_quantity;
        if (resting.quantity == 0) {
          level.pop_front();
          --order_count_;
        }
        if (level.empty()) {
          asks_.erase(best);
        }
      }
      if (incoming.quantity > 0) {
        bids_[incoming.price].push_back(incoming);
        ++order_count_;
      }
      break;
    case Side::Sell:
      while (incoming.quantity > 0 && !bids_.empty() &&
             crosses(bids_.begin()->first, incoming.price)) {
        auto best = bids_.begin();
        auto& level = best->second;
        Order& resting = level.front();
        Quantity fill_quantity = std::min(incoming.quantity, resting.quantity);

        trades.push_back(
            {resting.id, incoming.id, resting.price, fill_quantity});
        incoming.quantity -= fill_quantity;
        resting.quantity -= fill_quantity;
        if (resting.quantity == 0) {
          level.pop_front();
          --order_count_;
        }
        if (level.empty()) {
          bids_.erase(best);
        }
      }
      if (incoming.quantity > 0) {
        asks_[incoming.price].push_back(incoming);
        ++order_count_;
      }
      break;
  }
  return trades;
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