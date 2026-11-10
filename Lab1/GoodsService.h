#pragma once

#include "Goods.h"

#include <vector>
#include <string>


class GoodsService {
private:
    std::vector<Goods> goods;

public:
    void addGood(const Goods& good);
    const Goods& getGoodByIndex(int index) const;
    void deleteLastGood();
    void deleteGoodByIndex(int index);
    void printAllGoods() const;

    void vectorClear();
    int vectorSize() const;
    bool isEmpty() const;

    bool writeToFile(const std::string& file) const;
    bool loadFromFile(const std::string& file);
    bool writeToFileBinary(const std::string& file) const;
    bool loadFromFileBinary(const std::string& file);
};