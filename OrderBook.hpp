#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#include <iostream>

#include "Order.hpp"
#include "Transaction.hpp"

struct ArrayDinamico {
    int capacidade;
    int tamanho;
    Order* dados; 
};

ArrayDinamico* inicializar(int capacidade);
void deletar(ArrayDinamico* p);
void remove(ArrayDinamico* p, Order pedido);
void append(ArrayDinamico* p, Order pedido);
void resize(ArrayDinamico* p, int nova_capacidade);

class OrderBook {
private:


public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};

#endif