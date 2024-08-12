
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <iostream>  // 표준 I/O 라이브러리 포함

using namespace std;  // 표준 네임스페이스 사용

// Material 클래스 선언
class Material {
public:
    // 기본 값을 가진 생성자
    Material(int id = 0, string = "", string = "", double = 0.0, int = 0, int = 0);

    // 멤버 함수 선언
    string getName() const;
    void setName(string&);

    string getSupplier() const;
    void setSupplier(string&);

    double getUnitPrice() const;
    void setUnitPrice(double);

    int getStock() const;
    void setStock(int);

    int getOrderQuantity() const;
    void setOrderQuantity(int);

    int getId() const;
    bool operator==(const Material &other) const;

private:
    // 멤버 변수
    int m_id;
    string m_name;
    string m_supplier;
    double m_unitPrice;
    int m_stock;
    int m_orderQuantity;
};

#endif          // __MATERIAL_H__
