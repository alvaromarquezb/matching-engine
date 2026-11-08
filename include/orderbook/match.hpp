#pragma once
#include <cstdint>

namespace orderbook {

using Price = std::int64_t;

// Devuelve true si un precio de compra (bid) y uno de venta (ask)
// permiten ejecutar una operación
bool crosses(Price bid, Price ask);

} //namespace orderbook

