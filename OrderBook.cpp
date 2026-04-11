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
    Order order2;    
    if(type == 'S'){ // se for do tipo sell 

        if (this->buys->tamanho != 0){ 
            order2 = this->buys->dados[0]; 

            for(int i = 1; i< this->buys->tamanho; i++){ 
                if (this->buys->dados[i].getPrice() > order2.getPrice()){
                    order2 = this->buys->dados[i];          
                }
                else {if (this->buys->dados[i].getPrice() == order2.getPrice()){
                    if (this->buys->dados[i].getTimestamp() < order2.getTimestamp()){
                        order2 = this->buys->dados[i];     
                    }     
                }}
            }
            if (order2.getPrice() >= order.getPrice()){
                remove(this->buys, order2); 
                append_trans(this->transactions, Transaction(order2.getId(), order.getId(), order2.getPrice())); 
                return true; 
            } 
        }
        append(this->sells, order);
        return false;
    } 
    if (this->sells->tamanho != 0){
        order2 = this->sells->dados[0]; 
        for(int i = 1; i< this->sells->tamanho; i++){
            if (this->sells->dados[i].getPrice() < order2.getPrice()){ 
                order2 = this->sells->dados[i]; 
            }
            else{if (this->sells->dados[i].getPrice() == order2.getPrice()){
                    if (this->sells->dados[i].getTimestamp() < order2.getTimestamp()){
                        order2 = this->sells->dados[i];     
                }     
            }}
        }
        if (order2.getPrice() <= order.getPrice()){
            remove(this->sells, order2); 
            append_trans(this->transactions, Transaction(order2.getId(), order.getId(), order2.getPrice())); 
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

