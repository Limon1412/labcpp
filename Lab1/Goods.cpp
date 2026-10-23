#include "Goods.h"

#include <iostream>
#include <format>
#include <cstring>

Goods::Goods() 
  : name(new char[1]{'\0'}),
    receiptDate(""),
    price(0),
    quantity(0) {
    std::cout << "Default constructor\n";
}

Goods::Goods(
    const char* name,
    std::string receiptDate,
    double price,
    int quantity) 
  : name(new char[std::strlen(name) + 1]),
    receiptDate(receiptDate),
    price(price > 0 ? price : 0),
    quantity(quantity > 0 ? quantity : 0) {
    std::strcpy(this->name, name);

    std::cout << "Parameterized constructor: " << name << '\n';
}

Goods::Goods(const Goods& other) 
  : name(new char[std::strlen(other.name) + 1]),
    receiptDate(other.receiptDate),
    price(other.price),
    quantity(other.quantity) {
    std::strcpy(name, other.name);

    std::cout << "Copy constructor: " << name << '\n';
}

Goods::~Goods() {
    std::cout << "Destuction " << name << "\n";

    delete[] name;
}

Goods& Goods::operator=(const Goods& other) {
    if (this != &other) {
        char* newName = new char[std::strlen(other.name) + 1];

        std::strcpy(newName, other.name);

        delete[] name;

        name = newName;
        receiptDate = other.receiptDate;
        price = other.price;
        quantity = other.quantity;
    }
    
    return *this;
}

void Goods::setPrice(double price) {
    if (price > 0) {
        this->price = price;
    }
}

void Goods::setQuantity(int quantity) {
    if (quantity >= 0) {
        this->quantity = quantity;
    }
}

const char* Goods::getName() const {
    return name;
}

double Goods::getPrice() const {
    return price;
}

int Goods::getQuantity() const {
    return quantity;
}

void Goods::markup(double percent) {
    if(percent <= 0) {
        return;
    }
    price = price * (1 + percent/100);
}

void Goods::discount(double percent) {
    if (percent > 100 || percent < 0) {
        return;
    }
    price = price * (1 - percent/100);
}

std::string Goods::toString() const {
    return std::format("Товар: {},\nДата получения: {},\nЦена: {},\nКоличество: {}", name, receiptDate, price, quantity);
}


