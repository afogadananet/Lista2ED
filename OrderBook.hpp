#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP
#include <iostream>

#include "Order.hpp"
#include "Transaction.hpp"

struct ArrayDinamicoOrders {
    int capacidade;
    int tamanho;
    Order* dados; 
};

struct ArrayDinamicoTrans {
    int capacidade;
    int tamanho;
    Transaction* dados; 
};

ArrayDinamicoOrders* inicializar(int capacidade);
void deletar(ArrayDinamicoOrders* p);
void remove(ArrayDinamicoOrders* p, Order pedido);
void append(ArrayDinamicoOrders* p, Order pedido);
void resize(ArrayDinamicoOrders* p, int nova_capacidade);

ArrayDinamicoTrans* inicializar_trans(int capacidade);
void deletar_trans(ArrayDinamicoTrans* p);
void append_trans(ArrayDinamicoTrans* p, Transaction pedido);
void resize_trans(ArrayDinamicoTrans* p, int nova_capacidade);


class OrderBook {
private:
    ArrayDinamicoOrders* buys; 
    ArrayDinamicoOrders* sells; 
    ArrayDinamicoTrans* transactions; 

public:

    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    bool executa_ordem(Order order, char type);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();

    // Outros métodos auxiliares, se necessário
};

#endif