#pragma once

#include "Goods.h"

class GoodsList {
private: 
    struct Node {
        Goods* data;
        Node* next;
    };

    Node* head = nullptr;
    int nodesCount = 0;

public:
    GoodsList() = default;
    GoodsList(const GoodsList&) = delete;
    GoodsList& operator=(const GoodsList&) = delete;

    ~GoodsList();

    void addGood(Goods& good);
    void deleteLastGood();
    void insertGood(int index, Goods& good);
    void deleteGoodByIndex(int index);
    Goods* findGoodByName(const std::string& name) const;
    void printAllGoods() const;
};