#include "TradingService.h"
#include <iostream>
#include <iomanip>

TradingService::TradingService(MarketDataService& marketData)
    : marketData(marketData) {}

// Validate buy order before execution
bool TradingService::canBuy(const Portfolio& p, const std::string& sym, int qty, double& cost, std::string& err) const {
    if (sym.empty()) {
        err = "Stock symbol cannot be empty";
        return false;
    }
    if (qty <= 0) {
        err = "Quantity must be greater than zero";
        return false;
    }

    double price = 0.0;
    if (!marketData.getCurrentPrice(sym, price)) {
        err = "Stock not found in market: " + sym;
        return false;
    }

    cost = price * qty;
    if (p.getCash() < cost) {
        err = "Insufficient cash (Required: " + std::to_string(cost) + ", Available: " + std::to_string(p.getCash()) + ")";
        return false;
    }

    err = "OK";
    return true;
}

// Validate sell order before execution
bool TradingService::canSell(const Portfolio& p, const std::string& sym, int qty, double& proceeds, std::string& err) const {
    if (sym.empty()) {
        err = "Stock symbol cannot be empty";
        return false;
    }
    if (qty <= 0) {
        err = "Quantity must be greater than zero";
        return false;
    }

    int curQty = p.getHoldingQty(sym);
    if (curQty < qty) {
        err = "Insufficient shares (Holding: " + std::to_string(curQty) + ", Requested: " + std::to_string(qty) + ")";
        return false;
    }

    double price = 0.0;
    if (!marketData.getCurrentPrice(sym, price)) {
        err = "Stock not found in market: " + sym;
        return false;
    }

    proceeds = price * qty;
    err = "OK";
    return true;
}

// Execute buy trade
bool TradingService::buy(Portfolio& p, const std::string& sym, int qty, std::string& msg) {
    double cost = 0.0;
    if (!canBuy(p, sym, qty, cost, msg)) {
        return false;
    }

    double price = cost / qty;
    p.withdraw(cost);
    p.addPosition(sym, qty, price);
    msg = "Bought " + std::to_string(qty) + " shares of " + sym;
    return true;
}

// Execute sell trade
bool TradingService::sell(Portfolio& p, const std::string& sym, int qty, std::string& msg) {
    double proceeds = 0.0;
    if (!canSell(p, sym, qty, proceeds, msg)) {
        return false;
    }

    p.deposit(proceeds);
    p.removePosition(sym, qty);
    msg = "Sold " + std::to_string(qty) + " shares of " + sym;
    return true;
}

// Overloaded buy
bool TradingService::buy(Portfolio& p, const std::string& sym, int qty) {
    std::string msg;
    return buy(p, sym, qty, msg);
}

// Overloaded sell
bool TradingService::sell(Portfolio& p, const std::string& sym, int qty) {
    std::string msg;
    return sell(p, sym, qty, msg);
}

// Calculate total portfolio net worth (cash + market value of stocks)
double TradingService::calculateValuation(const Portfolio& p) const {
    double total = p.getCash();
    for (const auto& h : p.getHoldings()) {
        double curPrice = 0.0;
        if (marketData.getCurrentPrice(h.getSymbol(), curPrice)) {
            total += h.getQty() * curPrice;
        } else {
            total += h.getQty() * h.getAvgPrice();
        }
    }
    return total;
}

// Calculate overall unrealized profit and loss
double TradingService::calculateTotalPnL(const Portfolio& p) const {
    double pnl = 0.0;
    for (const auto& h : p.getHoldings()) {
        double curPrice = 0.0;
        if (marketData.getCurrentPrice(h.getSymbol(), curPrice)) {
            pnl += (curPrice - h.getAvgPrice()) * h.getQty();
        }
    }
    return pnl;
}

// Display complete account snapshot
void TradingService::displaySummary(const Portfolio& p) const {
    double totalVal = calculateValuation(p);
    double stocksVal = totalVal - p.getCash();
    double pnl = calculateTotalPnL(p);

    std::cout << "\n=========== TRADING ACCOUNT SUMMARY ===========\n";
    std::cout << "Cash Balance:       $" << std::fixed << std::setprecision(2) << p.getCash() << "\n";
    std::cout << "Holdings Value:     $" << stocksVal << "\n";
    std::cout << "Total Net Worth:    $" << totalVal << "\n";
    std::cout << "Unrealized P&L:     " << (pnl >= 0 ? "+$" : "-$") << (pnl >= 0 ? pnl : -pnl) << "\n";
    std::cout << "-----------------------------------------------\n";
    std::cout << "Holdings Breakdown:\n";
    if (p.getHoldings().empty()) {
        std::cout << "  No active positions.\n";
    } else {
        std::cout << "  Symbol   Qty    Avg Price   Cur Price   Unrealized PnL\n";
        for (const auto& h : p.getHoldings()) {
            double curPrice = 0.0;
            marketData.getCurrentPrice(h.getSymbol(), curPrice);
            double diff = (curPrice - h.getAvgPrice()) * h.getQty();
            std::cout << "  " << std::left << std::setw(9) << h.getSymbol()
                      << std::setw(7) << h.getQty()
                      << "$" << std::setw(11) << std::fixed << std::setprecision(2) << h.getAvgPrice()
                      << "$" << std::setw(11) << curPrice
                      << (diff >= 0 ? "+$" : "-$") << (diff >= 0 ? diff : -diff) << "\n";
        }
    }
    std::cout << "===============================================\n";
}
