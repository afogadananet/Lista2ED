#include "Order.hpp"
#include "OrderBook.hpp"
#include "Transaction.hpp"

#include <iostream>
using namespace std;

int main(){
    OrderBook skoob; 
    skoob.printSellOrders();
    skoob.printBuyOrders();       
    skoob.printTransactions();

    float valor = 10; 
    
    // testes do valor 
    Order venda1(1,'S',valor, 11);
    Order pedido1(2, 'B', valor, 10); 
    Order pedido(4,'B', valor, 12);

    skoob.submit(pedido);
    skoob.submit(pedido1);
    skoob.submit(venda1);

    skoob.printBuyOrders(); 
    skoob.printSellOrders(); 
    skoob.printTransactions(); 

    int a; 
    skoob.getBuyOrders(&a); 
    cout << a << endl;

    int b; 
    skoob.getSellOrders(&b); 
    cout << b << endl;

    int c; 
    skoob.getTransactions(&c); 
    cout << c << endl;

    return 0;
}
