#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

#include <string>

#include "project.h"
#include "projectmanager.h"

void ProjectManager::displayNotFoundId(int id)
{
    setCmdColor(2);
    cout << "프로젝트ID " << id << "을(를) 찾을 수 없습니다..." << endl;
    setCmdColor();
}

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
        delete pair.second;  // 동적으로 할당된 프로젝트 객체 삭제
    }
}

void ProjectManager::create()
{
    string name, location, startDate, endDate, budget;
    setCmdColor(0);
    printf("예시) %14s | %10s | %11s | %11s | %13s\n", "프로젝트명", "위치", "시작일","종료일","예산(₩)");
    printf("      %14s | %10s | %11s | %11s | %13s\n", "도로 공사", "부산광역시", "2023-02-15","2024-02-15","800000000");
    printf("\n");
    setCmdColor();
    cout << "프로젝트명: ";
    cin >> name;
    if (name == "exit")    return;
    cout << "위치: ";
    cin >> location;
    if (location == "exit")    return;
    cout << "시작일: ";
    cin >> startDate;
    if (startDate == "exit")    return;
    cout << "종료일: ";
    cin >> endDate;
    if (endDate == "exit")    return;
    cout << "예산: ";
    cin >> budget;
    if (budget == "exit")    return;

    int id = makeId();
    Project* p = new Project(id, name, location, startDate, endDate, stoi(budget));
    projectList[id] = p;

    cout << "프로젝트가 성공적으로 추가되었습니다!" << endl;
}

void ProjectManager::remove(int id)
{
    auto it = projectList.find(id);
    if (it != projectList.end()) {
        delete it->second;  // 동적으로 할당된 프로젝트 객체 삭제
        projectList.erase(it);  // 프로젝트 리스트에서 삭제
        cout << "프로젝트가 성공적으로 삭제되었습니다!" << endl;
    }
    else {
        displayNotFoundId(id);
    }
}

Project* ProjectManager::search(int id)
{
    auto it = projectList.find(id);
    if (it != projectList.end()) {
        return it->second;  // 프로젝트 찾기 성공
    }
    else {
        displayNotFoundId(id);
        return nullptr;  // 프로젝트 찾기 실패
    }
}



void ProjectManager::modify(int id)
{
    if (projectList.find(id) != projectList.end()) {
        Project* project = projectList[id];

        if (project) {
            string name, location, startDate, endDate;
            int budget = 0;

            cout << "현재 프로젝트명: " << project->getProjectName() << endl;
            cout << "현재 위치: " << project->getLocation() << endl;
            cout << "현재 시작일: " << project->getStartDate() << endl;
            cout << "현재 종료일: " << project->getEndDate() << endl;
            cout << "현재 예산: " << project->getBudget() << endl;

            cout << "새로운 프로젝트명을 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
            cin.ignore();
            getline(cin, name);
            if (!name.empty()) project->setProjectName(name);

            cout << "새로운 위치를 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
            getline(cin, location);
            if (!location.empty()) project->setLocation(location);

            cout << "새로운 시작일를 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
            getline(cin, startDate);
            if (!startDate.empty()) project->setStartDate(startDate);

            cout << "새로운 종료일를 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
            getline(cin, endDate);
            if (!endDate.empty()) project->setEndDate(endDate);

            cout << "새로운 예산을 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
            cin >> budget;
            if (budget >= 0) project->setBudget(budget);

            cout << "성공적으로 수정되었습니다!" << endl;
        }
    }
    else {
        displayNotFoundId(id);
    }
}

void ProjectManager::displayInfo()
{
    setCmdColor(1);
    if (!projectList.empty()) {
        printf("%10s | %14s | %10s | %11s | %11s | %13s\n", "프로젝트ID", "프로젝트명", "위치", "시작일", "종료일", "예산(₩)");    ///setw()
        for (const auto& v : projectList)
        {
            int key = v.first;
            Project* p = projectList[key];
            p->showInfo();
        }
    }else {
        setCmdColor(2);
		cout << "등록된 프로젝트가 없습니다." << endl;
	}

    setCmdColor();
}

void ProjectManager::displayInfo(int key)
{
    if (projectList.find(key) != projectList.end()) {
        setCmdColor(1);
        printf("%10s | %14s | %10s | %10s | %10s | %10s\n", "프로젝트ID", "프로젝트명", "위치", "시작일", "종료일", "예산(₩)");
        if (!projectList.empty()) {
            Project* p = projectList[key];
            p->showInfo();
        }
        setCmdColor();
    }
    else {
        displayNotFoundId(key);
    }
}

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
        cout << "\033[30;94m┌───────────────────────────────────────────┐ \033[0m" << endl;
        cout << "\033[30;94m│               \033[30;93m프로젝트관리\033[0m                \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│───────────────────────────────────────────│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m1. 프로젝트 전체조회\033[0m                     \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m2. 프로젝트 ID조회\033[0m                       \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m3. 프로젝트 등록\033[0m                         \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m4. 프로젝트 삭제\033[0m                         \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m5. 프로젝트 수정\033[0m                         \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;91mexit. 나가기\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m└───────────────────────────────────────────┘ \033[0m" << endl;
        cout << "어떤 항목을 선택하시겠습니까? ";
        cin >> ch;
		if (!(ch == "1" || ch == "2" || ch == "3" || ch == "4" || ch == "5" || ch == "6" || ch == "exit"))
        {
            goto ff;
        }
        if (ch == "1") {
            displayInfo();
        }
        else if (ch == "2") {
            cout << "조회할 프로젝트ID를 입력해주세요: ";
            cin >> key;
            if (atoi(key.c_str()) == 0 && key != "0")
            {
                goto ff;
            }
            displayInfo(stoi(key));
        }
        else if (ch == "3") {
            create();
        }
        else if (ch == "4") {
            displayInfo();
            cout << "삭제할 프로젝트ID를 입력해주세요: ";
            cin >> key;
            if (atoi(key.c_str()) == 0 && key != "0")
            {
                goto ff;
            }
            remove(stoi(key));
        }
        else if (ch == "5") {
            displayInfo();
            cout << "수정할 프로젝트ID를 입력해주세요: ";
            cin >> key;
            if (atoi(key.c_str()) == 0 && key != "0")
            {
                goto ff;
            }
            modify(stoi(key));
        }
		else if (ch == "6" || ch=="exit") {
            return;
        }
        else {
        ff:
            setCmdColor(2);
            cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
            setCmdColor();

        }
        waitEnter();
    }


}

void ProjectManager::showAllDatas() {
    displayInfo();
}
