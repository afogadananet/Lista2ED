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
    Order pedido(2,'S',valor,1);
    Order pedido2(1,'B',valor-1,1);
    Order venda(3,'S', valor-2, 4);
    Order pedido3(5,'B',valor+1,1);
    Order venda1(6,'S', valor-3, 4);
    Order pedidu(5,'B',valor,1);
    Order vendas1(6,'S', valor+10, 4);

    skoob.submit(pedido);

    skoob.submit(pedido2);
    skoob.submit(venda);
    skoob.submit(pedido3); 
    skoob.submit(venda1);
    skoob.cancel(6); 
    skoob.submit(pedidu); 
    skoob.submit(vendas1); 
    
    skoob.printSellOrders();
    skoob.printBuyOrders(); 
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
