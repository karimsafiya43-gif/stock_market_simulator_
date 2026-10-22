
#include <iostream>
#include <string>
#include <vector>

#include "../stock/Stock.h"
#include "../market/Market.h"
#include "../market/MarketDataService.h"

int main() {
    Stock s1("TCS", "Tata Consultancy Services", 3500.0);
    Stock s2("INFY", "Infosys", 1800.0);

    Market market;

    // Test adding stocks.
    std::cout << "Adding stocks...\n";
    std::cout << market.addStock(s1) << '\n';
    std::cout << market.addStock(s2) << '\n';

    std::cout << "Adding duplicate TCS: "
              << market.addStock(s1) << '\n';

    MarketDataService service(market);
    double price = 0.0;

    // Test valid and invalid price updates.
    std::cout << "\nUpdating TCS price...\n";

    market.updateStockPrice("TCS", 3600.0);

    bool invalidUpdate =
        market.updateStockPrice("TCS", -100.0);

    bool zeroUpdate =
        market.updateStockPrice("TCS", 0.0);

    std::cout << "Zero price update accepted: "
              << zeroUpdate << '\n';

    if (service.getCurrentPrice("TCS", price)) {
        std::cout << "TCS price after zero update: "
                  << price << '\n';
    }

    std::cout << "Negative price update accepted: "
              << invalidUpdate << '\n';

    if (service.getCurrentPrice("TCS", price)) {
        std::cout << "TCS price after invalid update: "
                  << price << '\n';
    }

    if (service.getCurrentPrice("TCS", price)) {
        std::cout << "Updated TCS price: "
                  << price << '\n';
    }

    // Test lookup of an unknown stock.
    if (service.getCurrentPrice("UNKNOWN", price)) {
        std::cout << "Unknown stock found unexpectedly!\n";
    } else {
        std::cout << "Unknown stock correctly not found.\n";
    }

    if (service.getCurrentPrice("TCS", price)) {
        std::cout << "TCS current price: "
                  << price << '\n';
    } else {
        std::cout << "TCS not found\n";
    }

    // Display the market.
    std::cout << "\nMarket listing:\n";
    market.displayMarket();

    // Test automatic daily-change calculation.
    std::cout << "\nTesting automatic daily change calculation...\n";

    Stock changeTest(
        "TEST",
        "Test Company",
        "IT",
        110.0,
        10.0,
        std::vector<double>{100.0, 110.0}
    );

    std::cout << "Initial previous close: "
              << changeTest.getPreviousClose() << '\n';

    std::cout << "Initial daily change: "
              << changeTest.getDailyChangePercent() << "%\n";

    bool changePriceUpdated = changeTest.updatePrice(120.0);

    std::cout << "Price update accepted: "
              << changePriceUpdated << '\n';

    std::cout << "Price after update: "
              << changeTest.getPrice() << '\n';

    std::cout << "Daily change after price update: "
              << changeTest.getDailyChangePercent() << "%\n";

    // Test the additional Stock fields and price history.
    std::cout << "\nTesting new Stock fields...\n";

    Stock detailedStock(
        "WIPRO",
        "Wipro Limited",
        "IT",
        550.0,
        2.5,
        std::vector<double>{520.0, 530.0, 540.0, 550.0}
    );

    std::cout << "Sector: "
              << detailedStock.getSector() << '\n';

    std::cout << "Daily change: "
              << detailedStock.getDailyChangePercent()
              << "%\n";

    std::vector<double> history =
        detailedStock.getPriceHistory();

    std::cout << "History points: "
              << history.size() << '\n';

    if (!history.empty()) {
        std::cout << "Latest historical price: "
                  << history.back() << '\n';
    }

    // Updating price should append a history point.
    bool historyPriceUpdated =
        detailedStock.updatePrice(560.0);

    std::cout << "History price update accepted: "
              << historyPriceUpdated << '\n';

    history = detailedStock.getPriceHistory();

    std::cout << "History after update: "
              << history.size() << " points\n";

    if (!history.empty()) {
        std::cout << "Latest price after update: "
                  << history.back() << '\n';
    }

    // Test MarketDataService sector and history methods.
    std::cout << "\nTesting MarketDataService...\n";

    market.addStock(detailedStock);

    MarketDataService marketData(market);

    std::string sector;

    if (marketData.getStockSector("WIPRO", sector)) {
        std::cout << "WIPRO sector: "
                  << sector << '\n';
    } else {
        std::cout << "WIPRO sector lookup failed.\n";
    }

    std::vector<double> serviceHistory;

    if (marketData.getStockPriceHistory(
            "WIPRO", serviceHistory)) {
        std::cout << "WIPRO history points: "
                  << serviceHistory.size() << '\n';
    } else {
        std::cout << "WIPRO history lookup failed.\n";
    }

    // Test case-insensitive stock lookup.
    std::cout << "\nTesting case-insensitive symbols...\n";

    Stock foundStock;

    std::cout << "Lookup tcs: "
              << market.getStock("tcs", foundStock) << '\n';

    std::cout << "Lookup Tcs: "
              << market.getStock("Tcs", foundStock) << '\n';

    // A differently-cased duplicate should be rejected.
    Stock duplicateTcs(
        "tcs",
        "Duplicate TCS",
        "IT",
        3500.0,
        0.0,
        std::vector<double>{3400.0, 3500.0}
    );

    std::cout << "Add lowercase duplicate: "
              << market.addStock(duplicateTcs) << '\n';

    return 0;
}
