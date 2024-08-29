#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <string>

#include "project.h"
#include "projectmanager.h"

ProjectManager::ProjectManager()
{
    ifstream file;
    file.open("projectlist.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                Project* p = new Project(id, row[1], row[2], row[3], row[4], stoi(row[5]));
                projectList[id] = p;
            }
        }
    }
    file.close();
}

ProjectManager::~ProjectManager()
{
    ofstream file;
    file.open("projectlist.txt");
    if (!file.fail())
    {
        for (const auto& v : projectList)
        {
            Project* p = v.second;
            file << p->id() << ", " << p->getProjectName() << ", ";
            file << p->getLocation() << ", " << p->getStartDate() << ", ";;
            file << p->getEndDate() << ", " << p->getBudget() << endl;
        }
    }
    file.close();

    for (auto& pair : projectList)
    {
        delete pair.second;  // �������� �Ҵ�� ������Ʈ ��ü ����
    }
}

void ProjectManager::create()
{
    string name, location, startDate, endDate, budget;

    cout << "������Ʈ��: ";
    cin >> name;
    cout << "��ġ: ";
    cin >> location;
    cout << "������: ";
    cin >> startDate;
    cout << "������: ";
    cin >> endDate;
    cout << "����: ";
    cin >> budget; //cin.ignore(); getline(cin, budget, '\n'); //cin >> address;

    int id = makeId();
    Project* p = new Project(id, name, location, startDate, endDate, stoi(budget));
    projectList[id] = p;

    cout << "������Ʈ�� ���������� �߰��Ǿ����ϴ�!" << endl;
}

void ProjectManager::remove(int id)
{
    auto it = projectList.find(id);
    if (it != projectList.end()) {
        delete it->second;  // �������� �Ҵ�� ������Ʈ ��ü ����
        projectList.erase(it);  // ������Ʈ ����Ʈ���� ����
        cout << "������Ʈ�� ���������� �����Ǿ����ϴ�!" << endl;
    }
    else {
        cout << "������ƮID " << id << "��(��) ã�� �� �����ϴ�..." << endl;
    }
}

Project* ProjectManager::search(int id)
{
    auto it = projectList.find(id);
    if (it != projectList.end()) {
        return it->second;  // ������Ʈ ã�� ����
    }
    else {
        cout << "������ƮID " << id << "��(��) ã�� �� �����ϴ�..." << endl;
        return nullptr;  // ������Ʈ ã�� ����
    }
}



void ProjectManager::modify(int id)
{
    Project* project = projectList[id];
    if (project) {
        string name, location, startDate, endDate;
        int budget = 0;

        cout << "���� ������Ʈ��: " << project->getProjectName() << endl;
        cout << "���� ��ġ: " << project->getLocation() << endl;
        cout << "���� ������: " << project->getStartDate() << endl;
        cout << "���� ������: " << project->getEndDate() << endl;
        cout << "���� ����: " << project->getBudget() << endl;

        cout << "���ο� ������Ʈ���� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) project->setProjectName(name);

        cout << "���ο� ��ġ�� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        getline(cin, location);
        if (!location.empty()) project->setLocation(location);

        cout << "���ο� �����ϸ� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        getline(cin, startDate);
        if (!startDate.empty()) project->setStartDate(startDate);

        cout << "���ο� �����ϸ� �Է����ּ���. (�ƴϸ� EnterŰ�� ���� ���� ���� ����): ";
        getline(cin, endDate);
        if (!endDate.empty()) project->setEndDate(endDate);

        cout << "���ο� ������ �Է����ּ���. (�ƴϸ� -1�� �Է��Ͽ� ���� ���� ����): ";
        cin >> budget;
        if (budget >= 0) project->setBudget(budget);

        cout << "���������� �����Ǿ����ϴ�!" << endl;
        cout << "\n����Ϸ��� Enter Ű�� �����ּ���...";
        cin.ignore();
        cin.get();  // Enter �Է��� ��ٸ�
    }
}

void ProjectManager::displayInfo()
{
    cout << endl << "  ������ƮID  |     ������Ʈ��     | ��ġ | ������ | ������ | ���� " << endl;
    for (const auto& v : projectList)
    {
        int key = v.first;
        Project* p = projectList[key];
        p->showInfo();
    }
}

void ProjectManager::displayInfo(int key)
{
    cout << endl << "  ������ƮID  |     ������Ʈ��     | ��ġ | ������ | ������ | ���� " << endl;
    Project* p = projectList[key];
    p->showInfo();

}

/*void ProjectManager::showInfo(int key)
{
    Project* p = projectList[key];
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProjectName() << " | ";
    cout << setw(12) << p->getLocation() << " | ";
    cout << setw(12) << p->getStartDate() << " | ";
    cout << setw(12) << p->getEndDate() << " | ";
    cout << p->getBudget() << endl;
}*/


int ProjectManager::makeId()
{
    if (projectList.size() == 0) {
        return 0;
    }
    else {
        auto elem = projectList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> ProjectManager::parseCSV(istream& file, char delimiter)
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


void ProjectManager::displayMenu()
{
    while (1)
    {
        string ch, key;
        cout << "\033[2J\033[1;1H";
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��               \033[30;93m������Ʈ����\033[0m                \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m1. ������Ʈ ��ü��ȸ\033[0m                     \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m2. ������Ʈ ID��ȸ\033[0m                       \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m3. ������Ʈ ���\033[0m                         \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m4. ������Ʈ ����\033[0m                         \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m5. ������Ʈ ����\033[0m                         \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;91m6. ������Ʈ���� ������\033[0m                   \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << " � �׸��� �����Ͻðڽ��ϱ�? ";
        cin.ignore();
        cin >> ch;
        if (!(ch == "1" || ch == "2" || ch == "3" || ch == "4" || ch == "5" || ch == "6"))
        {
            goto ff;
        }
        switch (atoi(ch.c_str())) {
        case 1:
            displayInfo();
            cin.ignore();
            getchar();
            break;
        case 2:
            cout << "   ��ȸ�� ������ƮID�� �Է����ּ���: ";
            cin >> key;
            if (atoi(key.c_str()) == 0 && key != "0")
            {
                goto ff;
            }
            displayInfo(stoi(key));
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
            cout << "   ������ ������ƮID�� �Է����ּ���: ";
            cin >> key;
            if (atoi(key.c_str()) == 0 && key != "0")
            {
                goto ff;
            }
            remove(stoi(key));
            cin.ignore();
            getchar();
            break;
        case 5:
            displayInfo();
            cout << "   ������ ������ƮID�� �Է����ּ���: ";
            cin >> key;
            if (atoi(key.c_str()) == 0 && key != "0")
            {
                goto ff;
            }
            modify(stoi(key));
            cin.ignore();
            getchar();
            break;
        case 6:
            return;
        default:
        ff:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
            break;
        }
    }


}

void ProjectManager::showAllDatas() {
    displayInfo();
}
