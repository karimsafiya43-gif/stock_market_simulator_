
#ifndef STOCK_H
#define STOCK_H

#include <string>

class Stock {
private:
    std::string symbol;
    std::string companyName;
    double price;

public:
    Stock();
    Stock(const std::string& symbol,
          const std::string& companyName,
          double price);

    std::string getSymbol() const;
    std::string getCompanyName() const;
    double getPrice() const;

    bool updatePrice(double newPrice);
    void displayStock() const;
};

#endif
