#include <iostream>
using namespace std;

#include "Order.hpp" 
#include "Transaction.hpp"
#include "OrderBook.hpp" 

ArrayDinamico* inicializar(int capacidade) {
    ArrayDinamico* arr = new ArrayDinamico;
    arr->dados = new Order[capacidade];
    arr->capacidade = capacidade;
    arr->tamanho = 0;
    return arr;
}

void deletar(ArrayDinamico* p) {
    delete[] p->dados;
    delete p;
}

void remove(ArrayDinamico* p, Order pedido){
    int idx_reserva;
    for (int j = idx_reserva; j< p->tamanho; j++){
        p->dados[j] = p->dados[j+1]; 
    }
    p->tamanho--; 
}

void append(ArrayDinamico* p, Order pedido) {
    if(p->capacidade == p->tamanho) { 
        resize(p, 2 * p->capacidade);
    }
    p->dados[p->tamanho] = pedido;
    p->tamanho++;
}

void resize(ArrayDinamico* p, int nova_capacidade) {
    Order* novo_dados = new Order[nova_capacidade];
    for(int i = 0; i < p->capacidade; i++) {
        novo_dados[i] = p->dados[i];
    }
    delete[] p->dados;
    p->dados = novo_dados;
    p->capacidade = nova_capacidade;
}

OrderBook::OrderBook(){}

OrderBook::~OrderBook(){}; 

Order* OrderBook::getBuyOrders(int* n){}

Order* OrderBook::getBuyOrders(int* n){}

Order* OrderBook::getSellOrders(int* n){}

Transaction* OrderBook::getTransactions(int* n){}

void OrderBook::printBuyOrders(){
}

void OrderBook::printSellOrders(){
}

void OrderBook::printTransactions(){
}

