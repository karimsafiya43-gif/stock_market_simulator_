#include "Holding.h"
#include <iomanip>

// Default constructor
Holding::Holding() : symbol(""), qty(0), avgPrice(0.0) {}

// Parameterized constructor
Holding::Holding(const std::string& sym, int qty, double avgPrice)
    : symbol(sym), qty(qty > 0 ? qty : 0), avgPrice(avgPrice > 0.0 ? avgPrice : 0.0) {}

std::string Holding::getSymbol() const {
    return symbol;
}

int Holding::getQty() const {
    return qty;
}

double Holding::getAvgPrice() const {
    return avgPrice;
}

// Add shares and update weighted average price
void Holding::addShares(int count, double price) {
    if (count <= 0 || price < 0.0) return;
    double totalCost = (avgPrice * qty) + (price * count);
    qty += count;
    avgPrice = totalCost / qty;
}

// Remove shares safely
bool Holding::removeShares(int count) {
    if (count <= 0 || count > qty) return false;
    qty -= count;
    return true;
}

// Compare holding by symbol
bool Holding::operator==(const Holding& other) const {
    return symbol == other.symbol;
}

// Add shares via +=
Holding& Holding::operator+=(int count) {
    if (count > 0) qty += count;
    return *this;
}

// Deduct shares via -=
Holding& Holding::operator-=(int count) {
    removeShares(count);
    return *this;
}

// Stream insertion
std::ostream& operator<<(std::ostream& os, const Holding& h) {
    os << std::left << std::setw(8) << h.symbol
       << std::setw(8) << h.qty
       << "$" << std::fixed << std::setprecision(2) << h.avgPrice;
    return os;
}
