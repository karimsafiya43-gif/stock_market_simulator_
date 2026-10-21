
#include "Market.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

bool Market::addStock(const Stock& stock) {
    if (stock.getSymbol().empty() ||
        stock.getCompanyName().empty() ||
        stock.getPrice() <= 0.0) {
        return false;
    }

    for (const Stock& existing : stocks) {
        if (existing.getSymbol() == stock.getSymbol()) {
            return false;
        }
    }

    stocks.push_back(stock);
    return true;
}

bool Market::getStock(const std::string& symbol,
                      Stock& result) const {
    for (const Stock& stock : stocks) {
        if (stock.getSymbol() == symbol) {
            result = stock;
            return true;
        }
    }

    return false;
}

std::vector<Stock> Market::getAllStocks() const {
    return stocks;
}

bool Market::updateStockPrice(const std::string& symbol,
                              double newPrice) {
    if (newPrice <= 0.0) {
        return false;
    }

    for (Stock& stock : stocks) {
        if (stock.getSymbol() == symbol) {
            return stock.updatePrice(newPrice);
        }
    }

    return false;
}

int Market::getStockCount() const {
    return static_cast<int>(stocks.size());
}

void Market::displayMarket() const {
    if (stocks.empty()) {
        std::cout << "\nNo stocks available.\n";
        return;
    }

    std::cout << "\n========== STOCK MARKET ==========\n";
    std::cout << "Symbol      Company                   Price\n";
    std::cout << "------------------------------------------\n";

    for (const Stock& stock : stocks) {
        stock.displayStock();
    }

    std::cout << "------------------------------------------\n";
    std::cout << "Total stocks: " << getStockCount() << '\n';
}
