#pragma once
#include <string>

class User {
public:
    int id;
    std::string username;
    std::string email;
    double cashBalance;

    User(int id = 0, std::string username = "", std::string email = "", double cash = 10000.0)
        : id(id), username(username), email(email), cashBalance(cash) {}
};
