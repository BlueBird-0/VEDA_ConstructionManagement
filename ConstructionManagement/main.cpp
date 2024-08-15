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
        cout << "            건축 관리 프로그램               " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. 프로젝트 관리                           " << endl;
        cout << "  2. 고객 관리                               " << endl;
        cout << "  3. 자재 관리                               " << endl;
        cout << "  4. 인력 관리                               " << endl;
        cout << "  5. 비용 관리                               " << endl;
        cout << "  exit. 프로그램 종료                        " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "어떤 항목을 선택하시겠습니까? ";

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

