# TradingService & Portfolio Usage Guide

Owner: Person 3 — Trading & Portfolio Developer

## 1. Include the headers

```cpp
#include "../portfolio/Portfolio.h"
#include "../portfolio/TradingService.h"
```

## 2. Setup

```cpp
// Initialize portfolio with starting cash
Portfolio portfolio(10000.0);

// Pass the shared MarketDataService instance
TradingService trading(marketData);
```

## 3. Buy Stocks

```cpp
std::string msg;
if (trading.buy(portfolio, "TCS", 2, msg)) {
    // Buy succeeded; msg contains confirmation
} else {
    // Validation failed; msg contains reason (e.g. Insufficient cash)
}
```

## 4. Sell Stocks

```cpp
std::string msg;
if (trading.sell(portfolio, "TCS", 1, msg)) {
    // Sell succeeded; msg contains confirmation
} else {
    // Sell failed; msg contains reason (e.g. Insufficient shares)
}
```

## 5. Portfolio Valuation & Analytics

```cpp
double netWorth = trading.calculateValuation(portfolio);
double unrealizedPnL = trading.calculateTotalPnL(portfolio);
trading.displaySummary(portfolio);
```

## 6. Operator Overloading Examples

```cpp
portfolio += 1000.0;   // Deposit cash
portfolio -= 500.0;    // Withdraw cash
std::cout << portfolio; // Quick snapshot
```
