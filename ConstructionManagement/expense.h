#ifndef EXPENSE_H
#define EXPENSE_H

#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "Object.h"

using namespace std;

class Expense: public Object
{
public:
    Expense(int projectID = 0, int materialID = 0, int materialCosts = 0, int laborCosts = 0, int otherCosts = 0);

    // Getter and Setter functions
    int getProjectID() const;
    void setProjectID(int projectID);

    int getMaterialID() const;
    void setMaterialID(int materialID);

    int getMaterialCosts() const;
    void setMaterialCosts(int materialCosts);

    int getLaborCosts() const;
    void setLaborCosts(int laborCosts);

    int getOtherCosts() const;
    void setOtherCosts(int otherCosts);

    virtual void showInfo();

private:
    int m_projectID;
    int m_materialID;
    int m_materialCosts;
    int m_laborCosts;
    int m_otherCosts;
};

#endif // EXPENSE_H
