#include "materialmanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

MaterialManager::MaterialManager() {
    ifstream file("materiallist.txt");  // "materiallist.txt" ������ �б� ���� ����.
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');  // CSV �������� �����͸� �о�´�.
            if (row.size() > 0) {
                int id = stoi(row[0]);  // ù ��° ���� ������ ID�� ��ȯ
                int unitPrice = stoi(row[3]);  // �� ��° ���� �Ǽ��� �ܰ��� ��ȯ
                int stock = stoi(row[4]);  // �ټ� ��° ���� ������ ������� ��ȯ
                int orderQuantity = stoi(row[5]);  // ���� ��° ���� ������ �ֹ������� ��ȯ
                Material* m = new Material(id, row[1], row[2], unitPrice, stock, orderQuantity);  // ���� ��ü ����
                materialList[id] = m;  // ID�� Ű�� �Ͽ� materialList�� ���縦 ����
            }
        }
    }
    file.close();  // ���� �ݱ�
}

MaterialManager::~MaterialManager() {
    ofstream file("materiallist.txt");  // "materiallist.txt" ������ ���� ���� ����.
    if (!file.fail()) {
        for (const auto& pair : materialList) {
            Material* m = pair.second;
            file << m->getId() << "," << m->getName() << "," << m->getSupplier() << ","
                 << m->getUnitPrice() << "," << m->getStock() << "," << m->getOrderQuantity() << endl;
        }
    }
    file.close();  // ���� �ݱ�

    for (auto& pair : materialList) {
        delete pair.second;  // �������� �Ҵ�� ���� ��ü ����
    }
}

void MaterialManager::create() {
    string name, supplier;
    int stock, orderQuantity, unitPrice;

    cout << "�����: ";
    cin >> name;
    cout << "���޾�ü: ";
    cin >> supplier;
    cout << "�ܰ�: ";
    cin >> unitPrice;
    cout << "���: ";
    cin >> stock;
    cout << "�ֹ���: ";
    cin >> orderQuantity;

    int id = makeId();  // ���ο� ���� ID ����
    Material* material = new Material(id, name, supplier, unitPrice, stock, orderQuantity);
    materialList[id] = material;  // ���� ����Ʈ�� �߰�

    cout << "���簡 ���������� �߰��Ǿ����ϴ�!" << endl;
}

void MaterialManager::remove(int id) {
    auto it = materialList.find(id);
    if (it != materialList.end()) {
        delete it->second;  // �������� �Ҵ�� ���� ��ü ����
        materialList.erase(it);  // ���� ����Ʈ���� ����
        cout << "���簡 ���������� �����Ǿ����ϴ�!" << endl;
    } else {
        cout << "����ID " << id << "��(��) ã�� �� �����ϴ�..." << endl;
    }
}

Material* MaterialManager::search(int id) {
    auto it = materialList.find(id);
    if (it != materialList.end()) {
        return it->second;  // ���� ã�� ����
    } else {
        cout << "����ID " << id << "��(��) ã�� �� �����ϴ�..." << endl;
        return nullptr;  // ���� ã�� ����
    }
}

void MaterialManager::modify(int id) {
    Material* material = search(id);
    if (material) {
        string name, supplier;
        int stock, orderQuantity, unitPrice;

        cout << "���� �����: " << material->getName() << endl;
        cout << "���� ���޾�ü: " << material->getSupplier() << endl;
        cout << "���� �ܰ�: " << material->getUnitPrice() << endl;
        cout << "���� ���: " << material->getStock() << endl;
        cout << "���� �ֹ���: " << material->getOrderQuantity() << endl;

        cout << "���ο� ������� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) material->setName(name);

        cout << "���ο� ���޾�ü�� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        getline(cin, supplier);
        if (!supplier.empty()) material->setSupplier(supplier);

        cout << "���ο� �ܰ��� �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
        cin >> unitPrice;
        if (unitPrice >= 0) material->setUnitPrice(unitPrice);

        cout << "���ο� ����� �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
        cin >> stock;
        if (stock >= 0) material->setStock(stock);

        cout << "���ο� �ֹ����� �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
        cin >> orderQuantity;
        if (orderQuantity >= 0) material->setOrderQuantity(orderQuantity);

        cout << "���������� �����Ǿ����ϴ�!" << endl;
    }
}

void MaterialManager::displayInfo() {
    setCmdColor(1);
    printf("%6s | %10s | %10s | %10s | %6s | %6s\n", "����ID", "�����", "���޾�ü", "�ܰ�", "���", "�ֹ���");

    for (const auto& pair : materialList) {
        Material* m = pair.second;
        cout << setw(6) << m->getId() << " | ";  // ���� ID ���
        cout << setw(10) << m->getName() << " | ";  // ����� ���
        cout << setw(10) << m->getSupplier() << " | ";  // ���޾�ü�� ���
        cout << setw(10) << fixed << m->getUnitPrice() << " | ";  // �ܰ� ���
        cout << setw(6) << m->getStock() << " | ";  // ��� ���
        cout << setw(6) << m->getOrderQuantity() << endl;  // �ֹ��� ���
    }
    setCmdColor();

}

void MaterialManager::displayMenu() {
    int choice, id;
    bool running = true;

    while (running) {
        cout << "\033[2J\033[1;1H";  // ȭ���� ����� Ŀ���� �� ���� �̵�
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��                \033[30;93m�������\033[0m                   \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m1. ���� ��ȸ\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m2. ���� ���\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m3. ���� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m4. ���� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;91m5. ������� ������\033[0m                       \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "� �׸��� �����Ͻðڽ��ϱ�? ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayInfo();  // ���� ������ ���
            break;
        case 2:
            create();  // ���縦 �����Ͽ� ����Ʈ�� �߰�
            break;
        case 3:
            cout << "������ ����ID�� �Է����ּ���: ";
            cin >> id;
            remove(id);  // ���縦 ����
            break;
        case 4:
            cout << "������ ����ID�� �Է����ּ���: ";
            cin >> id;
            modify(id);  // ���縦 ����
            break;
        case 5:
            running = false;  // ���α׷� ����
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
            break;
        }
        if (running) {
            cout << "\n����Ϸ��� Enter Ű�� �����ּ���...";
            cin.ignore();
            cin.get();  // Enter �Է��� ��ٸ�
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
    return maxId + 1;  // ���ο� ID ����
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
    return result;  // CSV �Ľ� ��� ��ȯ
}

void MaterialManager::showAllDatas(){

}

