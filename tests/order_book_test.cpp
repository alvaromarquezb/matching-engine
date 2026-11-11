#include "orderbook/order_book.hpp"

#include <gtest/gtest.h>

namespace {
orderbook::Order buy(orderbook::OrderId id, orderbook::Price price,
                     orderbook::Quantity quantity = 100) {
  return orderbook::Order{.id = id,
                          .side = orderbook::Side::Buy,
                          .price = price,
                          .quantity = quantity};
}

orderbook::Order sell(orderbook::OrderId id, orderbook::Price price,
                      orderbook::Quantity quantity = 100) {
  return orderbook::Order{.id = id,
                          .side = orderbook::Side::Sell,
                          .price = price,
                          .quantity = quantity};
}
}  // namespace

TEST(OrderBookTest, EmptyBookHasNoBestBid) {
  orderbook::OrderBook book;
  EXPECT_FALSE(book.best_bid().has_value());
}

TEST(OrderBookTest, EmptyBookHasNoBestAsk) {
  orderbook::OrderBook book;
  EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, BestBidIsHighestBuyPrice) {
  orderbook::OrderBook book;
  book.add(buy(1, 10000));
  book.add(buy(2, 10200));
  book.add(buy(3, 10100));
  EXPECT_EQ(book.best_bid(), 10200);
}

TEST(OrderBookTest, BestAskIsLowestSellPrice) {
  orderbook::OrderBook book;
  book.add(sell(1, 10500));
  book.add(sell(2, 10300));
  book.add(sell(3, 10400));
  EXPECT_EQ(book.best_ask(), 10300);
}

TEST(OrderBookTest, BuyOrdersDoNotAffectAsks) {
  orderbook::OrderBook book;
  book.add(buy(1, 10000));
  book.add(buy(2, 10200));
  book.add(buy(3, 10100));
  EXPECT_FALSE(book.best_ask().has_value());
}

TEST(OrderBookTest, OrderCountTracksAddedOrders) {
  orderbook::OrderBook book;
  book.add(buy(1, 10000));
  book.add(buy(2, 10200));
  book.add(sell(3, 10500));
  EXPECT_EQ(book.order_count(), 3u);
}
