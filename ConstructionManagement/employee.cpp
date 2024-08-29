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

    string list = "";
    for (auto projectID : getProjectIdList())
    {
        list += to_string(projectID);
        list += ", ";
    }
    cout << setw(10) << right << list <<endl;

    cout << endl << endl;
}
