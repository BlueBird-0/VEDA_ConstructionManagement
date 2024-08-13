#include "employeemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>

void EmployeeManager::create()
{
    string name, jobTitle, phoneNum;

    cleanCMD();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "직원명: ";
    cin >> name;
    cout << "직책: ";
    cin >> jobTitle;
    cout << "연락처: ";
    cin >> phoneNum;

    int newId = m_employeeList.size();
    Employee* material = new Employee(newId, name, jobTitle, phoneNum);
    m_employeeList[newId] = material;

    cout << "직원 생성 성공!" << endl;
    saveCSV();
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

                Employee* employee = new Employee(id, name, jobTitle, phoneNum);
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
            file << employee->getPhoneNum() << endl;
        }
    }
    file.close();
}


void EmployeeManager::showAllDatas()
{
    cleanCMD();
	for (auto it = m_employeeList.begin(); it != m_employeeList.end(); it++)
    {
        Employee* employee = it->second;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "ID: " << employee->getId() << endl;
        cout << "이름: " << employee->getName() << endl;
        cout << "직책: " << employee->getJobTitle() << endl;
        cout << "연락처: " << employee->getPhoneNum() << endl;
        cout << endl << endl;
    }
    cout << "아무키나 입력하세요.";
    string temp;
    cin >> temp;
}

void EmployeeManager::run(){
    while(true)
    {
        cleanCMD();
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                 인력 관리                   " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. 인력 추가                               " << endl;
        cout << "  2. 인력 수정                               " << endl;
        cout << "  3. 인력 삭제                               " << endl;
        cout << "  4. 모든 인력 보기                          " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Enter your choice: ";
        string input;
        cin >> input;

        if (input == "1") 
        {
            create();
        }
        else if (input == "2")
        {
            //
		}
        else if (input == "3")
        {
            //
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
