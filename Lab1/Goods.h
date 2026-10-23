#pragma once
#include <string>

class Goods {
private:
    char* name;                // Собственный массив символов с названием товара(динамич).
    std::string receiptDate;  // Дата получения товара.
    double price;             // Цена одного товара.
    int quantity;             // Количество товара.

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
    
    // Возвращают поля приватные, для чтения
    const char* getName() const;
    double getPrice() const;
    int getQuantity() const;

    std::string toString() const; // Возвращает строку со всеми полями товара.
    void markup(double percent); // Повышает текущую цену на заданный процент.
    void discount(double percent); // Снижает текущую цену на процент от 0 до 100.

    Goods& operator=(const Goods& other); // Копирует данные в существующий объект.
};
