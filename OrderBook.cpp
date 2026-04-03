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

OrderBook::OrderBook(){
    this-> sells = inicializar(1); 
    this->buys = inicializar(1); 
    this -> transactions = inicializar_trans(1); 
}

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

bool OrderBook::submit(Order order){
    char type = order.getType(); 
    int value = 0; 
    int id = 0;     
    if(type == 'S'){ // se for do tipo sell 

        if (this->buys->tamanho != 0){ //se ele tá vazio ele tbm é diferente de zero, pq preencheu com lixo 
            value = this->buys->dados[0].getPrice();
            id = this->buys->dados[0].getId();

            for(int i = 1; i< this->buys->tamanho; i++){ 
                if (this->buys->dados[i].getPrice() > value){
                    value = this->buys->dados[i].getPrice();
                    id = this->buys->dados[i].getId();                    
                }
            }
            if (value >= order.getPrice()){
                remove(this->buys, order); 
                append_trans(this->transactions, Transaction(id, order.getId(), value)); 
                return true; 
            } 
        }
        append(this->sells, order);
        return false;
    } 
    if (this->sells->tamanho != 0){
        value = this->sells->dados[0].getPrice();
        id = this->sells->dados[0].getId();
        for(int i = 1; i< this->sells->tamanho; i++){
            cout << "for sells" << endl;
            if (this->sells->dados[i].getPrice() < value){ 
                value = this->sells->dados[i].getPrice();
                id = this->sells->dados[i].getId();
            }
        }
        if (value <= order.getPrice()){
            remove(this->sells, order); 
            append_trans(this->transactions, Transaction(id, order.getId(), value)); 
            return true; 
        }
    }
    append(this->buys, order);
    return false; 
}

bool OrderBook::cancel(int id){
    for (int i = 0; i < this->sells->tamanho; i++){
        if (this->sells->dados[i].getId() == id){
            remove(sells, this->sells->dados[i]);
            return true;
        }
    }
    for (int i = 0; i<this->buys->tamanho; i++){
        if(this->buys->dados[i].getId() == id){
            remove(buys, this->buys->dados[i]);
            return true;
        }
    }
    return false;
}


void OrderBook::printBuyOrders(){
    cout << "Buy Orders: " << endl; 
    if (this->buys->tamanho == 0){
        cout << "(empty)" << endl; 
    }
    else{
    for(int i =0; i<this->buys->tamanho; i++){
        cout << "[ " << this->buys->dados[i].getId() << " | " << this->buys->dados[i].getPrice() << " | " << this->buys->dados[i].getTimestamp() <<" ] " << endl; 
    }}
}

void OrderBook::printSellOrders(){
    cout << "Sell Orders: " << endl; 
    if (this->sells->tamanho == 0){
        cout << "(empty)" << endl;
    } 
    else{
    for(int i =0; i<this->sells->tamanho; i++){
        cout << "[ " << this->sells->dados[i].getId() << " | " << this->sells->dados[i].getPrice() << " | " << this->sells->dados[i].getTimestamp() <<" ]" << endl; 
    }}
}

void OrderBook::printTransactions(){
    cout << "Transactions: " << endl; 
    
    if (this->transactions->tamanho == 0){ // TAMANHO ESTÁ SENDO INICIALIZANDO COMO 1?? 
        cout << "(empty)" << endl;
    } 
    else{
    for(int i = 0; i<this->transactions->tamanho; i++){
        cout << "[ " << this->transactions->dados[i].getBuyOrderId() <<" | " << this->transactions->dados[i].getSellOrderId() <<  " | "  << this->transactions->dados[i].getExecutionPrice() <<" ]" << endl; 
    }}
}

