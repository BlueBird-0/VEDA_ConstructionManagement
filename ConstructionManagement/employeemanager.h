#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "manager.h"

class EmployeeManager : public Manager
{
private:
    //vector<Employee> m_employees;     //Todo : 구현 예정
    //void create();    //Todo : 구현 예정
    //void remove();    //Todo : 구현 예정
    //void modify();    //Todo : 구현 예정
public:
    EmployeeManager();
    virtual void showAllDatas();
    virtual void run();
    //vector<Employee> search(string currentProject)    //Todo : 구현 예정

};

#endif // EMPLOYEEMANAGER_H
