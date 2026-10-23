#pragma once
#include <string>

// Товар с наименованием в динамической памяти.
class Goods {
private:
    char* name;                // Собственный массив символов с названием товара.
    std::string receiptDate;  // Дата получения товара.
    double price;             // Цена одной единицы товара.
    int quantity;             // Количество единиц товара.

public:
    Goods(); // Создаёт пустой товар с нулевыми ценой и количеством.
    // Создаёт товар по переданным данным, копируя название в свой массив.
    Goods(const char* name,
          std::string receiptDate,
          double price,
          int quantity);
    Goods(const Goods& other); // Создаёт независимую копию товара.
    ~Goods(); // Освобождает массив с названием товара.

    void setPrice(double price);       // Устанавливает положительную цену.
    void setQuantity(int quantity);    // Устанавливает неотрицательное количество.
    
    // Чтение полей без изменения объекта.
    const char* getName() const;
    double getPrice() const;
    int getQuantity() const;

    std::string toString() const; // Возвращает строку со всеми полями товара.
    void markup(double percent); // Повышает текущую цену на заданный процент.
    void discount(double percent); // Снижает текущую цену на процент от 0 до 100.

    Goods& operator=(const Goods& other); // Копирует данные в существующий объект.
};
