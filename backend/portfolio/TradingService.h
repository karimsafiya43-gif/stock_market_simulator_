#ifndef TRADING_SERVICE_H
#define TRADING_SERVICE_H

#include <string>
#include "Portfolio.h"
#include "../market/MarketDataService.h"

class TradingService {
private:
    MarketDataService& marketData;

public:
    explicit TradingService(MarketDataService& marketData);

    // Validation checks
    bool canBuy(const Portfolio& p, const std::string& sym, int qty, double& cost, std::string& err) const;
    bool canSell(const Portfolio& p, const std::string& sym, int qty, double& proceeds, std::string& err) const;

    // Execution with feedback message
    bool buy(Portfolio& p, const std::string& sym, int qty, std::string& msg);
    bool sell(Portfolio& p, const std::string& sym, int qty, std::string& msg);

    // Quick execution overloads
    bool buy(Portfolio& p, const std::string& sym, int qty);
    bool sell(Portfolio& p, const std::string& sym, int qty);

    // Valuation & analytics
    double calculateValuation(const Portfolio& p) const;
    double calculateTotalPnL(const Portfolio& p) const;

    void displaySummary(const Portfolio& p) const;
};

#endif
