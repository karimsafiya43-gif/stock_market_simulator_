#include "LeaderboardService.h"

std::vector<LeaderboardEntry> LeaderboardService::getTopTraders() {
    return {
        {"Trader1", 150000.0, 1},
        {"Trader2", 125000.0, 2},
        {"Trader3", 110000.0, 3}
    };
}
