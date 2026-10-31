#pragma once
#include <string>

class Goods {
private:
    char* name;                
    std::string receiptDate;  
    double price;           
    int quantity;         

public:
    Goods(); 
    Goods(const char* name,
          std::string receiptDate,
          double price,
          int quantity);
    Goods(const Goods& other);
    ~Goods(); 

    void setPrice(double price);     
    void setQuantity(int quantity);  

    const char* getName() const;
    double getPrice() const;
    int getQuantity() const;

    std::string toString() const; 
    void markup(double percent); 
    void discount(double percent);

    Goods& operator=(const Goods& other);
};
