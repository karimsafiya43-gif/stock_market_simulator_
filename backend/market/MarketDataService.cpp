
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
bool MarketDataService::getStockSector(
    const std::string& symbol,
    std::string& sector) const {

    Stock stock;

    if (!market.getStock(symbol, stock)) {
        return false;
    }

    sector = stock.getSector();
    return true;
}

bool MarketDataService::getStockPriceHistory(
    const std::string& symbol,
    std::vector<double>& history) const {

    Stock stock;

    if (!market.getStock(symbol, stock)) {
        return false;
    }

    history = stock.getPriceHistory();
    return true;
}
