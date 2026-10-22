
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

## Extended Stock Data

The Stock class supports the following additional information:

- `getSector() const` returns the stock's sector.
- `getDailyChangePercent() const` returns the stored daily percentage change.
- `getPriceHistory() const` returns a copy of the stock's historical price points.
- `updateDailyChangePercent(double newChange)` updates the stored daily percentage change.
- `setPriceHistory(const std::vector<double>& history)` validates and replaces the price history.

The extended Stock constructor accepts:
- Stock symbol
- Company name
- Sector
- Current price
- Daily percentage change
- Historical price points

## MarketDataService Additions

- `getStockSector(symbol, sector)` returns true and fills the sector when the stock exists.
- `getStockPriceHistory(symbol, history)` returns true and fills the historical price points when the stock exists.
- Both functions return false when the requested stock is not found.

## Price History Behavior

- A successful `Stock::updatePrice()` appends the new price to the history.
- Historical prices must be positive.
- When the current price is valid, the final history point is kept equal to the current price.
- Price history currently represents recorded price updates; it does not guarantee daily intervals or real-world market history.
