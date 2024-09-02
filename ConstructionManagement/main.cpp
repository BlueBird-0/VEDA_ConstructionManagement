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

    Manager* manager = nullptr;
    ClientManager* clientManager = new ClientManager();
    ExpenseManager* expenseManager = new ExpenseManager();
    EmployeeManager* employeeManager = new EmployeeManager();
    MaterialManager* materialManager = new MaterialManager();
    ProjectManager* projectManagerr = new ProjectManager();

    string  input;
    while (true) {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��            \033[30;93m���� ���� ���α׷�\033[0m             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m1. ������Ʈ ����\033[0m                         \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m2. �� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m3. ���� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m4. �η� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m5. ��� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;91mexit. ���α׷� ����\033[0m                      \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << " � �׸��� �����Ͻðڽ��ϱ�? ";

        cin >> input;
        if (input == "1") {
            manager = projectManagerr;
        }
        else if (input == "2") {
            manager = clientManager;
        }
        else if (input == "3") {
            manager = materialManager;
        }
        else if (input == "4") {
            manager = employeeManager;
        }
        else if (input == "5") {
            manager = expenseManager;
        }
        else if (input == "exit")
            break;
        else {
            cout << "\n����Ϸ��� Enter Ű�� �����ּ���...";
            cin.ignore();
            cin.get();  // Enter �Է��� ��ٸ�
            continue;
        }
        manager->displayMenu();

    }

    delete clientManager;
    delete expenseManager;
    delete employeeManager;
    delete materialManager;
    delete projectManagerr;
    return 0;
}
