#pragma once

struct Order
{
    int id;
    double price;
    int quantity;
    char side; // B or S (Buy or Sell)
};