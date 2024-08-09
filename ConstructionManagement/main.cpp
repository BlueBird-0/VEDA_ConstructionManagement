#include <QCoreApplication>
#include <iostream>
#include "employeemanager.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Hello World" << endl;

    Manager* manager = new EmployeeManager();
    manager->run();

    return a.exec();
}
