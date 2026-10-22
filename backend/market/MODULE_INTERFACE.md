
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
