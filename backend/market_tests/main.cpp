#include <iostream>
#include "../stock/Stock.h"
#include "../market/Market.h"
#include "../market/MarketDataService.h"

int main() {
    Stock s1("TCS", "Tata Consultancy Services", 3500.0);
    Stock s2("INFY", "Infosys", 1800.0);

    Market market;

    std::cout << "Adding stocks...\n";
    std::cout << market.addStock(s1) << '\n';
    std::cout << market.addStock(s2) << '\n';
    std::cout << "Adding duplicate TCS: "
          << market.addStock(s1) << '\n';

    MarketDataService service(market);
     double price = 0.0;
    std::cout << "\nUpdating TCS price...\n";

market.updateStockPrice("TCS", 3600.0);
bool invalidUpdate = market.updateStockPrice("TCS", -100.0);

std::cout << "Negative price update accepted: "
          << invalidUpdate << '\n';

if (service.getCurrentPrice("TCS", price)) {
    std::cout << "TCS price after invalid update: "
              << price << '\n';
}

if (service.getCurrentPrice("TCS", price)) {
    std::cout << "Updated TCS price: " << price << '\n';
}
if (service.getCurrentPrice("UNKNOWN", price)) {
    std::cout << "Unknown stock found unexpectedly!\n";
} else {
    std::cout << "Unknown stock correctly not found.\n";
}

   

    if (service.getCurrentPrice("TCS", price)) {
        std::cout << "TCS current price: " << price << '\n';
    } else {
        std::cout << "TCS not found\n";
    }

    std::cout << "\nMarket listing:\n";
    market.displayMarket();

    return 0;
}