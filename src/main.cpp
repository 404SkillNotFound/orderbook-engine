#include <iostream>
#include "order.h"
#include "orderbook.h"

int main()
{
    OrderBook o1;

    // Buyer wants 50 shares at price 100
    Order buyOrder1;
    buyOrder1.id = 1;
    buyOrder1.price = 100;
    buyOrder1.quantity = 50;
    buyOrder1.side = 'B';

    // Seller #1 sells 10 shares at 90
    Order sellOrder1;
    sellOrder1.id = 2;
    sellOrder1.price = 90;
    sellOrder1.quantity = 10;
    sellOrder1.side = 'S';

    // Seller #2 sells 20 shares at 95
    Order sellOrder2;
    sellOrder2.id = 3;
    sellOrder2.price = 95;
    sellOrder2.quantity = 20;
    sellOrder2.side = 'S';

    // Seller #3 sells 15 shares at 100
    Order sellOrder3;
    sellOrder3.id = 4;
    sellOrder3.price = 100;
    sellOrder3.quantity = 15;
    sellOrder3.side = 'S';

    // This one should NOT trade
    // because ask price > best bid
    Order sellOrder4;
    sellOrder4.id = 5;
    sellOrder4.price = 120;
    sellOrder4.quantity = 100;
    sellOrder4.side = 'S';

    o1.addOrder(buyOrder1);

    o1.addOrder(sellOrder1);
    o1.addOrder(sellOrder2);
    o1.addOrder(sellOrder3);
    o1.addOrder(sellOrder4);

    std::cout << "INITIAL ORDERBOOK\n";
    o1.printBook();

    std::cout << "\nMATCHING ORDERS\n";
    o1.matchOrder();

    std::cout << "\nFINAL ORDERBOOK\n";
    o1.printBook();

    return 0;
}