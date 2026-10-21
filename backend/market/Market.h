
#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <vector>
#include "../stock/Stock.h"

class Market {
private:
    std::vector<Stock> stocks;

public:
    Market() = default;

    bool addStock(const Stock& stock);

    bool getStock(const std::string& symbol,
                  Stock& result) const;

    std::vector<Stock> getAllStocks() const;

    bool updateStockPrice(const std::string& symbol,
                          double newPrice);

    int getStockCount() const;

    void displayMarket() const;
};

#endif
