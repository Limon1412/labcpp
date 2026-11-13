#pragma once

#include "Goods.h"

class MilkGoods : public Goods {
private:
    std::string expirationDate;
    bool priceReduced = false;

public:
    MilkGoods();
    MilkGoods(const char* name,
              std::string receiptDate,
              double price, 
              int quantity,
              std::string expirationDate);

    std::string getExpirationDate() const;
    bool recalculationPrice(std::string currentDate, int percentageReduction);

    std::string toString() const override;
};