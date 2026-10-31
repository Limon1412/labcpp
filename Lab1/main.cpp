#include "Goods.h"

#include <iostream>


int main() {
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
    delete goods4;
}
