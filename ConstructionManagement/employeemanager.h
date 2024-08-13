#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "manager.h"
#include "employee.h"
#include <map>

class EmployeeManager : public Manager
{
private:
    map<int, Employee*> m_employeeList;
    void create();  //Employee를 생성합니다.
    //void remove();    //Todo : 구현 예정
    //void modify();    //Todo : 구현 예정
public:
    EmployeeManager();
    virtual void showAllDatas();
    virtual void run();
    //vector<Employee> search(string currentProject)    //Todo : 구현 예정
    vector<string> parseCSV(istream&, char);
    void saveCSV();
};

#endif // EMPLOYEEMANAGER_H
