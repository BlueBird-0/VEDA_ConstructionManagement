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

    cout << "Enter project ID: ";
    cin >> projectID;
    cout << "Enter material ID: ";
    cin >> materialID;
    cout << "Enter material costs: ";
    cin >> materialCosts;
    cout << "Enter labor costs: ";
    cin >> laborCosts;
    cout << "Enter other costs: ";
    cin >> otherCosts;

    Expense expense(projectID, materialID, materialCosts, laborCosts, otherCosts);
    m_expenses.push_back(expense);

    cout << "Expense added successfully!" << endl;
}

void ExpenseManager::modify(int projectID, int materialID) {
    for (auto& expense : m_expenses) {
        if (expense.getProjectID() == projectID && expense.getMaterialID() == materialID) {
            int materialCosts, laborCosts, otherCosts;

            cout << "Current Material Costs: " << expense.getMaterialCosts() << endl;
            cout << "Current Labor Costs: " << expense.getLaborCosts() << endl;
            cout << "Current Other Costs: " << expense.getOtherCosts() << endl;

            cout << "Enter new material costs (or enter -1 to keep current): ";
            cin >> materialCosts;
            if (materialCosts >= 0) expense.setMaterialCosts(materialCosts);

            cout << "Enter new labor costs (or enter -1 to keep current): ";
            cin >> laborCosts;
            if (laborCosts >= 0) expense.setLaborCosts(laborCosts);

            cout << "Enter new other costs (or enter -1 to keep current): ";
            cin >> otherCosts;
            if (otherCosts >= 0) expense.setOtherCosts(otherCosts);

            cout << "Expense updated successfully!" << endl;
            return;
        }
    }
    cout << "Expense with Project ID " << projectID << " and Material ID " << materialID << " not found." << endl;
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
    cout << endl << "Project ID | Material ID | Material Costs | Labor Costs | Other Costs" << endl;
    for (const auto& expense : m_expenses) {
        cout << setw(10) << expense.getProjectID() << " | ";
        cout << setw(10) << expense.getMaterialID() << " | ";
        cout << setw(15) << expense.getMaterialCosts() << " | ";
        cout << setw(12) << expense.getLaborCosts() << " | ";
        cout << setw(11) << expense.getOtherCosts() << endl;
    }
}

void ExpenseManager::displayMenu() {
    int choice, projectID, materialID;
    bool running = true;

    while (running) {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "              Expense Manager                " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. Display Expense List                    " << endl;
        cout << "  2. Add Expense                             " << endl;
        cout << "  3. Modify Expense                          " << endl;
        cout << "  4. Search by Project ID                    " << endl;
        cout << "  5. Search by Material ID                   " << endl;
        cout << "  6. Quit this Program                       " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayInfo();
            break;
        case 2:
            create();
            break;
        case 3:
            cout << "Enter Project ID: ";
            cin >> projectID;
            cout << "Enter Material ID: ";
            cin >> materialID;
            modify(projectID, materialID);
            break;
        case 4:
            cout << "Enter Project ID: ";
            cin >> projectID;
            {
                vector<int> materialIDs = searchByProjectID(projectID);
                cout << "Materials used in Project " << projectID << ": ";
                for (int id : materialIDs) {
                    cout << id << " ";
                }
                cout << endl;
            }
            break;
        case 5:
            cout << "Enter Material ID: ";
            cin >> materialID;
            {
                vector<int> projectIDs = searchByMaterialID(materialID);
                cout << "Projects using Material " << materialID << ": ";
                for (int id : projectIDs) {
                    cout << id << " ";
                }
                cout << endl;
            }
            break;
        case 6:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        if (running) {
            cout << "\nPress Enter to continue...";
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
