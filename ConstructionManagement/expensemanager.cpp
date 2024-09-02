#include "expensemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

ExpenseManager::ExpenseManager() {
    ifstream file("expenses.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size() > 0) {
                int projectID = stoi(row[0]);
                int materialID = stoi(row[1]);
                int materialCosts = stoi(row[2]);
                int laborCosts = stoi(row[3]);
                int otherCosts = stoi(row[4]);
                Expense e(projectID, materialID, materialCosts, laborCosts, otherCosts);
                m_expenses.push_back(e);
            }
        }
    }
    file.close();
}

ExpenseManager::~ExpenseManager() {
    ofstream file("expenses.txt");
    if (!file.fail()) {
        for (const auto& expense : m_expenses) {
            file << expense.getProjectID() << "," << expense.getMaterialID() << ","
                 << expense.getMaterialCosts() << "," << expense.getLaborCosts() << ","
                 << expense.getOtherCosts() << endl;
        }
    }
    file.close();
}

void ExpenseManager::create() {
	int projectID, materialID, materialCosts, laborCosts, otherCosts;
	setCmdColor(1);
	cout << "프로젝트ID: ";
	cin >> projectID;
	cout << "자재ID: ";
	cin >> materialID;
	cout << "자재비용: ";
	cin >> materialCosts;
	cout << "인건비: ";
	cin >> laborCosts;
	cout << "기타비용: ";
	cin >> otherCosts;
	setCmdColor();

    Expense expense(projectID, materialID, materialCosts, laborCosts, otherCosts);
    m_expenses.push_back(expense);

    cout << "비용이 성공적으로 추가되었습니다!" << endl;
}

void ExpenseManager::modify(int projectID, int materialID) {
    for (auto& expense : m_expenses) {
        if (expense.getProjectID() == projectID && expense.getMaterialID() == materialID) {
            int materialCosts, laborCosts, otherCosts;

            cout << "현재 자재비용: " << expense.getMaterialCosts() << endl;
            cout << "현재 인건비: " << expense.getLaborCosts() << endl;
            cout << "현재 기타비용: " << expense.getOtherCosts() << endl;

            cout << "새로운 자재비용을 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
            cin >> materialCosts;
            if (materialCosts >= 0) expense.setMaterialCosts(materialCosts);

            cout << "새로운 인건비를 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
            cin >> laborCosts;
            if (laborCosts >= 0) expense.setLaborCosts(laborCosts);

            cout << "새로운 기타비용을 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
            cin >> otherCosts;
            if (otherCosts >= 0) expense.setOtherCosts(otherCosts);

            cout << "성공적으로 수정되었습니다!" << endl;
            return;
        }
    }
    cout << "비용에 대한 프로젝트ID " << projectID << " 와 자재ID " << materialID << " 을(를) 찾을 수 없습니다..." << endl;
}

void ExpenseManager::remove(int projectID, int materialID) {
    for (auto it = m_expenses.begin(); it != m_expenses.end(); ++it) {
        if (it->getProjectID() == projectID && it->getMaterialID() == materialID) {
            m_expenses.erase(it);
            cout << "비용이 성공적으로 삭제되었습니다!" << endl;
            return;
        }
    }
    cout << "비용에 대한 프로젝트ID " << projectID << " 와 자재ID " << materialID << " 을(를) 찾을 수 없습니다..." << endl;
}

vector<int> ExpenseManager::searchByProjectID(int projectID) {
    vector<int> foundExpenses;
    for (const auto& expense : m_expenses) {
        if (expense.getProjectID() == projectID) {
            foundExpenses.push_back(expense.getMaterialID());
        }
    }
    return foundExpenses;
}

vector<int> ExpenseManager::searchByMaterialID(int materialID) {
    vector<int> foundExpenses;
    for (const auto& expense : m_expenses) {
        if (expense.getMaterialID() == materialID) {
            foundExpenses.push_back(expense.getProjectID());
        }
    }
    return foundExpenses;
}

void ExpenseManager::displayInfo() {
    setCmdColor(1);
    if (!m_expenses.empty()) {
        printf("%10s | %6s | %12s | %12s | %12s\n", "프로젝트ID", "자재ID", "자재비용(₩)", "인건비(₩)", "기타비용(₩)");
        for (const auto& expense : m_expenses) {
            cout << setw(10) << expense.getProjectID() << " | ";
            cout << setw(6) << expense.getMaterialID() << " | ";
            cout << setw(8) << expense.getMaterialCosts() << " | ";
            cout << setw(8) << expense.getLaborCosts() << " | ";
            cout << setw(8) << expense.getOtherCosts() << endl;
        }
    }
    else {
        setCmdColor(2);
        cout << "등록된 비용이 없습니다." << endl;
    }
    setCmdColor();
}

void ExpenseManager::displayMenu() {
    int projectID, materialID;
    string choice;
    bool running = true;

    while (running) {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "\033[30;94m┌───────────────────────────────────────────┐ \033[0m" << endl;
        cout << "\033[30;94m│                 \033[30;93m비용관리\033[0m                  \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│───────────────────────────────────────────│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m1. 비용 전체조회\033[0m                         \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m2. 비용 등록\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m3. 비용 수정\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m4. 비용 삭제\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m5. 프로젝트ID 검색\033[0m                       \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m6. 자재ID 검색\033[0m                           \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;91mexit. 나가기\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m└───────────────────────────────────────────┘ \033[0m" << endl;
        cout << "어떤 항목을 선택하시겠습니까? ";
        cin >> choice;

        if (choice == "1") {
            displayInfo();
        }
        else if (choice == "2") {
            create();
        }
		else if (choice == "3") {
            cout << "수정할 프로젝트ID를 입력해주세요: ";
            cin >> projectID;
            cout << "수정할 자재ID를 입력해주세요: ";
            cin >> materialID;
            modify(projectID, materialID);
        }
        else if (choice == "4") {
            cout << "삭제할 프로젝트ID를 입력해주세요: ";
            cin >> projectID;
            cout << "삭제할 자재ID를 입력해주세요: ";
            cin >> materialID;
            remove(projectID, materialID);
        }
        else if (choice == "5") {
            cout << "찾고싶은 프로젝트ID를 입력해주세요: ";
            cin >> projectID;
            {
                vector<int> materialIDs = searchByProjectID(projectID);
                cout << "프로젝트에서 사용되는 자재 " << projectID << ": ";
                for (int id : materialIDs) {
                    cout << id << " ";
                }
                cout << endl;
            }
        }
        else if (choice == "6") {
            cout << "찾고싶은 자재ID를 입력해주세요: ";
            cin >> materialID;
            {
                vector<int> projectIDs = searchByMaterialID(materialID);
                cout << "자재를 사용한 프로젝트 " << materialID << ": ";
                for (int id : projectIDs) {
                    cout << id << " ";
                }
                cout << endl;
            }
        }
		else if (choice == "7" || choice == "exit") {
            running = false;
        }
        else {
            setCmdColor(2);
            cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
            setCmdColor();
        }


        if (running) {
            cout << "\n계속하려면 Enter 키를 눌러주세요...";
            cin.ignore();
            cin.get();
        }
    }
}

vector<string> ExpenseManager::parseCSV(istream& str, char delimiter) {
    vector<string> result;
    string line;
    if (getline(str, line)) {
        stringstream ss(line);
        string item;
        while (getline(ss, item, delimiter)) {
            result.push_back(item);
        }
    }
    return result;
}

void ExpenseManager::showAllDatas()
{

}
