
# Stock & Market Module Interface

Owner: Person 2 — Stock & Market Developer

## Stock

File: `stock/Stock.h`

- `Stock()`
- `Stock(symbol, companyName, price)`
- `getSymbol() const`
- `getCompanyName() const`
- `getPrice() const`
- `updatePrice(double newPrice)`
- `displayStock() const`

## Market

File: `market/Market.h`

- `addStock(const Stock& stock)` returns bool
- `getStock(const std::string& symbol, Stock& result) const`
  returns bool
- `getAllStocks() const` returns `std::vector<Stock>`
- `updateStockPrice(const std::string& symbol, double newPrice)`
  returns bool
- `getStockCount() const` returns int
- `displayMarket() const`

## MarketDataService

File: `market/MarketDataService.h`

- `MarketDataService(Market& market)`
- `getStock(symbol, result) const`
- `getAllStocks() const`
- `getCurrentPrice(symbol, price) const`
- `getStockCount() const`

## Important rules

- Use these exact function names, parameter types, and return types.
- `Market` owns the stock list.
- `MarketDataService` accesses the existing Market object.
- Do not create a separate market stock list in another module.
- Check boolean return values before using results.

## Price Validation

- Stock prices must be positive to be accepted into the market.
- `Stock::updatePrice(double)` returns `false` for zero or negative prices.
- `Market::updateStockPrice(symbol, newPrice)` returns `false` if the symbol is missing or the price is invalid.
- `Market::addStock(stock)` returns `false` for empty symbols, empty company names, non-positive prices, or duplicate symbols.

## MarketDataService Behavior

- `getStock(symbol, result)` returns `true` when the symbol exists.
- `getCurrentPrice(symbol, price)` returns `true` when the symbol exists and writes its price to `price`.
- `getAllStocks()` returns a copy of the current market listing.
- `getStockCount()` returns the number of stocks currently listed.
