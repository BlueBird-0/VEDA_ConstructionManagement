#include "employeemanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include <windows.h>

void EmployeeManager::create()
{
    string name, jobTitle, phoneNum;
    vector<int> projectIdList;

    cout << "\033[2J\033[1;1H";  // Clear screen
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "������: ";
    cin >> name;
    cout << "��å: ";
    cin >> jobTitle;
    cout << "����ó: ";
    cin >> phoneNum;
    cout << "������ƮID: (-1 �Է½�����) ";
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

    cout << "���������� �߰��Ǿ����ϴ�!" << endl;
    saveCSV();
}

void EmployeeManager::remove()
{
    cout << "\033[2J\033[1;1H";  // Clear screen
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "������ ���� ID�� �Է��ϼ���: ";
    string idStr;
    cin >> idStr;
    int id = atoi(idStr.c_str());
    if (idStr != "0" && id == 0)
        id = -1;

    for (auto it = m_employeeList.begin(); it != m_employeeList.end(); ++it) {
        Employee* employee = it->second;
        if (employee->getId() == id) {
            m_employeeList.erase(id);
            cout << "������ ���������� �����Ǿ����ϴ�!" << endl;
            return;
        }
    }
    cout << "�ش� ID " << idStr << " �� ������(��) ã�� �� �����ϴ�..." << endl;
    string temp;
    cin >> temp;
}

void EmployeeManager::modify()
{
    cout << "\033[2J\033[1;1H";  // Clear screen
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "������ ���� ID�� �Է��ϼ���: ";
    string idStr;
    cin >> idStr;
    if (m_employeeList.find(stoi(idStr)) != m_employeeList.end())
    {
        auto employee = m_employeeList[stoi(idStr)];
        if (employee->getId() == stoi(idStr)) {
            employee->showInfo();
            cout << "+++++++++++++++++������ ����++++++++++++++++" << endl;
            string name, jobTitle, phoneNum;
            vector<int> projectIdList;
            cout << "������ (�����Է½� ���� ���� ����): ";
            cin >> name;
            if (name != "")
                employee->setName(name);
            cout << "��å (�����Է½� ���� ���� ����): ";
            cin >> jobTitle;
            if (name != "")
                employee->setJobTitle(jobTitle);
            cout << "����ó (�����Է½� ���� ���� ����): ";
            cin >> phoneNum;
            if (phoneNum != "")
                employee->setPhoneNum(phoneNum);
            cout << "������ƮID (-1�Է½� ����): ";
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
            cout << "���������� �����Ǿ����ϴ�!" << endl;
            return;
        }
    }
    else {
        cout << "�ش� ID " << idStr << " �� ������(��) ã�� �� �����ϴ�..." << endl;
    }
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
    setCmdColor(1);
    if (!m_employeeList.empty()) {
        //cout << "�� �ο� [" << m_employeeList.size() << "]" << endl;
        printf("%6s | %10s | %8s | %14s | %10s \n", "����ID", "������", "��å", "����ó", "���� ������ƮID");
        for (auto it = m_employeeList.begin(); it != m_employeeList.end(); it++)
        {
            Employee* employee = it->second;
            employee->showInfo();
        }
    }
    else {
        setCmdColor(2);
        cout << "��ϵ� ������ �����ϴ�." << endl;
    }
    setCmdColor();
    waitEnter();
}

void EmployeeManager::displayMenu(){
    while(true)
    {
        cout << "\033[2J\033[1;1H";  // Clear screen
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��                 \033[30;93m�η°���\033[0m                  \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m1. �η� ��ü��ȸ\033[0m                         \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m2. �η� �߰�\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m3. �η� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;97m4. �η� ����\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m��  \033[30;91mexit. ������\033[0m                             \033[30;94m�� \033[0m" << endl;
        cout << "\033[30;94m������������������������������������������������������������������������������������������ \033[0m" << endl;
        cout << "� �׸��� �����Ͻðڽ��ϱ�? ";
        string input;
        cin >> input;
		if (input == "1") {
            showAllDatas();
        }
        else if (input == "2")
        {
            create();
        }
        else if (input == "3")
        {
            modify();
        }
        else if (input == "4")
        {
            remove();
        }
        else if (input == "exit" || input == "5")
        {
            return;
        }
        else {
            setCmdColor(2);
            cout << "�߸��� �����Դϴ�. �ٽ� �Է����ּ���." << endl;
            setCmdColor();
            waitEnter();
        }
    }
}

vector<Employee> EmployeeManager::search(int projectId)
{
    vector<Employee> returnEmployeeList;
    for (pair<int, Employee*> pair : m_employeeList) {
        Employee* employee = pair.second;
        vector<int> projectIdList = employee->getProjectIdList();

        //employee���� projectId�� �ִٸ�, ����Ʈ�� �߰�
        if (find(projectIdList.begin(), projectIdList.end(), projectId) != projectIdList.end()) {
            returnEmployeeList.push_back(*employee);
        }
    }
    return returnEmployeeList;
}
