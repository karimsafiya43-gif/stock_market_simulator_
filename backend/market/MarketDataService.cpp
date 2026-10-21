
#include "MarketDataService.h"

MarketDataService::MarketDataService(Market& market)
    : market(market) {
}

bool MarketDataService::getStock(
    const std::string& symbol,
    Stock& result) const {

    return market.getStock(symbol, result);
}

std::vector<Stock> MarketDataService::getAllStocks() const {
    return market.getAllStocks();
}

bool MarketDataService::getCurrentPrice(
    const std::string& symbol,
    double& price) const {

    Stock stock;

    if (!market.getStock(symbol, stock)) {
        return false;
    }

    price = stock.getPrice();
    return true;
}

int MarketDataService::getStockCount() const {
    return market.getStockCount();
}
