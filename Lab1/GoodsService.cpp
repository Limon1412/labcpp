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
    std::ostream& textOut = out;

    for (const Goods& item : goods) {
        textOut << item << '\n';
    }

    out.close();
    return static_cast<bool>(out);
}

bool GoodsService::loadFromFile(const std::string& file) {
    std::ifstream in(file);
    if (!in) {
        return false;
    }

    std::istream& textIn = in;
    Goods item;
    while (true) {
        textIn >> std::ws;

        if (textIn.bad()) {
            return false;
        }

        if (textIn.eof()) {
            return true;
        }

        if (!(textIn >> item)) {
            return false;
        }

        addGood(item);
    }   
}


bool GoodsService::writeToFileBinary(const std::string& file) const {
    for (const Goods& good : goods) {
        if (std::strlen(good.getName()) > Goods::maxStringLength ||
            good.getReceiptDate().size() > Goods::maxStringLength) {
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
        outBinary << good;
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
        Goods good;
        if (!(inBinary >> good)) {
            return false;
        }

        addGood(good);
    }

    return true;
}
