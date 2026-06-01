#include <iostream>
#include <random>

#include "order.h"
#include "orderbook.h"

int main()
{
    OrderBook book;

    // Random number setup
    std::random_device rd;
    std::mt19937 gen(rd());

    // Synthetic workload configuration
    std::uniform_int_distribution<> priceDist(70, 100);
    std::uniform_int_distribution<> qtyDist(1, 100);
    std::uniform_int_distribution<> sideDist(0, 1);

    const int NUM_ORDERS = 100000;

    // Generate random orders and feed them into the book
    for (int i = 1; i <= NUM_ORDERS; i++)
    {
        Order order;

        // Sequential IDs keep every order unique
        order.id = i;

        // Random order attributes
        order.price = priceDist(gen);
        order.quantity = qtyDist(gen);
        order.side = sideDist(gen) ? 'B' : 'S';

        // Add incoming order to the book
        book.addOrder(order);

        // Attempt matching immediately after arrival
        book.matchOrder();
    }

    std::cout << "\nFINAL ORDERBOOK\n";
    book.printBook();

    return 0;
}