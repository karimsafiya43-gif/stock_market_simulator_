#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>
#include <vector>
#include <iostream>
#include "Holding.h"

class Portfolio {
private:
    double cash;
    std::vector<Holding> holdings;

public:
    Portfolio();
    explicit Portfolio(double initCash);

    double getCash() const;
    const std::vector<Holding>& getHoldings() const;

    bool getHolding(const std::string& sym, Holding& res) const;
    int getHoldingQty(const std::string& sym) const;
    int getHoldingCount() const;

    bool deposit(double amt);
    bool withdraw(double amt);

    bool addPosition(const std::string& sym, int qty, double price);
    bool removePosition(const std::string& sym, int qty);

    void displayPortfolio() const;

    // Operator overloads
    Portfolio& operator+=(double amt);
    Portfolio& operator-=(double amt);
    friend std::ostream& operator<<(std::ostream& os, const Portfolio& p);
};

#endif
