#include "employeemanager.h"

EmployeeManager::EmployeeManager() {}

void EmployeeManager::showAllDatas(){

}

void EmployeeManager::run(){
    while(true)
    {
        cout << "=========employee manager=========" << endl;
        cout << "1. create employee." << endl;
        cout << "2. delete employee." << endl;
        cout << "3. search employee." << endl;
        cout << "input : " << endl;
        string str;
        cin >> str;

        if(str == "exit")
            return;
    }
}
