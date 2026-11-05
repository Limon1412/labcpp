#include "Goods.h"

#include <iostream>
#include <format>
#include <cstring>
#include <stdexcept>

Goods::Goods() 
  : name(new char[1]{'\0'}),
    receiptDate(""),
    price(0),
    quantity(0) {
    aliveObjects++;
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
    aliveObjects++;
    std::strcpy(this->name, name);

    std::cout << "Parameterized constructor: " << name << '\n';
}

Goods::Goods(const Goods& other) 
  : name(new char[std::strlen(other.name) + 1]),
    receiptDate(other.receiptDate),
    price(other.price),
    quantity(other.quantity) {
    aliveObjects++;
    std::strcpy(name, other.name);

    std::cout << "Copy constructor: " << name << '\n';
}

Goods::~Goods() {
    aliveObjects--;
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

Goods Goods::operator+(const Goods& other) const {
    if (std::strcmp(this->getName(), other.getName()) != 0 ||
       this->getReceiptDate() != other.getReceiptDate()) {
        throw std::invalid_argument("it's not possible to combine these objects\n");
    }
    if (this->getQuantity() == 0 && other.getQuantity() == 0) {
        throw std::invalid_argument("could not calculate new price cause both quantiny are zero");
    }

    double newPrice = (this->getPrice() * this->getQuantity() + other.getPrice() * other.getQuantity()) /(this->getQuantity() + other.getQuantity());
    int newQuantity = this->getQuantity() + other.getQuantity();

    return Goods(this->getName(), this->getReceiptDate(), newPrice, newQuantity);
}

Goods operator-(const Goods& left, const Goods& right) {
    if (std::strcmp(left.getName(), right.getName()) != 0 ||
       left.getReceiptDate() != right.getReceiptDate()) {
        throw std::invalid_argument("it's not possible to subtract these objects\n");
    }

    if (left.getQuantity() - right.getQuantity() < 0) {
        throw std::invalid_argument("left operand has no enough quantity");
    }

    double newPrice = left.getPrice();
    int newQuantity = left.getQuantity() - right.getQuantity();

    return Goods(left.getName(), left.getReceiptDate(), newPrice, newQuantity);
}

Goods& Goods::operator++() {
    int quantity = this->getQuantity();
    this->setQuantity(++quantity);
    return *this;
}

Goods Goods::operator++(int) {
    Goods copyGoods = *this;
    int quantity = this->getQuantity();
    this->setQuantity(++quantity);
    return copyGoods;
}

Goods::operator double() const {
    return this->getPrice() * this->getQuantity();
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

std::string Goods::getReceiptDate() const {
    return receiptDate;
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

int Goods::alive() {
    return aliveObjects;
}

