
#include "Market.h"

#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

namespace {
    std::string normalizeSymbol(const std::string& symbol) {
        std::string normalized = symbol;

        for (char& ch : normalized) {
            ch = static_cast<char>(
                std::toupper(static_cast<unsigned char>(ch))
            );
        }

        return normalized;
    }
}

bool Market::addStock(const Stock& stock) {
    if (stock.getSymbol().empty() ||
        stock.getCompanyName().empty() ||
        stock.getPrice() <= 0.0) {
        return false;
    }

    const std::string newSymbol =
        normalizeSymbol(stock.getSymbol());

    for (const Stock& existing : stocks) {
        if (normalizeSymbol(existing.getSymbol()) == newSymbol) {
            return false;
        }
    }

    stocks.push_back(stock);
    return true;
}

bool Market::getStock(const std::string& symbol,
                      Stock& result) const {
    const std::string requestedSymbol = normalizeSymbol(symbol);

    for (const Stock& stock : stocks) {
        if (normalizeSymbol(stock.getSymbol()) == requestedSymbol) {
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
        if (normalizeSymbol(stock.getSymbol()) ==
            normalizeSymbol(symbol)) {
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
    std::cout << std::left
              << std::setw(12) << "Symbol"
              << std::setw(28) << "Company"
              << std::setw(16) << "Sector"
              << "Price\n";

    std::cout << "--------------------------------------------------------\n";

    for (const Stock& stock : stocks) {
        stock.displayStock();
    }

    std::cout << "--------------------------------------------------------\n";
    std::cout << "Total stocks: " << getStockCount() << '\n';
}
