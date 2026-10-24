#pragma once
#include <vector>
#include <string>

class WatchlistService {
public:
    static std::vector<std::string> getUserWatchlist(int userId);
    static bool addToWatchlist(int userId, const std::string& symbol);
    static bool removeFromWatchlist(int userId, const std::string& symbol);
};
