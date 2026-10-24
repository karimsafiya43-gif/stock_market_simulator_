#pragma once
#include <string>

enum class TransactionType { BUY, SELL };

class Transaction {
public:
    int id;
    int userId;
    std::string symbol;
    TransactionType type;
    int quantity;
    double price;
    std::string timestamp;

    Transaction(int id, int userId, std::string symbol, TransactionType type, int quantity, double price, std::string timestamp)
        : id(id), userId(userId), symbol(symbol), type(type), quantity(quantity), price(price), timestamp(timestamp) {}
};
