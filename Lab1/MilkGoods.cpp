#include "MilkGoods.h"

#include <format>


MilkGoods::MilkGoods()
            : Goods(),
              expirationDate("") {}

MilkGoods::MilkGoods(const char* name,
              std::string receiptDate,
              double price, 
              int quantity,
              std::string expirationDate)
             : Goods(name, receiptDate, price, quantity),
               expirationDate(expirationDate) {}

std::string MilkGoods::getExpirationDate() const {
    return expirationDate;
}

bool MilkGoods::recalculationPrice(std::string currentDate, int percentageReduction) {
    if (priceReduced) {
        return false;
    }
    
    if (percentageReduction <= 0 || percentageReduction > 100) {
        return false;
    }

    if (currentDate.empty() || getExpirationDate().empty()) {
        return false;
    }

    if (currentDate > getExpirationDate()) {
        discount(percentageReduction);
        priceReduced = true;
        return true;
    }

    return false;
}

std::string MilkGoods::toString() const {
    return std::format("{}\nМолочный товар\nСрок годности: {}", Goods::toString(), getExpirationDate());
}