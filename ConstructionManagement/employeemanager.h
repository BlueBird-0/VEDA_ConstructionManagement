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
    void remove();
    //void modify();    //Todo : 구현 예정
public:
    EmployeeManager();
    virtual void showAllDatas();
    virtual void displayMenu();
    vector<Employee> search(int projectId);  //특정 projectId로 연관된 employee들을 반환합니다.
    vector<string> parseCSV(istream&, char);
    void saveCSV();
};

#endif // EMPLOYEEMANAGER_H
