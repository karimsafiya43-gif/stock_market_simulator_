#pragma once
#include <vector>
#include <string>

struct LeaderboardEntry {
    std::string username;
    double portfolioValue;
    int rank;
};

class LeaderboardService {
public:
    static std::vector<LeaderboardEntry> getTopTraders();
};
