#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
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
        delete pair.second;  // 동적으로 할당된 프로젝트 객체 삭제
    }
}

void ProjectManager::create()
{
    string name, location, startDate, endDate, budget;

    cout << "프로젝트명: "; 
    cin >> name;
    cout << "위치: "; 
    cin >> location;
    cout << "시작일: "; 
    cin >> startDate;
    cout << "종료일: "; 
    cin >> endDate;
    cout << "예산: "; 
    cin >> budget; //cin.ignore(); getline(cin, budget, '\n'); //cin >> address;

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
        cout << "프로젝트ID " << id << "을(를) 찾을 수 없습니다..." << endl;
    }
}

Project* ProjectManager::search(int id)
{
    auto it = projectList.find(id);
    if (it != projectList.end()) {
        return it->second;  // 프로젝트 찾기 성공
    }
    else {
        cout << "프로젝트ID " << id << "을(를) 찾을 수 없습니다..." << endl;
        return nullptr;  // 프로젝트 찾기 실패
    }
}



void ProjectManager::modify(int id)
{
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

void ProjectManager::displayInfo()
{
    cout << endl << "  프로젝트ID  |     프로젝트명     | 위치 | 시작일 | 종료일 | 예산 " << endl;
    for (const auto& v : projectList)
    {
        int key = v.first;
        showInfo(key);
    }
}

void ProjectManager::displayInfo(int key)
{
    cout << endl << "  프로젝트ID  |     프로젝트명     | 위치 | 시작일 | 종료일 | 예산 " << endl;
    showInfo(key);

}

void ProjectManager::showInfo(int key)
{
    Project* p = projectList[key];
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProjectName() << " | ";
    cout << setw(12) << p->getLocation() << " | ";
    cout << setw(12) << p->getStartDate() << " | ";
    cout << setw(12) << p->getEndDate() << " | ";
    cout << p->getBudget() << endl;
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


bool ProjectManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              프로젝트관리                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. 프로젝트 전체조회                    " << endl;
    cout << "  2. 프로젝트 ID조회                    " << endl;
    cout << "  3. 프로젝트 등록                            " << endl;
    cout << "  4. 프로젝트 삭제                           " << endl;
    cout << "  5. 프로젝트 수정                           " << endl;
    cout << "  6. 프로젝트관리 나가기                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " 어떤 항목을 선택하시겠습니까? ";
    cin >> ch;
    switch (ch) {
    case 1:
        displayInfo();
        cin.ignore();
        getchar();
        break;
    case 2:
        cout << "   조회할 프로젝트ID를 입력해주세요: ";
        cin >> key;
        displayInfo(key);
        break;
    case 3:
        create();
        break;
    case 4:
        //displayInfo();
        cout << "   삭제할 프로젝트ID를 입력해주세요: ";
        cin >> key;
        remove(key);
        break;
    case 5:
        //displayInfo();
        cout << "   수정할 프로젝트ID를 입력해주세요: ";
        cin >> key;
        modify(key);
        break;
    case 6:
        return false;
        break;
    default:
        cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
        break;

    }
    return true;
}
