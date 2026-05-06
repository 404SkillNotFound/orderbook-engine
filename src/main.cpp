#include <iostream>
#include "order.h"
#include "orderbook.h"

int main()
{

    OrderBook o1;
    Order buyOrder1;
    buyOrder1.id = 001;
    buyOrder1.price = 3000;
    buyOrder1.quantity = 1200;
    buyOrder1.side = 'B';

    Order buyOrder2;
    buyOrder2.id = 002;
    buyOrder2.price = 40000;
    buyOrder2.quantity = 100;
    buyOrder2.side = 'S';

    Order buyOrder3;
    buyOrder3.id = 003;
    buyOrder3.price = 100;
    buyOrder3.quantity = 10;
    buyOrder3.side = 'S';

    Order buyOrder4;
    buyOrder4.id = 004;
    buyOrder4.price = 2000;
    buyOrder4.quantity = 109;
    buyOrder4.side = 'B';

    o1.addOrder(buyOrder1);
    o1.addOrder(buyOrder2);
    o1.addOrder(buyOrder3);
    o1.addOrder(buyOrder4);

    o1.printBook();

    o1.matchOrder();

    return 0;
}