#pragma once
#include <cstdint>

namespace orderbook {

using Price = std::int64_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

enum class Side { Buy, Sell };

}  // namespace orderbook