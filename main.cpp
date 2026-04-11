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
    skoob.submit(pedido1);
    skoob.printBuyOrders(); 
    skoob.submit(venda1);

    skoob.printSellOrders();
    skoob.printBuyOrders(); 
    skoob.printTransactions();


    int b; 
    skoob.getBuyOrders(&b); 
    cout << b << endl;

    int a; 
    skoob.getTransactions(&a); 
    cout << a << endl;

    int c; 
    skoob.getSellOrders(&c); 
    cout << c << endl;

    return 0;
}
