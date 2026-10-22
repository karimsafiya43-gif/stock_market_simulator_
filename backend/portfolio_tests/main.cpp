#include <iostream>
#include "../stock/Stock.h"
#include "../market/Market.h"
#include "../market/MarketDataService.h"
#include "../portfolio/Portfolio.h"
#include "../portfolio/TradingService.h"

int main() {
    std::cout << "=== Trading & Portfolio Module Test ===\n";

    // Setup market
    Market market;
    market.addStock(Stock("TCS", "Tata Consultancy Services", 3500.0));
    market.addStock(Stock("INFY", "Infosys Limited", 1800.0));
    market.addStock(Stock("RELIANCE", "Reliance Industries", 2500.0));

    MarketDataService marketData(market);

    // Setup portfolio with initial cash
    Portfolio myPortfolio(10000.0);
    TradingService trading(marketData);

    std::cout << "\nInitial " << myPortfolio << "\n";

    // Test Operator Overload += (cash deposit)
    std::cout << "\nDepositing $5,000 cash via += operator...\n";
    myPortfolio += 5000.0;
    std::cout << "Updated " << myPortfolio << "\n";

    // Test 1: Valid Buy Order
    std::cout << "\n--- Test 1: Buying 2 shares of TCS @ $3500 --- \n";
    std::string msg;
    bool buyRes = trading.buy(myPortfolio, "TCS", 2, msg);
    std::cout << "Result: " << (buyRes ? "SUCCESS" : "FAILED") << " | " << msg << "\n";
    std::cout << myPortfolio << "\n";

    // Test 2: Valid Buy Order of another stock
    std::cout << "\n--- Test 2: Buying 3 shares of INFY @ $1800 --- \n";
    buyRes = trading.buy(myPortfolio, "INFY", 3, msg);
    std::cout << "Result: " << (buyRes ? "SUCCESS" : "FAILED") << " | " << msg << "\n";
    std::cout << myPortfolio << "\n";

    // Test 3: Insufficient Funds
    std::cout << "\n--- Test 3: Attempting to buy 100 shares of RELIANCE ($250,000) --- \n";
    buyRes = trading.buy(myPortfolio, "RELIANCE", 100, msg);
    std::cout << "Result: " << (buyRes ? "SUCCESS" : "FAILED") << " | Error: " << msg << "\n";

    // Test 4: Unknown Stock Symbol
    std::cout << "\n--- Test 4: Attempting to buy unknown stock 'APPLE' --- \n";
    buyRes = trading.buy(myPortfolio, "APPLE", 5, msg);
    std::cout << "Result: " << (buyRes ? "SUCCESS" : "FAILED") << " | Error: " << msg << "\n";

    // Test 5: Invalid Quantity (0 or negative)
    std::cout << "\n--- Test 5: Attempting to buy with negative quantity --- \n";
    buyRes = trading.buy(myPortfolio, "TCS", -2, msg);
    std::cout << "Result: " << (buyRes ? "SUCCESS" : "FAILED") << " | Error: " << msg << "\n";

    // Display portfolio table
    myPortfolio.displayPortfolio();

    // Test 6: Selling more shares than owned
    std::cout << "\n--- Test 6: Selling 5 shares of TCS (only own 2) --- \n";
    bool sellRes = trading.sell(myPortfolio, "TCS", 5, msg);
    std::cout << "Result: " << (sellRes ? "SUCCESS" : "FAILED") << " | Error: " << msg << "\n";

    // Test 7: Selling valid quantity
    std::cout << "\n--- Test 7: Selling 1 share of TCS --- \n";
    sellRes = trading.sell(myPortfolio, "TCS", 1, msg);
    std::cout << "Result: " << (sellRes ? "SUCCESS" : "FAILED") << " | " << msg << "\n";
    std::cout << myPortfolio << "\n";

    // Test 8: Market price change & PnL calculation
    std::cout << "\n--- Test 8: Market Price Fluctuations & Account Summary --- \n";
    market.updateStockPrice("TCS", 3800.0);    // TCS goes up from 3500 to 3800
    market.updateStockPrice("INFY", 1750.0);   // INFY drops from 1800 to 1750

    trading.displaySummary(myPortfolio);

    // Test Operator Overload -= (cash withdrawal)
    std::cout << "\nWithdrawing $1,000 cash via -= operator...\n";
    myPortfolio -= 1000.0;
    std::cout << "Final " << myPortfolio << "\n";

    std::cout << "\nAll trading tests completed successfully!\n";
    return 0;
}
