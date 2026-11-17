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

std::ostream& operator<<(std::ostream& os, const Goods& item) {
    os << item.getName() << '|'
        << item.getReceiptDate() << '|'
        << item.getPrice() << '|'
        << item.getQuantity();

    return os;
}

std::istream& operator>>(std::istream& is, Goods& item) {
    std::string name, receiptDate;
    double price;
    int quantity;
    char separator;

    if (getline(is >> std::ws, name, '|') &&
        getline(is, receiptDate, '|') &&
        (is >> price) &&
        is.get(separator) && separator == '|' &&
        (is >> quantity) &&
        price >= 0 && quantity >= 0) {
        item = Goods(name.c_str(), receiptDate, price, quantity);
    } else {
        is.setstate(std::ios::failbit); 
    }

    return is;
}

std::ofstream& operator<<(std::ofstream& os, const Goods& item) {
    int nameLength = std::strlen(item.getName());
    os.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    os.write(item.getName(), nameLength);

    int dateLength = item.getReceiptDate().size();
    os.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
    os.write(item.getReceiptDate().c_str(), dateLength);

    double price = item.getPrice();
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));

    int quantity = item.getQuantity();
    os.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));

    return os;
}

std::ifstream& operator>>(std::ifstream& is, Goods& item) {
    int nameLength = 0;
    if(!is.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)) ||
        nameLength < 0 || nameLength > Goods::maxStringLength) {
            is.setstate(std::ios::failbit);
            return is;
    }
    std::string name(nameLength, '\0');
    if (!is.read(name.data(), nameLength)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    int dateLength = 0;
    if (!is.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength)) ||
        dateLength < 0 || dateLength > Goods::maxStringLength) {
            is.setstate(std::ios::failbit);
            return is;
    }
    std::string date(dateLength, '\0');
    if (!is.read(date.data(), dateLength)) {
        is.setstate(std::ios::failbit);
        return is;
    }
    
    double price = 0;
    if (!is.read(reinterpret_cast<char*>(&price), sizeof(price))) {
        is.setstate(std::ios::failbit);
        return is;
    }

    int quantity = 0;
    if (!is.read(reinterpret_cast<char*>(&quantity), sizeof(quantity))) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if(price < 0 || quantity < 0 ) {
        is.setstate(std::ios::failbit);
        return is;
    }

    item = Goods(name.c_str(), date, price, quantity);
    return is;
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

