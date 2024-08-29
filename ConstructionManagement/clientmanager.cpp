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
        setCmdColor(1);
		printf("%6s | %10s | %14s | %10s\n", "��ID", "����", "��ȭ��ȣ", "�ּ�");
		for (auto it = clientList.begin(); it != clientList.end(); it++)
		{
			int key = it->first;
			Client* c = clientList[key];
			c->showInfo();
		}
	}
	else {
        setCmdColor(2);
		cout << "��ϵ� ���� �����ϴ�." << endl;
	}
    setCmdColor();
}
void ClientManager::displayInfo(int key)
{
    
    if (clientList.find(key) != clientList.end())
    {
        setCmdColor(1);
        printf("%6s | %10s | %14s | %10s\n", "��ID", "����", "��ȭ��ȣ", "�ּ�");
        Client* c = clientList[key];
        c->showInfo();
    }
    else {
        setCmdColor(2);
        cout << "�ش� ���� �����ϴ�." << endl;
    }
    setCmdColor();
}

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
    bool running = true;
    while (running)
    {
        string ch;
        string keystr = "-1";
        int key;
        cout << "\033[2J\033[1;1H";
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��                \033[30;93m������\033[0m                   \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m1. ��ü �� ��ȸ\033[0m                        \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m2. �� ID ��ȸ\033[0m                          \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m3. �� ���\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m4. �� ���� ����\033[0m                        \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m5. �� ���� ����\033[0m                        \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;91m6. ������ ������\033[0m                       \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << " � �׸��� �����Ͻðڽ��ϱ�? ";
        cin >> ch;
        if (!(ch == "1" || ch == "2" || ch == "3" || ch == "4" || ch == "5" || ch == "6"))
        {
            goto ff;
        }

        // 0x30<= stoi(ch) <= 0x36
        switch (stoi(ch)) {
        case 1:
            displayInfo();
            waitEnter();
            break;

        case 2:
            cout << "   ��ȸ�� ��ID�� �Է����ּ���: ";
            cin >> keystr;
            if (atoi(keystr.c_str()) == 0 && keystr != "0")
            {
                goto ff;
            }
            key = stoi(keystr);
            displayInfo(key);
            waitEnter();
            break;
        case 3:
            create();
            waitEnter();
            break;
        case 4:
            displayInfo();
            cout << "������ ��ID�� �Է����ּ���: ";
            cin >> keystr;
            if (atoi(keystr.c_str()) == 0 && keystr != "0")
            {
                goto ff;
            }
            remove(stoi(keystr));
            waitEnter();
            break;
        case 5:
            displayInfo();
            cout << "������ ��ID�� �Է����ּ���: ";
            cin >> keystr;
            if (atoi(keystr.c_str()) == 0 && keystr != "0")
            {
                goto ff;
            }
            modify(stoi(keystr));
            waitEnter();
            break;
        case 6:
            return;
        default:
        ff:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
            waitEnter();
            break;
        }
    }

}

void ClientManager::showAllDatas()
{
    displayInfo();
}
