#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "client.h"
#include "clientmanager.h"

ClientManager::ClientManager()
{
    ifstream file;
    file.open("clientlist.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                Client* c = new Client(id, row[1], row[2], row[3]);
                clientList[id] = c;
            }
        }
    }
    file.close();
}

ClientManager::~ClientManager()
{
    ofstream file;
    file.open("clientlist.txt");
    if (!file.fail()) 
    {
        for (const auto& v : clientList) 
        {
            Client* c = v.second;
            file << c->id() << ", " << c->getClientName() << ", ";
            file << c->getPhoneNum() << ", ";
            file << c->getAddress() << endl;
        }
    }
    file.close();

    for (auto& pair : clientList)
    {
        delete pair.second;  // �������� �Ҵ�� �� ��ü ����
    }
}

void ClientManager::create()
{
    string name, phoneNum, address;

    cout << "����: ";
    cin >> name;
    cout << "��ȭ��ȣ: ";
    cin >> phoneNum;
    cout << "�ּ�: ";
    cin >> address;


    int id = makeId();  // ���ο� �� ID ����
    Client* client = new Client(id, name, phoneNum, address);
    clientList[id] = client;  // �� ����Ʈ�� �߰�

    cout << "���� ���������� �߰��Ǿ����ϴ�!" << endl;
}

Client* ClientManager::search(int id)
{
    auto it = clientList.find(id);
    if (it != clientList.end()) {
        return it->second;  // �� ã�� ����
    }
    else {
        cout << "��ID " << id << "��(��) ã�� �� �����ϴ�..." << endl;
        return nullptr;  // �� ã�� ����
    }
}

void ClientManager::remove(int id)
{
    auto it = clientList.find(id);
    if (it != clientList.end()) {
        delete it->second;  // �������� �Ҵ�� �� ��ü ����
        clientList.erase(it);  // �� ����Ʈ���� ����
        cout << "�� ������ ���������� �����Ǿ����ϴ�!" << endl;
    }
    else {
        cout << "��ID " << id << "��(��) ã�� �� �����ϴ�..." << endl;
    }
}

void ClientManager::modify(int id)
{
    Client* client = search(id);
    if (client) {
        string name, phoneNum, address;

        cout << "���� ����: " << client->getClientName() << endl;
        cout << "���� ��ȭ��ȣ: " << client->getPhoneNum() << endl;
        cout << "���� �ּ�: " << client->getAddress() << endl;

        cout << "���ο� ������ �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) client->setClientName(name);

        cout << "���ο� ��ȭ��ȣ�� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        getline(cin, phoneNum);
        if (!phoneNum.empty()) client->setPhoneNum(phoneNum);

        cout << "���ο� �ּҸ� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        getline(cin, address);
        if (!address.empty()) client->setAddress(address);

        cout << "���������� �����Ǿ����ϴ�!" << endl;
    }
}

void ClientManager::displayInfo()
{
    if (clientList.size() != 0) {
        cout << endl << "  ID  |     ����     | ��ȭ��ȣ |      �ּ�" << endl;
        for (auto it = clientList.begin(); it != clientList.end(); it++)
        {
            int key = it->first;
            Client* c = clientList[key];
            c->showInfo();
        }
    }
    else {
        cout << "��ϵ� ���� �����ϴ�." << endl;
    }
    
}
void ClientManager::displayInfo(int key)
{
    if (clientList.find(key) != clientList.end())
    {
        cout << endl << "  ID  |     ����     | ��ȭ��ȣ |      �ּ�" << endl;
        Client* c = clientList[key];
        c->showInfo();
    }
    else {
        cout << "�ش� ���� �����ϴ�." << endl;
    }
}

//void ClientManager::showInfo(int key)
//{
//    Client* c = clientList[key];
//    cout << setw(5) << setfill('0') << right << c->id() << " | " << left;
//    cout << setw(12) << setfill(' ') << c->getClientName() << " | ";
//    cout << setw(12) << c->getPhoneNum() << " | ";
//    cout << c->getAddress() << endl;
//}

int ClientManager::makeId()
{
    if (clientList.size() == 0) {
        return 0;
    }
    else {
        auto elem = clientList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> ClientManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}


void ClientManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              ������                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. ��ü �� ��ȸ                     " << endl;
    cout << "  2. �� ID ��ȸ                     " << endl;
    cout << "  3. �� ���                            " << endl;
    cout << "  4. �� ���� ����                           " << endl;
    cout << "  5. �� ���� ����                          " << endl;
    cout << "  6. ������ ������                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " � �׸��� �����Ͻðڽ��ϱ�? ";
    cin >> ch;
    switch (ch) {
    case 1:
        displayInfo();
        cin.ignore();
        getchar();
        break;

    case 2:
        cout << "   ��ȸ�� ��ID�� �Է����ּ���: ";
        cin >> key;
        displayInfo(key);
        cin.ignore();
        getchar();
        break;

    case 3:
        create();
        cin.ignore();
        getchar();
        break;
    case 4:
        displayInfo();
        cout << "������ ��ID�� �Է����ּ���: ";
        cin >> key;
        remove(key);
        break;
    case 5:
        displayInfo();
        cout << "������ ��ID�� �Է����ּ���: ";
        cin >> key;
        modify(key);
        break;
    case 6:
        break;
    default:
        cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
        break;
    }
}

void ClientManager::showAllDatas() 
{
    displayInfo();
}
