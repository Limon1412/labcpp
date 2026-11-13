#include "Goods.h"
#include "ChildGoods.h"
#include "MilkGoods.h"
#include "GoodsService.h"

#include <iostream>
#include <cstring>


int main() {
    //lab1
    std::cout << "----------------Lab1------------------\n";
    Goods goods1;
    std::cout << goods1.toString() << "\n\n";

    Goods goods2("Ноутбук", "2010.10.10", 15000, 15);


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

    Goods* goods4 = new Goods("Пк", "2009.09.09", 30000, 5);
    std::cout << goods4->toString() << "\n\n";


    //lab2
    std::cout << "----------------Lab2------------------\n";
    std::cout << "Объекты до создания 5-8: " << Goods::alive() << "\n";
    goods1.setPrice(100);
    goods1.setQuantity(10);
    goods3.setPrice(200);
    goods3.setQuantity(2); //goods1 и goods3 одинаковые кроме количества и цены

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

    //lab3
    std::cout << "----------------Lab3------------------\n";
    Goods goodInOut;

    std::cout << "ОПЕРАТОРЫ << И >>\n\n";

    std::cout << "Введите товар в формате:\n"
              << "Название|Дата|Цена|Количество\n";

    if (std::cin >> goodInOut) {
        std::cout << "Вы ввели:\n" << goodInOut << '\n';
    } else {
        std::cout << "Ошибка ввода!\n";
    }

    std::cout << "ТЕКСТОВЫЕ ФАЙЛЫ\n\n";

    GoodsService goodsService1;
    goodsService1.addGood(Goods("Телефон", "2007.12.14", 150000, 25));
    goodsService1.addGood(Goods("Ноутбук", "2007.12.15", 56789, 12));
    goodsService1.addGood(Goods("Планшет", "2007.12.16", 78123, 9));
    if (goodsService1.writeToFile("goods.txt")) {
        std::cout << "Товары сохранены\n";
    } else {
        std::cout << "Ошибка сохранения\n";
    }

    GoodsService goodsService2;
    if (goodsService2.loadFromFile("goods.txt")) {
        goodsService2.printAllGoods();
    } else {
        std::cout << "Ошибка загрузки\n";
    }

    std::cout << "БИНАРНЫЕ ФАЙЛЫ\n\n";
    
    if (goodsService1.writeToFileBinary("goods.dat")) {
        std::cout << "Товары сохранены(БИНАРНЫЙ)\n";
    } else {
        std::cout << "Ошибка сохранения(БИНАРНЫЙ)\n";
    }

    goodsService2.vectorClear();
    if (goodsService2.loadFromFileBinary("goods.dat")) {
        goodsService2.printAllGoods();
    } else {
        std::cout << "Ошибка загрузки(БИНАРНЫЙ)\n";
    }

    //lab4
    std::cout << "----------------Lab4------------------\n";
    std::cout << "ДЕТСКИЕ ТОВАРЫ\n\n";

    ChildGoods childGood("Конструктор", "2022.02.22", 2500, 10, 6, "building blocks");
    std::cout << childGood.toString();

    std::cout << "проверка при 5 годах:";
    std::cout << childGood.checkAge(5) << '\n';

    std::cout << "проверка при 6 годах:";
    std::cout << childGood.checkAge(6) << '\n';

    ChildGoods toyCopy = childGood;
    std::cout << "COPY: " << toyCopy.toString() << '\n';
    if (toyCopy.getName() == childGood.getName()) {
        std::cout << "the same addresses of string`s names(toy)\n";
    } else {
        std::cout << "different addresses of string`s names(toy)\n";
    }

    Goods& virtualCallToy = childGood;
    std::cout << virtualCallToy.toString() << '\n';

    std::cout << "МОЛОЧНЫЕ ТОВАРЫ\n\n";

    MilkGoods milkGood("молоко","2026.11.13", 100, 19, "2026.11.15");
    std::cout << "ПЕРЕСЧЕТ ЦЕНЫ ПРИ НЕИСТЕЧЕННОМ СРОКЕ: ";
    std::cout << milkGood.recalculationPrice("2026.11.15", 20) << '\n';
    std::cout << milkGood.getPrice() << '\n';

    std::cout << "ПЕРЕСЧЕТ ЦЕНЫ ПРИ ИСТЕЧЕННОМ СРОКЕ: ";
    std::cout << milkGood.recalculationPrice("2026.11.16", 20) << '\n';
    std::cout << milkGood.getPrice() << '\n';

    std::cout << "ПЕРЕСЧЕТ ЦЕНЫ ПРИ ИСТЕЧЕННОМ СРОКЕ НО ПОВТОРНО: ";
    std::cout << milkGood.recalculationPrice("2026.11.16", 20) << '\n';
    std::cout << milkGood.getPrice() << '\n';

    MilkGoods milkCopy = milkGood;
    if (milkCopy.getName() == milkGood.getName()) {
        std::cout << "the same addresses of string`s names(milk)\n";
    } else {
        std::cout << "different addresses of string`s names(milk)\n";
    }

    std::cout << "Copy: " << milkCopy.toString() << '\n';

    Goods& virtualCallMilk = milkGood;
    std::cout << virtualCallMilk.toString() << '\n'; 
}
