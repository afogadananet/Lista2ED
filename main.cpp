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
    Order pedido(2,'S',valor,1);
    Order pedido2(1,'B',valor-1,0);
    Order pedido3(5,'B',valor+1,12);
    Order pedidu(15,'B',valor,1);
    Order venda(3,'S', valor-2, 3);
    Order venda1(6,'S', valor-3, 13);
    Order vendas1(16,'S', valor+10, 5);
    Order vendas2(16,'S', valor+10, 6);
    Order compra(11,'B', valor + 11, 1); 

    skoob.submit(pedido);
    skoob.submit(pedido2);
    skoob.submit(venda);

    skoob.printSellOrders();
    skoob.printBuyOrders(); 
    skoob.printTransactions();

    skoob.submit(pedido3); 
    skoob.submit(venda1);
    skoob.cancel(6); 
    
    skoob.submit(pedidu); 
    skoob.submit(vendas1); 
    skoob.submit(vendas2);



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
