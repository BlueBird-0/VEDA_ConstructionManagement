#ifndef EXPENSE_H
#define EXPENSE_H

#include <iostream>
using namespace std;

class Expense {
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

private:
    int m_projectID;
    int m_materialID;
    int m_materialCosts;
    int m_laborCosts;
    int m_otherCosts;
};

#endif // EXPENSE_H
