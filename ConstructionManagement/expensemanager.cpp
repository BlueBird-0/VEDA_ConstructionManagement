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
	cout << "������ƮID: ";
	cin >> projectID;
	cout << "����ID: ";
	cin >> materialID;
	cout << "������: ";
	cin >> materialCosts;
	cout << "�ΰǺ�: ";
	cin >> laborCosts;
	cout << "��Ÿ���: ";
	cin >> otherCosts;
	setCmdColor();

    Expense expense(projectID, materialID, materialCosts, laborCosts, otherCosts);
    m_expenses.push_back(expense);

    cout << "����� ���������� �߰��Ǿ����ϴ�!" << endl;
}

void ExpenseManager::modify(int projectID, int materialID) {
    for (auto& expense : m_expenses) {
        if (expense.getProjectID() == projectID && expense.getMaterialID() == materialID) {
            int materialCosts, laborCosts, otherCosts;

            cout << "���� ������: " << expense.getMaterialCosts() << endl;
            cout << "���� �ΰǺ�: " << expense.getLaborCosts() << endl;
            cout << "���� ��Ÿ���: " << expense.getOtherCosts() << endl;

            cout << "���ο� �������� �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
            cin >> materialCosts;
            if (materialCosts >= 0) expense.setMaterialCosts(materialCosts);

            cout << "���ο� �ΰǺ� �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
            cin >> laborCosts;
            if (laborCosts >= 0) expense.setLaborCosts(laborCosts);

            cout << "���ο� ��Ÿ����� �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
            cin >> otherCosts;
            if (otherCosts >= 0) expense.setOtherCosts(otherCosts);

            cout << "���������� �����Ǿ����ϴ�!" << endl;
            return;
        }
    }
    cout << "��뿡 ���� ������ƮID " << projectID << " �� ����ID " << materialID << " ��(��) ã�� �� �����ϴ�..." << endl;
}

void ExpenseManager::remove(int projectID, int materialID) {
    for (auto it = m_expenses.begin(); it != m_expenses.end(); ++it) {
        if (it->getProjectID() == projectID && it->getMaterialID() == materialID) {
            m_expenses.erase(it);
            cout << "����� ���������� �����Ǿ����ϴ�!" << endl;
            return;
        }
    }
    cout << "��뿡 ���� ������ƮID " << projectID << " �� ����ID " << materialID << " ��(��) ã�� �� �����ϴ�..." << endl;
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
    printf("%10s | %6s | %8s | %8s | %8s\n", "������ƮID", "����ID", "������", "�ΰǺ�", "��Ÿ���");
    for (const auto& expense : m_expenses) {
        cout << setw(10) << expense.getProjectID() << " | ";
        cout << setw(6) << expense.getMaterialID() << " | ";
        cout << setw(8) << expense.getMaterialCosts() << " | ";
        cout << setw(8) << expense.getLaborCosts() << " | ";
        cout << setw(8) << expense.getOtherCosts() << endl;
    }
    setCmdColor();
}

void ExpenseManager::displayMenu() {
    int choice, projectID, materialID;
    bool running = true;

    while (running) {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��                 \033[30;93m������\033[0m                  \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m1. ��� ��ȸ\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m2. ��� ���\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m3. ��� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m4. ��� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m5. ������ƮID �˻�\033[0m                       \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m6. ����ID �˻�\033[0m                           \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;91m7. ������ ������\033[0m                       \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "� �׸��� �����Ͻðڽ��ϱ�? ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayInfo();
            break;
        case 2:
            create();
            break;
        case 3:
            cout << "������ ������ƮID�� �Է����ּ���: ";
            cin >> projectID;
            cout << "������ ����ID�� �Է����ּ���: ";
            cin >> materialID;
            modify(projectID, materialID);
            break;
        case 4:
            cout << "������ ������ƮID�� �Է����ּ���: ";
            cin >> projectID;
            cout << "������ ����ID�� �Է����ּ���: ";
            cin >> materialID;
            remove(projectID, materialID);
            break;
        case 5:
            cout << "ã����� ������ƮID�� �Է����ּ���: ";
            cin >> projectID;
            {
                vector<int> materialIDs = searchByProjectID(projectID);
                cout << "������Ʈ���� ���Ǵ� ���� " << projectID << ": ";
                for (int id : materialIDs) {
                    cout << id << " ";
                }
                cout << endl;
            }
            break;
        case 6:
            cout << "ã����� ����ID�� �Է����ּ���: ";
            cin >> materialID;
            {
                vector<int> projectIDs = searchByMaterialID(materialID);
                cout << "���縦 ����� ������Ʈ " << materialID << ": ";
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
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
            break;
        }
        if (running) {
            cout << "\n����Ϸ��� Enter Ű�� �����ּ���...";
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
