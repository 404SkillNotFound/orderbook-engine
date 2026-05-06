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
        std::cout << key << " -- " << value.size() << " orders\n";
    }
}
void OrderBook::matchOrder()
{
    if (bids.empty() || asks.empty())
    {
        std::cout << "Sorry! We do not have enough number of orders to match yor up, try again later.\n";
        return;
    }
    auto bestBid = bids.begin();        // first key-value pair of bids
    double priceOfBid = bestBid->first; // first key of bids entry
    auto bestAsk = asks.begin();
    double priceOfAsk = bestAsk->first;
    if (priceOfBid >= priceOfAsk) // Bid = Buyer, Ask = Seller
    {
        std::cout << "Trade Possible.\n";
    }
    else
    {
        std::cout << "Trade not possible.\n";
    }
}
