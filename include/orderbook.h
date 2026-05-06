#pragma once
#include <map>
#include <list>
#include <functional>
#include <iostream>
#include "order.h"

class OrderBook
{
    std::map<double, std::list<Order>, std::greater<double>> bids; // highest price
    std::map<double, std::list<Order>> asks;                       // lowest price
public:
    void addOrder(const Order &o)
    {
        if (o.side == 'B')
        {
            bids[o.price].push_back(o);
        }
        else if (o.side == 'S')
        {
            asks[o.price].push_back(o);
        }
        else
        {
            std::cout << "Kindly choose from 'B' or 'S'\n";
        }
    }
    void printBook();
};