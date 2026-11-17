#pragma once

#include <iostream>
#include <fstream>
#include <string>


class Goods {
private:
    char* name;                
    std::string receiptDate;  
    double price;           
    int quantity;  
    
    inline static int aliveObjects = 0;

public:
    static constexpr int maxStringLength = 10000;

    Goods(); 
    Goods(const char* name,
          std::string receiptDate,
          double price, 
          int quantity);
    Goods(const Goods& other);
    virtual ~Goods(); 

    void setPrice(double price);     
    void setQuantity(int quantity);  

    const char* getName() const;
    std::string getReceiptDate() const;
    double getPrice() const;
    int getQuantity() const;

    virtual std::string toString() const; 
    void markup(double percent); 
    void discount(double percent);

    Goods& operator=(const Goods& other);
    Goods operator+(const Goods& other) const;
    friend Goods operator-(const Goods& left, const Goods& right);
    Goods& operator++();
    Goods operator++(int);

    friend std::ostream& operator<<(std::ostream& os, const Goods& item);
    friend std::istream& operator>>(std::istream& is, Goods& item);
    friend std::ofstream& operator<<(std::ofstream& os, const Goods& item);
    friend std::ifstream& operator>>(std::ifstream& is, Goods& item);

    explicit operator double() const;

    static int alive();
};
