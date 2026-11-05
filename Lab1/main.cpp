#include "Goods.h"

#include <iostream>


int main() {
    //lab1
    std::cout << "----------------Lab1------------------\n";
    Goods goods1;
    std::cout << goods1.toString() << "\n\n";

    Goods goods2("Ноутбук", "10.10.2010", 15000, 15);


    goods2.setPrice(20000);
    std::cout << goods2.toString() << "\n\n";
    goods2.setQuantity(10);
    std::cout << goods2.toString() << "\n\n";
    
    goods2.markup(15);
    std::cout << goods2.getPrice() << "\n\n";
    goods2.discount(10);
    std::cout << goods2.getPrice() << "\n\n"; 

    Goods goods3 = goods2;

    if (goods2.getName() != goods3.getName()) {
        std::cout << "Different addresses" << "\n";
    } else {
        std::cout << "Same addresses" << "\n";
    }
     
    goods1 = goods3;
    std::cout << "Название: " << goods1.getName() << "\nЦена: " << goods1.getPrice() << "\nКоличество: " << goods1.getQuantity() << "\n";

    Goods* goods4 = new Goods("Пк", "09.09.2009", 30000, 5);
    std::cout << goods4->toString() << "\n\n";


    //lab2
    std::cout << "----------------Lab2------------------\n";
    std::cout << "Объекты до создания 5-8: " << Goods::alive() << "\n";
    goods1.setPrice(100);
    goods1.setQuantity(10);
    goods3.setPrice(200);
    goods3.setQuantity(2); //goods1 и goods2 одинаковые кроме количества и цены

    Goods goods5 = goods1 + goods3;
    Goods goods6 = goods1 - goods3;

    std::cout << "a + b " << goods5.toString() << "\n"; 
    std::cout << "a - b" << goods6.toString() << "\n\n";

    std::cout<< static_cast<double>(goods1) << "\n\n";

    Goods goods7 = goods1++;
    std::cout << "copy: " << goods7.toString() <<"\n";
    std::cout << "original: " << goods1.toString() <<"\n\n";

    Goods goods8 = ++goods1;
    std::cout << "copy: " << goods8.toString() <<"\n";
    std::cout << "original: " << goods1.toString() <<"\n\n";

    std::cout << "Объекты после создания 5-8: " << Goods::alive() << "\n";


    delete goods4;

    std::cout << "Объекты после удаления goods4: " << Goods::alive() << "\n";
}
