#ifndef HOLDING_H
#define HOLDING_H

#include <string>
#include <iostream>

class Holding {
private:
    std::string symbol;
    int qty;
    double avgPrice;

public:
    Holding();
    Holding(const std::string& sym, int qty, double avgPrice);

    std::string getSymbol() const;
    int getQty() const;
    double getAvgPrice() const;

    void addShares(int count, double price);
    bool removeShares(int count);

    // Operator overloads
    bool operator==(const Holding& other) const;
    Holding& operator+=(int count);
    Holding& operator-=(int count);

    friend std::ostream& operator<<(std::ostream& os, const Holding& h);
};

#endif
