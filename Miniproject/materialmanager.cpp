#include <vector>  // 벡터 라이브러리 포함
#include <algorithm>  // 알고리즘 라이브러리 포함
#include <fstream>  // 파일 스트림 라이브러리 포함
#include <sstream>  // 문자열 스트림 라이브러리 포함
#include <iomanip>  // IO 조정 라이브러리 포함

#include "material.h"  // Material 클래스 헤더 파일 포함
#include "materialmanager.h"  // MaterialManager 클래스 헤더 파일 포함


MaterialManager::MaterialManager() {
    ifstream file("materiallist.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size() > 0) {
                int id = stoi(row[0]);
                double unitPrice = stod(row[3]);
                int stock = stoi(row[4]);
                int orderQuantity = stoi(row[5]);
                Material* m = new Material(id, row[1], row[2], unitPrice, stock, orderQuantity);
                materialList[id] = m;
            }
        }
    }
    file.close();
}

MaterialManager::~MaterialManager() {
    ofstream file("materiallist.txt");
    if (!file.fail()) {
        for (const auto& pair : materialList) {
            Material* m = pair.second;
            file << m->getId() << "," << m->getName() << "," << m->getSupplier() << ","
                 << m->getUnitPrice() << "," << m->getStock() << "," << m->getOrderQuantity() << endl;
        }
    }
    file.close();

    // 메모리 누수를 방지하기 위해 모든 자재 객체 삭제
    for (auto& pair : materialList) {
        delete pair.second;
    }
}

void MaterialManager::create() {
    string name, supplier;
    double unitPrice;
    int stock, orderQuantity;

    cout << "Enter material name: ";
    cin >> name;
    cout << "Enter supplier name: ";
    cin >> supplier;
    cout << "Enter unit price: ";
    cin >> unitPrice;
    cout << "Enter stock quantity: ";
    cin >> stock;
    cout << "Enter order quantity: ";
    cin >> orderQuantity;

    int id = makeId();
    Material* material = new Material(id, name, supplier, unitPrice, stock, orderQuantity);
    materialList[id] = material;

    cout << "Material added successfully!" << endl;
}

void MaterialManager::remove(int id) {
    auto it = materialList.find(id);
    if (it != materialList.end()) {
        delete it->second;
        materialList.erase(it);
        cout << "Material removed successfully!" << endl;
    } else {
        cout << "Material with ID " << id << " not found." << endl;
    }
}

Material* MaterialManager::search(int id) {
    auto it = materialList.find(id);
    if (it != materialList.end()) {
        return it->second;
    } else {
        cout << "Material with ID " << id << " not found." << endl;
        return nullptr;
    }
}

void MaterialManager::modify(int id) {
    Material* material = search(id);
    if (material) {
        string name, supplier;
        double unitPrice;
        int stock, orderQuantity;

        cout << "Current Name: " << material->getName() << endl;
        cout << "Current Supplier: " << material->getSupplier() << endl;
        cout << "Current Unit Price: " << material->getUnitPrice() << endl;
        cout << "Current Stock: " << material->getStock() << endl;
        cout << "Current Order Quantity: " << material->getOrderQuantity() << endl;

        cout << "Enter new material name (or press enter to keep current): ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) material->setName(name);

        cout << "Enter new supplier name (or press enter to keep current): ";
        getline(cin, supplier);
        if (!supplier.empty()) material->setSupplier(supplier);

        cout << "Enter new unit price (or enter -1 to keep current): ";
        cin >> unitPrice;
        if (unitPrice >= 0) material->setUnitPrice(unitPrice);

        cout << "Enter new stock quantity (or enter -1 to keep current): ";
        cin >> stock;
        if (stock >= 0) material->setStock(stock);

        cout << "Enter new order quantity (or enter -1 to keep current): ";
        cin >> orderQuantity;
        if (orderQuantity >= 0) material->setOrderQuantity(orderQuantity);

        cout << "Material updated successfully!" << endl;
    }
}

void MaterialManager::displayInfo() {
    cout << endl << "  ID  |     Name     |   Supplier   |  Unit Price  |  Stock  |  Order Qty" << endl;
    for (const auto& pair : materialList) {
        Material* m = pair.second;
        cout << setw(5) << setfill('0') << right << m->getId() << " | " << left;
        cout << setw(12) << m->getName() << " | ";
        cout << setw(12) << m->getSupplier() << " | ";
        cout << setw(12) << m->getUnitPrice() << " | ";
        cout << setw(7) << m->getStock() << " | ";
        cout << setw(10) << m->getOrderQuantity() << endl;
    }
}

bool MaterialManager::displayMenu() {
    int choice, id;
    bool running = true;

    while (running) {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "              Material Manager               " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. Display Material List                   " << endl;
        cout << "  2. Add Material                            " << endl;
        cout << "  3. Remove Material                         " << endl;
        cout << "  4. Modify Material                         " << endl;
        cout << "  5. Quit this Program                       " << endl;
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
            cout << "Enter Material ID to remove: ";
            cin >> id;
            remove(id);
            break;
        case 4:
            cout << "Enter Material ID to modify: ";
            cin >> id;
            modify(id);
            break;
        case 5:
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

int MaterialManager::makeId() {
    int maxId = 0;
    for (const auto& pair : materialList) {
        if (pair.first > maxId) {
            maxId = pair.first;
        }
    }
    return maxId + 1;
}

vector<string> MaterialManager::parseCSV(istream& str, char delimiter) {
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
