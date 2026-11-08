# Matching Engine

A limit order book matching engine written in C++20, similar to the one at the core of a stock exchange. 
It receives buy and sell orders, keeps them in an order book sorted by price, and executes a trade whenever a buyer's and a seller's prices cross, following price-time priority

**Status:** work in progress. 

## Build
```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```
