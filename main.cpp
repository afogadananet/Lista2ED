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
    
    cout << endl;
    cout << "Teste de timestamp" << endl; 
    Order venda1(1,'S',valor, 11);
    Order pedido(2, 'B', valor, 10); 
    Order pedido1(4,'B', valor, 12);

    skoob.submit(pedido);
    skoob.submit(pedido1);
    skoob.submit(venda1);

    skoob.printBuyOrders(); 
    skoob.printSellOrders(); 
    skoob.printTransactions(); 

    cout << endl;
    cout << "Teste de valor" << endl; 
    Order venda2(3,'S',valor+1, 20);
    Order pedido2(4, 'B', valor+15, 21); 
    Order pedido3(5,'B', valor-2, 22);

    skoob.submit(venda2);
    skoob.submit(pedido2);
    skoob.submit(pedido3);

    skoob.printBuyOrders(); 
    skoob.printSellOrders(); 
    skoob.printTransactions(); 

    cout << endl;
    cout << "Teste de cancelar" << endl; 
    Order venda7(6,'S',valor+10, 20);
    skoob.submit(venda7);
    skoob.printSellOrders(); 
    skoob.cancel(6);
    skoob.printSellOrders();

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
