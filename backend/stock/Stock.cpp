
#include "Stock.h"
#include <iostream>
#include <iomanip>
#include <utility>

Stock::Stock()
    : symbol(""), companyName(""), price(0.0) {
}

Stock::Stock(const std::string& symbol,
             const std::string& companyName,
             double price)
    : symbol(symbol),
      companyName(companyName),
      price(price >= 0.0 ? price : 0.0) {
}

std::string Stock::getSymbol() const {
    return symbol;
}

std::string Stock::getCompanyName() const {
    return companyName;
}

double Stock::getPrice() const {
    return price;
}

bool Stock::updatePrice(double newPrice) {
    if (newPrice <= 0.0) {
        return false;
    }

    price = newPrice;
    return true;
}

void Stock::displayStock() const {
    std::cout << std::left
              << std::setw(12) << symbol
              << std::setw(28) << companyName
              << std::fixed << std::setprecision(2)
              << price << '\n';
}
