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
        delete pair.second;  // 동적으로 할당된 고객 객체 삭제
    }
}

void ClientManager::create()
{
    string name, phoneNum, address;

    cout << "고객명: ";
    cin >> name;
    cout << "전화번호: ";
    cin >> phoneNum;
    cout << "주소: ";
    cin >> address;


    int id = makeId();  // 새로운 고객 ID 생성
    Client* client = new Client(id, name, phoneNum, address);
    clientList[id] = client;  // 고객 리스트에 추가

    cout << "고객이 성공적으로 추가되었습니다!" << endl;
}

Client* ClientManager::search(int id)
{
    auto it = clientList.find(id);
    if (it != clientList.end()) {
        return it->second;  // 고객 찾기 성공
    }
    else {
        cout << "고객ID " << id << "을(를) 찾을 수 없습니다..." << endl;
        return nullptr;  // 고객 찾기 실패
    }
}

void ClientManager::remove(int id)
{
    auto it = clientList.find(id);
    if (it != clientList.end()) {
        delete it->second;  // 동적으로 할당된 고객 객체 삭제
        clientList.erase(it);  // 고객 리스트에서 삭제
        cout << "고객 정보가 성공적으로 삭제되었습니다!" << endl;
    }
    else {
        cout << "고객ID " << id << "을(를) 찾을 수 없습니다..." << endl;
    }
}

void ClientManager::modify(int id)
{
    Client* client = search(id);
    if (client) {
        string name, phoneNum, address;

        cout << "현재 고객명: " << client->getClientName() << endl;
        cout << "현재 전화번호: " << client->getPhoneNum() << endl;
        cout << "현재 주소: " << client->getAddress() << endl;

        cout << "새로운 고객명을 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) client->setClientName(name);

        cout << "새로운 전화번호를 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
        getline(cin, phoneNum);
        if (!phoneNum.empty()) client->setPhoneNum(phoneNum);

        cout << "새로운 주소를 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
        getline(cin, address);
        if (!address.empty()) client->setAddress(address);

		cout << "성공적으로 수정되었습니다!" << endl;
	}
}

void ClientManager::displayInfo()
{
	if (clientList.size() != 0) {
        setCmdColor(1);
		printf("%6s | %10s | %14s | %10s\n", "고객ID", "고객명", "전화번호", "주소");
		for (auto it = clientList.begin(); it != clientList.end(); it++)
		{
			int key = it->first;
			Client* c = clientList[key];
			c->showInfo();
		}
	}
	else {
        setCmdColor(2);
		cout << "등록된 고객이 없습니다." << endl;
	}
    setCmdColor();
}
void ClientManager::displayInfo(int key)
{
    
    if (clientList.find(key) != clientList.end())
    {
        setCmdColor(1);
        printf("%6s | %10s | %14s | %10s\n", "고객ID", "고객명", "전화번호", "주소");
        Client* c = clientList[key];
        c->showInfo();
    }
    else {
        setCmdColor(2);
        cout << "해당 고객이 없습니다." << endl;
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
        cout << "\033[30;94m┌───────────────────────────────────────────┐ \033[0m" << endl;
        cout << "\033[30;94m│                \033[30;93m고객관리\033[0m                   \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│───────────────────────────────────────────│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m1. 전체 고객 조회\033[0m                        \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m2. 고객 ID 조회\033[0m                          \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m3. 고객 등록\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m4. 고객 정보 삭제\033[0m                        \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m5. 고객 정보 수정\033[0m                        \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;91m6. 고객관리 나가기\033[0m                       \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m└───────────────────────────────────────────┘ \033[0m" << endl;
        cout << " 어떤 항목을 선택하시겠습니까? ";
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
            cout << "   조회할 고객ID를 입력해주세요: ";
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
            cout << "삭제할 고객ID를 입력해주세요: ";
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
            cout << "수정할 고객ID를 입력해주세요: ";
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
            cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
            waitEnter();
            break;
        }
    }

}

void ClientManager::showAllDatas()
{
    displayInfo();
}
