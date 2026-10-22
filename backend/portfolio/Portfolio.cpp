#include "Portfolio.h"
#include <iomanip>

Portfolio::Portfolio() : cash(0.0) {}

Portfolio::Portfolio(double initCash)
    : cash(initCash >= 0.0 ? initCash : 0.0) {}

double Portfolio::getCash() const {
    return cash;
}

const std::vector<Holding>& Portfolio::getHoldings() const {
    return holdings;
}

// Find a holding by symbol
bool Portfolio::getHolding(const std::string& sym, Holding& res) const {
    for (const auto& h : holdings) {
        if (h.getSymbol() == sym) {
            res = h;
            return true;
        }
    }
    return false;
}

// Get quantity owned for a symbol
int Portfolio::getHoldingQty(const std::string& sym) const {
    Holding res;
    if (getHolding(sym, res)) {
        return res.getQty();
    }
    return 0;
}

int Portfolio::getHoldingCount() const {
    return static_cast<int>(holdings.size());
}

// Deposit cash into portfolio
bool Portfolio::deposit(double amt) {
    if (amt <= 0.0) return false;
    cash += amt;
    return true;
}

// Withdraw cash from portfolio
bool Portfolio::withdraw(double amt) {
    if (amt <= 0.0 || amt > cash) return false;
    cash -= amt;
    return true;
}

// Add shares to existing or new holding
bool Portfolio::addPosition(const std::string& sym, int qty, double price) {
    if (sym.empty() || qty <= 0 || price < 0.0) return false;

    for (auto& h : holdings) {
        if (h.getSymbol() == sym) {
            h.addShares(qty, price);
            return true;
        }
    }

    holdings.push_back(Holding(sym, qty, price));
    return true;
}

// Deduct shares, erasing holding if qty drops to 0
bool Portfolio::removePosition(const std::string& sym, int qty) {
    if (sym.empty() || qty <= 0) return false;

    for (auto it = holdings.begin(); it != holdings.end(); ++it) {
        if (it->getSymbol() == sym) {
            if (qty > it->getQty()) return false;

            it->removeShares(qty);
            if (it->getQty() == 0) {
                holdings.erase(it);
            }
            return true;
        }
    }
    return false;
}

// Print portfolio summary
void Portfolio::displayPortfolio() const {
    std::cout << "\n========== PORTFOLIO ==========\n";
    std::cout << "Available Cash: $" << std::fixed << std::setprecision(2) << cash << "\n";
    std::cout << "Holdings (" << holdings.size() << "):\n";
    if (holdings.empty()) {
        std::cout << "  No stocks held currently.\n";
    } else {
        std::cout << "  Symbol   Qty     Avg Price\n";
        std::cout << "  --------------------------\n";
        for (const auto& h : holdings) {
            std::cout << "  " << h << "\n";
        }
    }
    std::cout << "===============================\n";
}

// Cash deposit via +=
Portfolio& Portfolio::operator+=(double amt) {
    deposit(amt);
    return *this;
}

// Cash withdraw via -=
Portfolio& Portfolio::operator-=(double amt) {
    withdraw(amt);
    return *this;
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const Portfolio& p) {
    os << "Portfolio [Cash: $" << std::fixed << std::setprecision(2) << p.cash
       << ", Positions: " << p.holdings.size() << "]";
    return os;
}
