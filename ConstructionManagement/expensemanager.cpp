#include "expensemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <locale>
#include <iomanip>
#include <algorithm>

// 숫자를 쉼표가 포함된 문자열로 포맷하는 함수
string formatNumberWithCommas(int number) {
    stringstream ss;
    ss.imbue(locale(""));  // 현재 시스템의 로케일 설정
    ss << fixed << setprecision(0) << number;

    string str = ss.str();
    string result;
    int count = 0;

    // 문자열을 끝에서부터 탐색하여 3자리마다 쉼표 추가
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        result += *it;
        count++;
        if (count % 3 == 0 && it + 1 != str.rend()) {
            result += ','; // 쉼표 추가
        }
    }
    reverse(result.begin(), result.end()); // 문자열을 원래 순서로 복원
    return result;
}

int parseCost(const string& costStr) {
    string cleanStr;
    for (char c : costStr) {
        // 숫자와 쉼표만 허용
        if (isdigit(c) || c == ',') {
            cleanStr += c;
        }
    }

    // 쉼표를 제거한 후 숫자로 변환
    cleanStr.erase(remove(cleanStr.begin(), cleanStr.end(), ','), cleanStr.end());

    try {
        return stoi(cleanStr);
    } catch (const invalid_argument& e) {
        throw invalid_argument("잘못된 숫자 형식입니다: " + costStr);
    } catch (const out_of_range& e) {
        throw out_of_range("숫자 범위를 초과했습니다: " + costStr);
    }
}

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
    int projectID, materialID;
    string materialCostsStr, laborCostsStr, otherCostsStr;
    setCmdColor(0);
    printf("%2s)  %10s | %10s | %20s | %18s | %20s\n", "예", "프로젝트ID", "자재ID", "자재비용(₩)", "인건비(₩)", "기타비용(₩)");
    printf("%2s | %10s | %8s | %14s | %13s | %14s\n", "","1", "1", "300,000,000", "150,000,000", "50,000,000");
    setCmdColor();
    cout << "프로젝트ID: ";
    cin >> projectID;
    cout << "자재ID: ";
    cin >> materialID;

    cout << "자재비용: ";
    cin.ignore();  // 입력 버퍼를 비웁니다.
    getline(cin, materialCostsStr);

    cout << "인건비: ";
    getline(cin, laborCostsStr);

    cout << "기타비용: ";
    getline(cin, otherCostsStr);

    setCmdColor();

    try {
        int materialCosts = parseCost(materialCostsStr);
        int laborCosts = parseCost(laborCostsStr);
        int otherCosts = parseCost(otherCostsStr);

        Expense expense(projectID, materialID, materialCosts, laborCosts, otherCosts);
        m_expenses.push_back(expense);

        cout << "비용이 성공적으로 추가되었습니다!" << endl;
    } catch (const exception& e) {
        cout << "입력 오류: " << e.what() << endl;
    }
}

void ExpenseManager::modify(int projectID, int materialID) {
    for (auto& expense : m_expenses) {
        if (expense.getProjectID() == projectID && expense.getMaterialID() == materialID) {
            string materialCostsStr, laborCostsStr, otherCostsStr;

            cout << "현재 자재비용: " << formatNumberWithCommas(expense.getMaterialCosts()) << endl;
            cout << "현재 인건비: " << formatNumberWithCommas(expense.getLaborCosts()) << endl;
            cout << "현재 기타비용: " << formatNumberWithCommas(expense.getOtherCosts()) << endl;

            cout << "새로운 자재비용 (쉼표 포함 가능, 아니면 -1로 유지): ";
            cin.ignore();
            std::getline(cin, materialCostsStr);

            cout << "새로운 인건비 (쉼표 포함 가능, 아니면 -1로 유지): ";
            std::getline(cin, laborCostsStr);

            cout << "새로운 기타비용 (쉼표 포함 가능, 아니면 -1로 유지): ";
            std::getline(cin, otherCostsStr);

            try {
                int materialCosts = (materialCostsStr == "-1") ? expense.getMaterialCosts() : parseCost(materialCostsStr);
                int laborCosts = (laborCostsStr == "-1") ? expense.getLaborCosts() : parseCost(laborCostsStr);
                int otherCosts = (otherCostsStr == "-1") ? expense.getOtherCosts() : parseCost(otherCostsStr);

                expense.setMaterialCosts(materialCosts);
                expense.setLaborCosts(laborCosts);
                expense.setOtherCosts(otherCosts);

                cout << "성공적으로 수정되었습니다!" << endl;
            } catch (const exception& e) {
                cout << "입력 오류: " << e.what() << endl;
            }
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
    printf("%10s | %10s | %18s | %16s | %18s\n", "프로젝트ID", "자재ID", "자재비용", "인건비", "기타비용");
    for (const auto& expense : m_expenses) {
        cout << setw(10) << expense.getProjectID() << " | ";
        cout << setw(8) << expense.getMaterialID() << " | ";
        cout << setw(14) << formatNumberWithCommas(expense.getMaterialCosts()) << " | ";
        cout << setw(13) << formatNumberWithCommas(expense.getLaborCosts()) << " | ";
        cout << setw(14) << formatNumberWithCommas(expense.getOtherCosts()) << endl;
    }
    setCmdColor();
}

void ExpenseManager::displayMenu() {
    int choice, projectID, materialID;
    bool running = true;

    while (running) {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "\033[30;94m┌───────────────────────────────────────────┐ \033[0m" << endl;
        cout << "\033[30;94m│                 \033[30;93m비용관리\033[0m                  \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│───────────────────────────────────────────│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m1. 비용 조회\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m2. 비용 등록\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m3. 비용 수정\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m4. 비용 삭제\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m5. 프로젝트ID 검색\033[0m                       \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m6. 자재ID 검색\033[0m                           \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;91m7. 비용관리 나가기\033[0m                       \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m└───────────────────────────────────────────┘ \033[0m" << endl;
        cout << "어떤 항목을 선택하시겠습니까? ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayInfo();
            break;
        case 2:
            create();
            break;
        case 3:
            cout << "수정할 프로젝트ID를 입력해주세요: ";
            cin >> projectID;
            cout << "수정할 자재ID를 입력해주세요: ";
            cin >> materialID;
            modify(projectID, materialID);
            break;
        case 4:
            cout << "삭제할 프로젝트ID를 입력해주세요: ";
            cin >> projectID;
            cout << "삭제할 자재ID를 입력해주세요: ";
            cin >> materialID;
            remove(projectID, materialID);
            break;
        case 5:
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
            break;
        case 6:
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
            break;
        case 7:
            running = false;
            break;
        default:
            cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
            break;
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
