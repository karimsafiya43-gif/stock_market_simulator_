
#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

class Stock {
private:
    std::string symbol;
    std::string companyName;
    std::string sector;
    double price;
    double previousClose;
    double dailyChangePercent;
    std::vector<double> priceHistory;

public:
    Stock();

    Stock(const std::string& symbol,
          const std::string& companyName,
          double price);

    Stock(const std::string& symbol,
          const std::string& companyName,
          const std::string& sector,
          double price,
          double dailyChangePercent,
          const std::vector<double>& priceHistory);

    std::string getSymbol() const;
    std::string getCompanyName() const;
    std::string getSector() const;
    double getPrice() const;
    double getPreviousClose() const;
    double getDailyChangePercent() const;
    std::vector<double> getPriceHistory() const;

    bool updatePrice(double newPrice);
    bool setPreviousClose(double newPreviousClose);
    bool updateDailyChangePercent(double newChange);
    bool setPriceHistory(const std::vector<double>& history);

    void displayStock() const;
};

#endif
