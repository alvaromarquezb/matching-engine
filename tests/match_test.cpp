#include <gtest/gtest.h>
#include "orderbook/match.hpp"

TEST(CrossesTest, BidAboveAskCrosses) {
    EXPECT_TRUE(orderbook::crosses(10100, 10050));
}

TEST(CrossesTest, BidEqualToAskCrosses) {
    EXPECT_TRUE(orderbook::crosses(10050, 10050));
}

TEST(CrossesTest, BidBelowAskDoesNotCross) {
    EXPECT_FALSE(orderbook::crosses(10000, 10050));
}

