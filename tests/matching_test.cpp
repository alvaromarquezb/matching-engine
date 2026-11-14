#include <gtest/gtest.h>

#include "orderbook/order_book.hpp"

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

TEST(MatchingTest, NonCrossingOrdersProduceNoTrades) {
  orderbook::OrderBook book;
  book.add(buy(1, 10000));
  auto trades = book.add(sell(2, 10100));
  EXPECT_TRUE(trades.empty());
  EXPECT_EQ(book.order_count(), 2);
}

TEST(MatchingTest, FullMatchEmptiesBook) {
  orderbook::OrderBook book;
  book.add(sell(1, 10000));
  auto trades = book.add(buy(2, 10000));
  ASSERT_EQ(trades.size(), 1u);
  EXPECT_EQ(trades[0], (orderbook::Trade{2, 1, 10000, 100}));
  EXPECT_EQ(book.order_count(), 0);
}

TEST(MatchingTest, TradeExecutesAtRestingPrice) {
  orderbook::OrderBook book;
  book.add(sell(1, 10000));
  auto trades = book.add(buy(2, 10200));
  ASSERT_EQ(trades.size(), 1u);
  EXPECT_EQ(trades[0].price, 10000);
}

TEST(MatchingTest, BetterPriceMatchesFirst) {
  orderbook::OrderBook book;
  book.add(sell(1, 10200));
  book.add(sell(2, 10100));
  auto trades = book.add(buy(3, 10200));
  ASSERT_EQ(trades.size(), 1u);
  EXPECT_EQ(trades[0].sell_order_id, 2);
  EXPECT_EQ(trades[0].price, 10100);
  EXPECT_EQ(book.best_ask(), 10200);
}

TEST(MatchingTest, EarlierOrderMatchesFirstAtSamePrice) {
  orderbook::OrderBook book;
  book.add(sell(1, 10100));
  book.add(sell(2, 10100));
  auto trades = book.add(buy(3, 10100));
  ASSERT_EQ(trades.size(), 1u);
  EXPECT_EQ(trades[0].sell_order_id, 1);
  EXPECT_EQ(book.order_count(), 1);
  EXPECT_EQ(book.best_ask(), 10100);
}

TEST(MatchingTest, PaperExerciseScenario) {
  orderbook::OrderBook book;
  book.add(sell(5, 10100, 50));
  book.add(sell(7, 10100, 30));
  book.add(sell(9, 10200, 100));
  auto trades = book.add(buy(11, 10200, 60));
  ASSERT_EQ(trades.size(), 2u);
  EXPECT_EQ(trades[0], (orderbook::Trade{11, 5, 10100, 50}));
  EXPECT_EQ(trades[1], (orderbook::Trade{11, 7, 10100, 10}));
  EXPECT_EQ(book.best_ask(), 10100);
  EXPECT_EQ(book.order_count(), 2u);
}

TEST(MatchingTest, IncomingSellMatchesBids) {
  orderbook::OrderBook book;
  book.add(buy(1, 10100));
  auto trades = book.add(sell(2, 10000));
  ASSERT_EQ(trades.size(), 1u);
  EXPECT_EQ(trades[0], (orderbook::Trade{1, 2, 10100, 100}));
}