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
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "       Project Management Program            " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. Project Manage                          " << endl;
        cout << "  2. Client Manage                           " << endl;
        cout << "  3. Material Manage                         " << endl;
        cout << "  4. EmployeeManage                          " << endl;
        cout << "  5. Expense Manage\                         " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Enter your choice: ";

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

    delete expenseManager;
    delete employeeManager;
    delete materialManager;
    delete projectManagerr;

    //MaterialManager manager;  // MaterialManager 객체 생성
    /*int projectID, materialID;

    cout << "Enter Project ID to search: ";
    cin >> projectID;

    cout << "Enter Material ID to search: ";
    cin >> materialID;

    // 프로젝트 ID로 검색
    vector<int> materialIDs = manager.searchByProjectID(projectID);
    if (!materialIDs.empty()) {
        cout << "Materials used in Project " << projectID << ": ";
        for (int id : materialIDs) {
            cout << id << " ";
        }
        cout << endl;
    } else {
        cout << "No materials found for Project ID " << projectID << endl;
    }

    // 자재 ID로 검색
    vector<int> projectIDs = manager.searchByMaterialID(materialID);
    if (!projectIDs.empty()) {
        cout << "Projects using Material " << materialID << ": ";
        for (int id : projectIDs) {
            cout << id << " ";
        }
        cout << endl;
    } else {
        cout << "No projects found for Material ID " << materialID << endl;
    }*/
    return 0;

}

