#include <iostream>
using namespace std;

#include "Order.hpp" 
#include "Transaction.hpp"
#include "OrderBook.hpp" 

ArrayDinamicoOrders* inicializar(int capacidade){
    ArrayDinamicoOrders* arr = new ArrayDinamicoOrders;
    arr->dados = new Order[capacidade];
    arr->capacidade = capacidade;
    arr->tamanho = 0;
    return arr;
}

void deletar(ArrayDinamicoOrders* p) {
    delete[] p->dados;
    delete p;
}

void remove(ArrayDinamicoOrders* p, Order pedido){
    int idx_pdd;
    for (int idx = 0; idx < p->capacidade; idx++){
        if (p->dados[idx].getId() == pedido.getId()){
            idx_pdd = idx; 
        } 
    }
    for (int j = idx_pdd; j< p->tamanho; j++){
        p->dados[j] = p->dados[j+1]; 
    }
    p->tamanho--; 
}

void append(ArrayDinamicoOrders* p, Order pedido) {
    if(p->capacidade == p->tamanho) { 
        resize(p, 2 * p->capacidade);
    }
    p->dados[p->tamanho] = pedido;
    p->tamanho++;
}

void resize(ArrayDinamicoOrders* p, int nova_capacidade) {
    Order* novo_dados = new Order[nova_capacidade];
    for(int i = 0; i < p->capacidade; i++) {
        novo_dados[i] = p->dados[i];
    }
    delete[] p->dados;
    p->dados = novo_dados;
    p->capacidade = nova_capacidade;
}

ArrayDinamicoTrans* inicializar_trans(int capacidade) {
    ArrayDinamicoTrans* arr = new ArrayDinamicoTrans;
    arr->dados = new Transaction[capacidade];
    arr->capacidade = capacidade;
    arr->tamanho = 0;
    return arr;
}

void deletar_trans(ArrayDinamicoTrans* p) {
    delete[] p->dados;
    delete p;
}

void append_trans(ArrayDinamicoTrans* p, Transaction trans) {
    if(p->capacidade == p->tamanho) { 
        resize_trans(p, 2 * p->capacidade);
    }
    p->dados[p->tamanho] = trans;
    p->tamanho++;
}

void resize_trans(ArrayDinamicoTrans* p, int nova_capacidade) {
    Transaction* novo_dados = new Transaction[nova_capacidade];
    for(int i = 0; i < p->capacidade; i++) {
        novo_dados[i] = p->dados[i];
    }
    delete[] p->dados;
    p->dados = novo_dados;
    p->capacidade = nova_capacidade;
}

OrderBook::OrderBook(){}

OrderBook::~OrderBook(){}

Order* OrderBook::getBuyOrders(int* n){
    if(this->buys->tamanho == 0){
        *n = 0; 
        return nullptr; 
    } 
    *n = this->buys->tamanho; 
    return this->buys->dados;
}

Order* OrderBook::getSellOrders(int* n){    
    if(this->sells->tamanho == 0){
        *n = 0; 
        return nullptr; 
    } 
    *n = this->sells->tamanho; 
    return this->sells->dados;
}

Transaction* OrderBook::getTransactions(int* n){
    if(this->transactions->tamanho == 0){
        *n = 0; 
        return nullptr; 
    } 
    *n = this->transactions->tamanho; 
    return this->transactions->dados; 
}

bool submit(Order order){
    
};

void OrderBook::printBuyOrders(){
    for(int i =0; i<this->buys->tamanho; i++){
        cout << "[" << this->buys->dados[i].getId() << "|" << this->buys->dados[i].getPrice() << "|" << this->buys->dados[i].getTimestamp() <<"]" << endl; 
    }
}

void OrderBook::printSellOrders(){
    for(int i =0; i<this->sells->tamanho; i++){
        cout << "[" << this->sells->dados[i].getId() << "|" << this->sells->dados[i].getPrice() << "|" << this->sells->dados[i].getTimestamp() <<"]" << endl; 
    }
}

void OrderBook::printTransactions(){
    for(int i =0; i<this->transactions->tamanho; i++){
        cout << "[" << this->transactions->dados[i].getBuyOrderId() << "|" << this->transactions->dados[i].getSellOrderId() << "|" << this->transactions->dados[i].getExecutionPrice() <<"]" << endl; 
    }
}

