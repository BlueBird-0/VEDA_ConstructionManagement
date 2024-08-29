#include "employee.h"
#include <iostream>

void Employee::showInfo()
{
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "ID: " << getId() << endl;
    cout << "이름: " << getName() << endl;
    cout << "직책: " << getJobTitle() << endl;
    cout << "연락처: " << getPhoneNum() << endl;
    cout << "관련 프로젝트ID: ";
    for (auto projectID : getProjectIdList())
    {
        cout << projectID << ", ";
    }

    cout << endl << endl;
}
