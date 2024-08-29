#include "employeemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <windows.h>

void EmployeeManager::create()
{
    string name, jobTitle, phoneNum;
    vector<int> projectIdList;

    cleanCMD();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "직원명: ";
    cin >> name;
    cout << "직책: ";
    cin >> jobTitle;
    cout << "연락처: ";
    cin >> phoneNum;
    cout << "프로젝트ID: (-1 입력시종료) ";
    int input;
    while (true)
    {
        cin >> input;
        if (input == -1)
            break;
        else
            projectIdList.push_back(input);
    }

    int newId = m_employeeList.size();
    Employee* material = new Employee(newId, name, jobTitle, phoneNum, projectIdList);
    m_employeeList[newId] = material;

    cout << "성공적으로 추가되었습니다!" << endl;
    saveCSV();
}

void EmployeeManager::remove()
{
    cleanCMD();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "삭제할 직원 ID를 입력하세요: ";
    string idStr;
    cin >> idStr;
    int id = atoi(idStr.c_str());
    if (idStr != "0" && id == 0)
        id = -1;

    for (auto it = m_employeeList.begin(); it != m_employeeList.end(); ++it) {
        Employee* employee = it->second;
        if (employee->getId() == id) {
            m_employeeList.erase(id);
            cout << "직원이 성공적으로 삭제되었습니다!" << endl;
            return;
        }
    }
    cout << "해당 ID " << idStr << " 의 직원을(를) 찾을 수 없습니다..." << endl;
    string temp;
    cin >> temp;
}

void EmployeeManager::modify()
{
    cleanCMD();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "삭제할 직원 ID를 입력하세요: ";
    string idStr;
    cin >> idStr;
    if (m_employeeList.find(stoi(idStr)) != m_employeeList.end())
    {
        auto employee = m_employeeList[stoi(idStr)];
        if (employee->getId() == stoi(idStr)) {
            employee->showInfo();
            cout << "+++++++++++++++++수정할 정보++++++++++++++++" << endl;
            string name, jobTitle, phoneNum;
            vector<int> projectIdList;
            cout << "직원명 (공백입력시 현재 상태 유지): ";
            cin >> name;
            if (name != "")
                employee->setName(name);
            cout << "직책 (공백입력시 현재 상태 유지): ";
            cin >> jobTitle;
            if (name != "")
                employee->setJobTitle(jobTitle);
            cout << "연락처 (공백입력시 현재 상태 유지): ";
            cin >> phoneNum;
            if (phoneNum != "")
                employee->setPhoneNum(phoneNum);
            cout << "프로젝트ID (-1입력시 종료): ";
            int input;
            while (true)
            {
                cin >> input;
                if (input == -1)
                    break;
                else
                    projectIdList.push_back(input);
            }
            if (projectIdList.size() != 0)
                employee->setProjectIdList(projectIdList);
            cout << "성공적으로 수정되었습니다!" << endl;
            return;
        }
    }
    else {
        cout << "해당 ID " << idStr << " 의 직원을(를) 찾을 수 없습니다..." << endl;
    }
}

EmployeeManager::EmployeeManager()
{
    //파일에서 불러오기
    ifstream file("employeeList.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size() > 0) {
                int id = stoi(row[0]);
                string name = row[1];
                string jobTitle = row[2];
                string phoneNum = row[3];
                string projectIdStr = row[4];
                vector<int> projectIdList;
                while(true)
                {
                    int i = projectIdStr.find('&');
                    if (i == -1) {
                        break;
                    }
                    else {
                        projectIdList.push_back(stoi(projectIdStr.substr(0, i)));
                        projectIdStr.erase(0, i+1);
                    }
                }

                Employee* employee = new Employee(id, name, jobTitle, phoneNum, projectIdList);
                m_employeeList[id] = employee;
            }
        }
    }
    file.close();
}

vector<string> EmployeeManager::parseCSV(istream& str, char delimiter) {
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

void EmployeeManager::saveCSV()
{
    ofstream file("employeeList.txt");
    if (!file.fail()) {

        for (auto it = m_employeeList.begin(); it != m_employeeList.end(); it++)
        {
            Employee* employee = it->second;
            file << employee->getId() << ",";
            file << employee->getName() << ",";
            file << employee->getJobTitle() << ",";
            file << employee->getPhoneNum() << ",";
            for (auto id : employee->getProjectIdList()) {
                file << id << "&";
            }
            file << endl;
        }
    }
    file.close();
}


void EmployeeManager::showAllDatas()
{
    cleanCMD();

    cout << "총 인원 [" << m_employeeList.size() << "]" << endl;
    for (auto it = m_employeeList.begin(); it != m_employeeList.end(); it++)
    {
        Employee* employee = it->second;
        employee->showInfo();
    }
    cout << "아무키나 입력하세요.";
    string temp;
    cin >> temp;
}

void EmployeeManager::displayMenu(){
    while(true)
    {
        cleanCMD();
        cout << "\033[30;94m┌───────────────────────────────────────────┐\033[0m" << endl;
        cout << "\033[30;94m│                \033[30;93m인력관리\033[0m                   \033[30;94m│\033[0m" << endl;
        cout << "\033[30;94m│───────────────────────────────────────────│\033[0m" << endl;
        cout << "\033[30;94m│   \033[30;97m1. 인력 추가\033[0m                            \033[30;94m│\033[0m" << endl;
        cout << "\033[30;94m│   \033[30;97m2. 인력 수정\033[0m                            \033[30;94m│\033[0m" << endl;
        cout << "\033[30;94m│   \033[30;97m3. 인력 삭제\033[0m                            \033[30;94m│\033[0m" << endl;
        cout << "\033[30;94m│   \033[30;97m4. 모든 인력 보기\033[0m                       \033[30;94m│\033[0m" << endl;
        cout << "\033[30;94m│   \033[30;91mexit. 인력관리 나가기\033[0m                   \033[30;94m│\033[0m" << endl;
        cout << "\033[30;94m└───────────────────────────────────────────┘\033[0m" << endl;
        cout << "어떤 항목을 선택하시겠습니까? ";
        string input;
        cin >> input;

        if (input == "1")
        {
            create();
        }
        else if (input == "2")
        {
            modify();
        }
        else if (input == "3")
        {
            remove();
        }
        else if (input == "4")
        {
            showAllDatas();
        }
        else if (input == "exit")
        {
            return;
        }

    }
}

vector<Employee> EmployeeManager::search(int projectId)
{
    vector<Employee> returnEmployeeList;
    for (pair<int, Employee*> pair : m_employeeList) {
        Employee* employee = pair.second;
        vector<int> projectIdList = employee->getProjectIdList();

        //employee에게 projectId가 있다면, 리스트에 추가
        if (find(projectIdList.begin(), projectIdList.end(), projectId) != projectIdList.end()) {
            returnEmployeeList.push_back(*employee);
        }
    }
    return returnEmployeeList;
}
