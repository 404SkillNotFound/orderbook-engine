#include <chrono>
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

    auto totalStart = std::chrono::high_resolution_clock::now();

    long long addOrderTime = 0;
    long long matchOrderTime = 0;

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

        auto addStart = std::chrono::high_resolution_clock::now();

        // Add incoming order to the book
        book.addOrder(order);

        auto addEnd = std::chrono::high_resolution_clock::now();

        addOrderTime +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                addEnd - addStart)
                .count();

        auto matchStart = std::chrono::high_resolution_clock::now();

        // Attempt matching immediately after arrival
        book.matchOrder();

        auto matchEnd = std::chrono::high_resolution_clock::now();

        matchOrderTime +=
            std::chrono::duration_cast<std::chrono::nanoseconds>(
                matchEnd - matchStart)
                .count();
    }

    auto totalEnd = std::chrono::high_resolution_clock::now();

    auto totalTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            totalEnd - totalStart)
            .count();

    std::cout << "\n===== BENCHMARK RESULTS =====\n";

    std::cout << "Orders Processed: "
              << NUM_ORDERS
              << "\n";

    std::cout << "Total Runtime: "
              << totalTime
              << " ms\n";

    std::cout << "addOrder() Time: "
              << addOrderTime / 1000000.0
              << " ms\n";

    std::cout << "matchOrder() Time: "
              << matchOrderTime / 1000000.0
              << " ms\n";

    std::cout << "\nFINAL ORDERBOOK\n";
    book.printBook();

    return 0;
}