#include "ChildGoods.h"

#include <format>


ChildGoods::ChildGoods()
            : Goods() {
    minAge = 0;
    toyType = "";
}

ChildGoods::ChildGoods(
    const char* name,
    std::string receiptDate,
    double price,
    int quantity,
    int minAge,
    std::string toyType) 
   : Goods(name, receiptDate, price, quantity),
     minAge(minAge),
     toyType(toyType) {}

bool ChildGoods::checkAge(int age) const{
    return age >= minAge;
}

int ChildGoods::getMinAge() const {
    return minAge;
}

std::string ChildGoods::getToyType() const {
    return toyType;
}

std::string ChildGoods::toString() const {
    return std::format("{},\nДетская игрушка\nТип: {}\nМинимальный возраст: {}\n", Goods::toString(), getToyType(), getMinAge());
}