#include "GoodsService.h"

#include <iostream>
#include <fstream>
#include <cstring>

void GoodsService::addGood(const Goods& good) {
    goods.push_back(good);
}

const Goods& GoodsService::getGoodByIndex(int index) const {
    return goods.at(index);
}

void GoodsService::deleteLastGood() {
    if (!isEmpty()) {
        goods.pop_back();
    }
}
 
void GoodsService::deleteGoodByIndex(int index) {
    if (isEmpty()) {
        return;
    }

    if (index < 0 || index >= vectorSize()) {
        return;
    }

    goods.erase(goods.begin() + index);
}

void GoodsService::printAllGoods() const {
    for (const Goods& item : goods) {
        std::cout << item << '\n';
    }
}

void GoodsService::vectorClear() {
    goods.clear();
}

int GoodsService::vectorSize() const {
    return goods.size();
}

bool GoodsService::isEmpty() const {
    return goods.empty();
}

bool GoodsService::writeToFile(const std::string& file) const {
    std::ofstream out(file);
    if (!out) {
        return false;
    }

    out.precision(17);

    for (const Goods& item : goods) {
        out << item << '\n';
    }

    out.close();
    return static_cast<bool>(out);
}

bool GoodsService::loadFromFile(const std::string& file) {
    std::ifstream in(file);
    if (!in) {
        return false;
    }

    Goods item;
    while (true) {
        in >> std::ws;

        if (in.bad()) {
            return false;
        }

        if (in.eof()) {
            return true;
        }

        if (!(in >> item)) {
            return false;
        }

        addGood(item);
    }   
}

const int maxStringLength = 10000;

bool GoodsService::writeToFileBinary(const std::string& file) const {
    for (const Goods& good : goods) {
        if (std::strlen(good.getName()) > maxStringLength ||
            good.getReceiptDate().size() > maxStringLength) {
                return false;
            }
    }

    std::ofstream outBinary(file, std::ios::binary);

    if (!outBinary) {
        return false;
    }

    int quantityGoods = vectorSize();
    outBinary.write(reinterpret_cast<const char*>(&quantityGoods), sizeof(quantityGoods));

    for (const Goods& good : goods) {
        int nameLength = std::strlen(good.getName());
        outBinary.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
        outBinary.write(good.getName(), nameLength);

        int dateLength = good.getReceiptDate().size();
        outBinary.write(reinterpret_cast<const char*>(&dateLength), sizeof(dateLength));
        outBinary.write(good.getReceiptDate().c_str(), dateLength);

        double price = good.getPrice();
        outBinary.write(reinterpret_cast<const char*>(&price), sizeof(price));

        int quantity = good.getQuantity();
        outBinary.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
    }

    outBinary.close();
    return static_cast<bool>(outBinary);
}

bool GoodsService::loadFromFileBinary(const std::string& file) {
    std::ifstream inBinary(file, std::ios::binary);

    if (!inBinary) {
        return false;
    }

    int quantityGoods = 0;
    if(!inBinary.read(reinterpret_cast<char*>(&quantityGoods), sizeof(quantityGoods)) ||
        quantityGoods < 0) {
            return false;   
    }

    for (int i = 0; i < quantityGoods; i++) {
        int nameLength = 0;
        if(!inBinary.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength)) ||
           nameLength < 0 || nameLength > maxStringLength) {
                return false;
        }
        std::string name(nameLength, '\0');
        if (!inBinary.read(name.data(), nameLength)) {
            return false;
        }

        int dateLength = 0;
        if (!inBinary.read(reinterpret_cast<char*>(&dateLength), sizeof(dateLength)) ||
            dateLength < 0 || dateLength > maxStringLength) {
                return false;
        }
        std::string date(dateLength, '\0');
        if (!inBinary.read(date.data(), dateLength)) {
            return false;
        }
        
        double price = 0;
        if (!inBinary.read(reinterpret_cast<char*>(&price), sizeof(price))) {
            return false;
        }

        int quantity = 0;
        if (!inBinary.read(reinterpret_cast<char*>(&quantity), sizeof(quantity))) {
            return false;
        }

        if(price < 0 || quantity < 0 ) {
            return false;
        }

        Goods good(name.c_str(), date, price, quantity);
        addGood(good);
    }

    return true;
}
