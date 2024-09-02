#include "employee.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

void Employee::showInfo()
{
    cout << setw(6) << right << getId() << " | ";
    cout << setw(10) << right << getName() << " | ";
    cout << setw(8) << right << getJobTitle() << " | ";
    cout << setw(14) << right << getPhoneNum() << " | ";

    string str = "";
    auto projectList = getProjectIdList();
    if (projectList.empty())
        str = "empty";
    else {
		for (auto it = projectList.begin(); it != projectList.end(); it++) {
            str += to_string(*it);
            if (it != projectList.end() - 1)
                str += ", ";
        }
    }
    cout << setw(10) << right << str <<endl;
}
