
#include "Stock.h"

#include <iostream>
#include <iomanip>

Stock::Stock()
    : symbol(""),
      companyName(""),
      sector(""),
      price(0.0),
      previousClose(0.0),
      dailyChangePercent(0.0),
      priceHistory() {
}

Stock::Stock(const std::string& symbol,
             const std::string& companyName,
             double price)
    : symbol(symbol),
      companyName(companyName),
      sector("Other"),
      price(price > 0.0 ? price : 0.0),
      previousClose(price > 0.0 ? price : 0.0),
      dailyChangePercent(0.0),
      priceHistory() {

    if (this->price > 0.0) {
        priceHistory.push_back(this->price);
    }
}

Stock::Stock(const std::string& symbol,
             const std::string& companyName,
             const std::string& sector,
             double price,
             double dailyChangePercent,
             const std::vector<double>& priceHistory)
    : symbol(symbol),
      companyName(companyName),
      sector(sector),
      price(price > 0.0 ? price : 0.0),
      previousClose(0.0),
      dailyChangePercent(0.0),
      priceHistory(priceHistory) {

    std::vector<double> validHistory;

    for (double historicalPrice : this->priceHistory) {
        if (historicalPrice > 0.0) {
            validHistory.push_back(historicalPrice);
        }
    }

    this->priceHistory = validHistory;

    if (this->price > 0.0) {
        if (this->priceHistory.empty()) {
            this->priceHistory.push_back(this->price);
        } else {
            this->priceHistory.back() = this->price;
        }
    }

    // Use the supplied daily change to infer the previous close.
    if (dailyChangePercent > -100.0) {
        previousClose =
            this->price / (1.0 + dailyChangePercent / 100.0);
    }

    if (previousClose > 0.0) {
        this->dailyChangePercent =
            ((this->price - previousClose) / previousClose) * 100.0;
    }
}

std::string Stock::getSymbol() const {
    return symbol;
}

std::string Stock::getCompanyName() const {
    return companyName;
}

std::string Stock::getSector() const {
    return sector;
}

double Stock::getPrice() const {
    return price;
}
double Stock::getPreviousClose() const {
    return previousClose;
}

bool Stock::setPreviousClose(double newPreviousClose) {
    if (newPreviousClose <= 0.0) {
        return false;
    }

    previousClose = newPreviousClose;

    dailyChangePercent =
        ((price - previousClose) / previousClose) * 100.0;

    return true;
}

double Stock::getDailyChangePercent() const {
    return dailyChangePercent;
}

std::vector<double> Stock::getPriceHistory() const {
    return priceHistory;
}

bool Stock::updatePrice(double newPrice) {
    if (newPrice <= 0.0) {
        return false;
    }

    price = newPrice;
    priceHistory.push_back(newPrice);

    if (previousClose > 0.0) {
        dailyChangePercent =
            ((price - previousClose) / previousClose) * 100.0;
    }

    return true;
}

bool Stock::updateDailyChangePercent(double newChange) {
    dailyChangePercent = newChange;
    return true;
}

bool Stock::setPriceHistory(
    const std::vector<double>& history) {

    std::vector<double> validHistory;

    for (double historicalPrice : history) {
        if (historicalPrice <= 0.0) {
            return false;
        }

        validHistory.push_back(historicalPrice);
    }

    if (price > 0.0) {
        if (validHistory.empty()) {
            validHistory.push_back(price);
        } else {
            validHistory.back() = price;
        }
    }

    priceHistory = validHistory;
    return true;
}

void Stock::displayStock() const {
    std::cout << std::left
              << std::setw(12) << symbol
              << std::setw(28) << companyName
              << std::setw(16) << sector
              << std::fixed << std::setprecision(2)
              << price << '\n';
}
