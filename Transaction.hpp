#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include <iostream>

class Transaction {

private:
    int buy_order_id;
    int sell_order_id;
    float execution_price;

public:

    Transaction();
    Transaction(int buy_order_id, int sell_order_id, float execution_price);
    ~Transaction();

    int getBuyOrderId();
    int getSellOrderId();
    float getExecutionPrice();
};

#endif