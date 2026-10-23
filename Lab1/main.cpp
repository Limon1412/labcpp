#include "Goods.h"

#include <iostream>


int main() {
    // Вызывается конструктор по умолчанию.
    Goods goods1;
    std::cout << goods1.toString() << "\n\n";

    // Вызывается конструктор с параметрами.
    Goods goods2("Ноутбук", "10.10.2010", 15000, 15);


    goods2.setPrice(20000);
    std::cout << goods2.toString() << "\n\n";
    goods2.setQuantity(10);
    std::cout << goods2.toString() << "\n\n";
    
    goods2.markup(15);
    std::cout << goods2.getPrice() << "\n\n";
    goods2.discount(10);
    std::cout << goods2.getPrice() << "\n\n"; 

    // Создаётся новый объект( конструктор копирования).
    Goods goods3 = goods2;
    
    // goods1 уже существует вызывается оператор присваивания.
    goods1 = goods3;
    // Демонстрация всех трёх геттеров.
    std::cout << "Название: " << goods1.getName() << "\nЦена: " << goods1.getPrice() << "\nКоличество: " << goods1.getQuantity() << "\n";

    // new создаёт объект в динамической памяти и вызывает конструктор с параметрами.
    Goods* goods4 = new Goods("Пк", "09.09.2009", 30000, 5);
    std::cout << goods4->toString() << "\n\n";
    // delete вызывает деструктор goods4 и освобождает память самого объекта.
    delete goods4;
}
