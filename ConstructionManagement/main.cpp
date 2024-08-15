#include <iostream>
#include "materialmanager.h"
#include "material.h"
#include "expensemanager.h"
#include "manager.h"
#include "employeemanager.h"
#include "projectmanager.h"
#include "clientmanager.h"
#include <vector>

using namespace std;

int main()
{
    Manager* manager;
    ClientManager* clientManager = new ClientManager();
    ExpenseManager* expenseManager = new ExpenseManager();
    EmployeeManager* employeeManager = new EmployeeManager();
    MaterialManager* materialManager = new MaterialManager();
    ProjectManager* projectManagerr = new ProjectManager();

    string  input;
    while(true){
        cleanCMD();
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "            ���� ���� ���α׷�               " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. ������Ʈ ����                           " << endl;
        cout << "  2. �� ����                               " << endl;
        cout << "  3. ���� ����                               " << endl;
        cout << "  4. �η� ����                               " << endl;
        cout << "  5. ��� ����                               " << endl;
        cout << "  exit. ���α׷� ����                        " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "� �׸��� �����Ͻðڽ��ϱ�? ";

		cin >> input;
        if (input == "1") {
            projectManagerr->displayMenu();
        }
        else if (input == "2") {
            clientManager->displayMenu();
        }
        else if (input == "3") {
            materialManager->displayMenu();
        }
        else if (input == "4") {
            manager = employeeManager;
            manager->displayMenu();
        }
        else if (input == "5") {
            expenseManager->displayMenu();
        }
        else if (input =="exit")
            break;

    }

    delete clientManager;
    delete expenseManager;
    delete employeeManager;
    delete materialManager;
    delete projectManagerr;
    return 0;

}

