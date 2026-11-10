#pragma once

#include <iostream>
#include <string>


class Goods {
private:
    char* name;                
    std::string receiptDate;  
    double price;           
    int quantity;  
    
    inline static int aliveObjects = 0;

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
    std::string getReceiptDate() const;
    double getPrice() const;
    int getQuantity() const;

    std::string toString() const; 
    void markup(double percent); 
    void discount(double percent);

    Goods& operator=(const Goods& other);
    Goods operator+(const Goods& other) const;
    friend Goods operator-(const Goods& left, const Goods& right);
    Goods& operator++();
    Goods operator++(int);

    friend std::ostream& operator<<(std::ostream& os, const Goods& item);
    friend std::istream& operator>>(std::istream& is, Goods& item);

    explicit operator double() const;

    static int alive();
};
