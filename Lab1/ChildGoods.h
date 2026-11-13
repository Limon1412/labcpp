#pragma once

#include "Goods.h"

#include <string>


class ChildGoods : public Goods {
private:
    int minAge;
    std::string toyType;

public:
    ChildGoods();
    ChildGoods(const char* name,
          std::string receiptDate,
          double price, 
          int quantity,
          int minAge,
          std::string toyType);


    int getMinAge() const;
    std::string getToyType() const;

    bool checkAge(int age) const;

    std::string toString() const override; 
};