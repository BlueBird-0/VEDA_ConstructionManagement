#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "object.h"

using namespace std;

class Material : public Object 
{
public:
    Material(int id = 0, string name = "", string supplier = "", double unitPrice = 0.0, int stock = 0, int orderQuantity = 0);

    // Getter and Setter functions
    string getName() const;
    void setName(const string& name);

    string getSupplier() const;
    void setSupplier(const string& supplier);

    int getUnitPrice() const;
    void setUnitPrice(double unitPrice);

    int getStock() const;
    void setStock(int stock);

    int getOrderQuantity() const;
    void setOrderQuantity(int orderQuantity);

    int getId() const;

    // Overloaded equality operator
    bool operator==(const Material& other) const;

private:
    int m_id;
    string m_name;
    string m_supplier;
    int m_unitPrice;      // 단가
    int m_stockQuantity;     // 재고량
    int m_orderQuantity;     // 주문수량
};

#endif // __MATERIAL_H__
