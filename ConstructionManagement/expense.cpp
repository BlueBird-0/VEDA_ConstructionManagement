#include "expense.h"

Expense::Expense(int projectID, int materialID, int materialCosts, int laborCosts, int otherCosts)
    : m_projectID(projectID), m_materialID(materialID), m_materialCosts(materialCosts),
    m_laborCosts(laborCosts), m_otherCosts(otherCosts) {}

int Expense::getProjectID() const {
    return m_projectID;
}

void Expense::setProjectID(int projectID) {
    m_projectID = projectID;
}

int Expense::getMaterialID() const {
    return m_materialID;
}

void Expense::setMaterialID(int materialID) {
    m_materialID = materialID;
}

int Expense::getMaterialCosts() const {
    return m_materialCosts;
}

void Expense::setMaterialCosts(int materialCosts) {
    m_materialCosts = materialCosts;
}

int Expense::getLaborCosts() const {
    return m_laborCosts;
}

void Expense::setLaborCosts(int laborCosts) {
    m_laborCosts = laborCosts;
}

int Expense::getOtherCosts() const {
    return m_otherCosts;
}

void Expense::setOtherCosts(int otherCosts) {
    m_otherCosts = otherCosts;
}
