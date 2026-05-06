#include <map>
#include <list>
#include <functional>
#include <iostream>
#include "order.h"
#include "orderbook.h"

void OrderBook::printBook()
{
    std::cout << "Bids:\n";

    // key = price level, value = list of orders at that price
    for (const auto &[key, value] : bids)
    {
        // printing: price level -> number of orders at that level
        std::cout << key << " -- " << value.size() << " orders\n";
    }
    std::cout << "\nAsks\n";

    for (const auto &[key, value] : asks)
    {
        std::cout << key << "--" << value.size() << " orders\n";
    }
}
