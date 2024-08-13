#include "material.h"

Material::Material(int id, string name, string supplier, double unitPrice, int stock, int orderQuantity)
    : m_id(id), m_name(name), m_supplier(supplier), m_unitPrice(unitPrice), m_stock(stock), m_orderQuantity(orderQuantity) {}

string Material::getName() const {
    return m_name;
}

void Material::setName(const string& name) {
    m_name = name;
}

string Material::getSupplier() const {
    return m_supplier;
}

void Material::setSupplier(const string& supplier) {
    m_supplier = supplier;
}

double Material::getUnitPrice() const {
    return m_unitPrice;
}

void Material::setUnitPrice(double unitPrice) {
    m_unitPrice = unitPrice;
}

int Material::getStock() const {
    return m_stock;
}

void Material::setStock(int stock) {
    m_stock = stock;
}

int Material::getOrderQuantity() const {
    return m_orderQuantity;
}

void Material::setOrderQuantity(int orderQuantity) {
    m_orderQuantity = orderQuantity;
}

int Material::getId() const {
    return m_id;
}

bool Material::operator==(const Material& other) const {
    return (this->m_name == other.m_name);
}
