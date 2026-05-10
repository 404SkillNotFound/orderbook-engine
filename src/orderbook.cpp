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
        std::cout << "Sorry! We do not have enough number of orders to match you up, try again later.\n";
        return;
    }
    auto bestBid = bids.begin();        // first key-value pair of bids
    double priceOfBid = bestBid->first; // first key of 'bids' entry

    auto bestAsk = asks.begin();
    double priceOfAsk = bestAsk->first; // first key of 'asks' entry

    if (priceOfBid >= priceOfAsk) // Bid = Buyer, Ask = Seller
    {
        std::cout << "Trade Possible.\n";

        // map entry: first = price level, second = list<Order> at that price
        auto &buyOrder = (bestBid->second).front(); // front() gives oldest order at this price level (FIFO)

        auto &sellOrder = (bestAsk->second).front(); // front() gives oldest order at this price level (FIFO)

        int tradeQuantity = std::min(buyOrder.quantity, sellOrder.quantity); // actual shares traded = smaller quantity between buyer and seller
        buyOrder.quantity -= tradeQuantity;
        sellOrder.quantity -= tradeQuantity; // reduce remaining quantities after executing the trade

        if (buyOrder.quantity == 0)
        {
            // we pop that Order from the bestBid, as now the order is executed
            (bestBid->second).pop_front();
        }
        if (sellOrder.quantity == 0)
        {
            // we pop that Order from the bestAsk, as now the order is exceuted
            (bestAsk->second).pop_front();
        }
        // Todo: Now has the list gone empty?
    }
    else
    {
        std::cout << "Trade not possible.\n";
    }
}
