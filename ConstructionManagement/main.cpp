#include <iostream>
#include "materialmanager.h"
#include "material.h"
#include "expensemanager.h"
#include <vector>

using namespace std;

int main()
{
    ExpenseManager manager;
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

    // 프로그램 메뉴 실행
    manager.displayMenu();

    return 0;
}
