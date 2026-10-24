#include "WatchlistService.h"

std::vector<std::string> WatchlistService::getUserWatchlist(int userId) {
    return {"RELIANCE", "TCS", "INFY"};
}

bool WatchlistService::addToWatchlist(int userId, const std::string& symbol) {
    return true;
}

bool WatchlistService::removeFromWatchlist(int userId, const std::string& symbol) {
    return true;
}
