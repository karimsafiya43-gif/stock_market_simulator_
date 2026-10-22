
# MarketDataService Usage Guide

This guide explains how other backend modules can access market data.

## 1. Include the header

```cpp
#include "../market/MarketDataService.h"
```

Adjust the relative include path if your source file is in a different folder.

## 2. Use an existing Market object

```cpp
Market market;
market.addStock(Stock("TCS", "Tata Consultancy Services", 3500.0));

MarketDataService marketData(market);
```

In the complete application, use the shared Market instance rather than creating a separate market for each module.

## 3. Get the current price

```cpp
double price = 0.0;

if (marketData.getCurrentPrice("TCS", price)) {
    // Use price for trade calculations.
} else {
    // The requested stock was not found.
}
```

## 4. Get stock details

```cpp
Stock stock;

if (marketData.getStock("TCS", stock)) {
    // Read stock.getSymbol(), stock.getCompanyName(),
    // and stock.getPrice().
}
```

## 5. Get all stocks

```cpp
std::vector<Stock> stocks = marketData.getAllStocks();
```

## Important

- MarketDataService does not own a separate stock list.
- The Market object must outlive MarketDataService because the service stores a reference to it.
- Check boolean return values before using lookup results.
- Coordinate interface changes with Person 2.
