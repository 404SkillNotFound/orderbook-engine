# Order Book Engine

A simplified C++ order book matching engine built to understand price-time priority, FIFO execution and order matching.

## Overview

An order book is a collection of buy and sell orders maintained by an exchange. A matching engine uses this book to determine which orders can be fully or partially executed based on price and availability.

This project was built from scratch to understand how orders are stored, matched and executed inside a market. The implementation focuses on the core mechanics of an order book, including price levels, price-time priority, FIFO execution, partial fills and order cancellation.

The objective of V1 was correctness and understanding rather than maximum performance.

## Build

```bash
g++ src/main.cpp src/orderbook.cpp -Iinclude -o orderbook
```

## Run

```bash
./orderbook
```

## Data Structures

Bid and ask price levels are stored using `std::map`.

The map keeps prices sorted automatically, allowing the engine to access the best bid and best ask directly without performing additional sorting operations.

Orders belonging to the same price level are stored using `std::list`.

This preserves arrival order at each price level and allows the engine to process orders according to the FIFO principle. The oldest order at a price level can be accessed using `front()` and removed using `pop_front()` once it has been completely executed.

The bid side uses a descending order map while the ask side uses an ascending order map. This allows the engine to access the highest bid and lowest ask directly from the beginning of their respective containers.

## Order Matching

The engine follows a price-time priority model.

Orders are first prioritized by price. A trade can occur only when the highest bid price is greater than or equal to the lowest ask price.

When multiple orders exist at the same price level, the order that arrived first is matched first. This follows the FIFO (First In First Out) principle.

The engine supports both complete and partial fills. If one side of a trade contains a larger quantity than the other, the remaining quantity stays in the order book until another matching order arrives.

Matching stops whenever either side of the book becomes empty or when no valid trade exists between the best bid and best ask.

## Order Cancellation

Orders can be cancelled using their unique order identifier.

The engine searches both the bid and ask side of the book to locate the requested order. Once found, the order is removed from its corresponding price level.

If the cancelled order was the final order at that price level, the price level itself is removed from the book.

The current implementation performs a linear search through the order book in order to locate an order identifier.

## Design Decisions

Several implementation choices were made to keep the first version simple while still exercising the important parts of a matching engine.

Price levels were stored using `std::map` because the container maintains sorted ordering automatically. This made it straightforward to obtain the highest bid and lowest ask while implementing the matching logic.

Orders at the same price level were stored using `std::list` in order to preserve FIFO execution and allow efficient removal of fully executed orders.

Order identifiers were generated sequentially during testing. The only requirement for an identifier was uniqueness, and sequential identifiers made debugging and verification easier.

Orders are matched immediately after arrival. This mirrors the behaviour of an exchange where incoming orders are checked against the opposite side of the book as soon as they enter the matching engine.

The project intentionally prioritised readability and correctness over aggressive optimisation. More advanced data structures and memory management techniques have been left for future versions.

## Synthetic Workload

A synthetic workload was used to evaluate engine behaviour and performance.

The benchmark generates 100,000 orders.

A workload of one hundred thousand orders was selected because it is large enough to stress the matching engine while still allowing rapid iteration during development and testing.

Prices are generated within a range of 70 to 100.

A relatively narrow price range was chosen intentionally so that many orders accumulate at the same price levels. This increases queue depth and exercises FIFO matching behaviour more heavily than a wider distribution would.

Order quantities are generated within a range of 1 to 100.

Buy and sell orders are generated with equal probability in order to keep both sides of the book active throughout the benchmark.

Each generated order is inserted into the book and matching is attempted immediately afterwards.

The workload is intended to test correctness and throughput rather than simulate real market behaviour.

## Benchmark Results

The benchmark was executed multiple times using the synthetic workload described above.

Across multiple runs the engine processed one hundred thousand orders in approximately 75 milliseconds.

Average execution time for `addOrder()` was approximately 35.6 milliseconds while average execution time for `matchOrder()` was approximately 24.0 milliseconds.

This corresponds to a throughput of roughly 1.3 million orders per second, or approximately 757 nanoseconds per order.

In the benchmark workload, `addOrder()` consumed more time than `matchOrder()`. One possible explanation is that every incoming order must be inserted into the book, while not every call to `matchOrder()` results in a trade being executed.

The benchmark results should be interpreted as measurements of this specific synthetic workload and not as representative exchange latency.

## Limitations

This implementation is intended as an educational project and does not attempt to replicate the complete behaviour of a production exchange matching engine.

Order cancellation currently requires a linear search through the order book.

Price levels are stored using `std::map`, which introduces logarithmic lookup costs and additional pointer traversal.

The benchmark workload is synthetic and does not reflect real market activity.

The engine is single-threaded and does not include networking, persistence, market data handling or exchange connectivity.

No direct order identifier index is currently maintained.

## Future Work

Future versions of the project may introduce direct order identifier indexing for faster cancellation, alternative storage structures for price levels, memory pooling techniques, historical market data replay and more realistic workload generation.

Additional profiling and benchmarking can also be performed to better understand latency characteristics and identify performance bottlenecks.

The primary goal for future versions is to explore how the design can evolve from a correctness-focused implementation towards a more performance-oriented matching engine.
