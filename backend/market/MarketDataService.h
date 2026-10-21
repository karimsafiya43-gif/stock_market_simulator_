
#ifndef MARKET_DATA_SERVICE_H
#define MARKET_DATA_SERVICE_H

#include <string>
#include <vector>
#include "../stock/Stock.h"
#include "Market.h"

class MarketDataService {
private:
    Market& market;

public:
    explicit MarketDataService(Market& market);

    bool getStock(const std::string& symbol, Stock& result) const;

    std::vector<Stock> getAllStocks() const;

    bool getCurrentPrice(const std::string& symbol,
                         double& price) const;
};

#endif
