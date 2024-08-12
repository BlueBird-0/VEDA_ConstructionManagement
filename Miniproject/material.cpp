#include "material.h"  // Material 클래스 헤더 파일 포함
#include <iostream>  // 표준 I/O 라이브러리 포함

using namespace std;  // 표준 네임스페이스 사용

// Material 클래스의 생성자 정의
Material::Material(int id, string name, string supplier, double unitPrice, int stock, int orderQuantity)
    : m_id(id), m_name(name), m_supplier(supplier), m_unitPrice(unitPrice), m_stock(stock), m_orderQuantity(orderQuantity)
{
}

// 자재의 이름을 반환하는 getter 함수
string Material::getName() const
{
    return m_name;
}

// 자재의 이름을 설정하는 setter 함수
void Material::setName(string& name)
{
    m_name = name;
}

// 자재의 공급업체를 반환하는 getter 함수
string Material::getSupplier() const
{
    return m_supplier;
}

// 자재의 공급업체를 설정하는 setter 함수
void Material::setSupplier(string& supplier)
{
    m_supplier = supplier;
}

// 자재의 단가를 반환하는 getter 함수
double Material::getUnitPrice() const
{
    return m_unitPrice;
}

// 자재의 단가를 설정하는 setter 함수
void Material::setUnitPrice(double unitPrice)
{
    m_unitPrice = unitPrice;
}

// 자재의 재고량을 반환하는 getter 함수
int Material::getStock() const
{
    return m_stock;
}

// 자재의 재고량을 설정하는 setter 함수
void Material::setStock(int stock)
{
    m_stock = stock;
}

// 자재의 주문수량을 반환하는 getter 함수
int Material::getOrderQuantity() const
{
    return m_orderQuantity;
}

// 자재의 주문수량을 설정하는 setter 함수
void Material::setOrderQuantity(int orderQuantity)
{
    m_orderQuantity = orderQuantity;
}

// 자재의 ID를 반환하는 getter 함수
int Material::getId() const
{
    return m_id;
}

// Material 클래스의 동등 연산자 정의 (이름을 기준으로 비교)
bool Material::operator==(const Material &other) const {
    return (this->m_name == other.m_name);
}
