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
    Order venda1(10,'S',valor, 11);
    Order pedido(20, 'B', valor, 12); 
    Order pedido1(40,'B', valor, 14);

    skoob.submit(pedido);
    skoob.submit(venda1);
    skoob.cancel(6); 

    int b; 
    skoob.getSellOrders(&b); 
    cout << b << endl;

    int c; 
    skoob.getTransactions(&c); 
    cout << c << endl;

    return 0;
}
