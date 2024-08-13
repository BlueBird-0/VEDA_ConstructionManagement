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
    cout << "������: ";
    cin >> name;
    cout << "��å: ";
    cin >> jobTitle;
    cout << "����ó: ";
    cin >> phoneNum;

    int newId = m_employeeList.size();
    Employee* material = new Employee(newId, name, jobTitle, phoneNum);
    m_employeeList[newId] = material;

    cout << "���� ���� ����!" << endl;
    saveCSV();
}

EmployeeManager::EmployeeManager()
{
    //���Ͽ��� �ҷ�����
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
        cout << "�̸�: " << employee->getName() << endl;
        cout << "��å: " << employee->getJobTitle() << endl;
        cout << "����ó: " << employee->getPhoneNum() << endl;
        cout << endl << endl;
    }
    cout << "�ƹ�Ű�� �Է��ϼ���.";
    string temp;
    cin >> temp;
}

void EmployeeManager::run(){
    while(true)
    {
        cleanCMD();
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "                 �η� ����                   " << endl;
        cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "  1. �η� �߰�                               " << endl;
        cout << "  2. �η� ����                               " << endl;
        cout << "  3. �η� ����                               " << endl;
        cout << "  4. ��� �η� ����                          " << endl;
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
