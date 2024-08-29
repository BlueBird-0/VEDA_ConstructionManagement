#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include "object.h"
using namespace std;

using namespace std;
class Employee : public Object
{
public:
    Employee(int id, string employeeName, string jobTitle, string phoneNum, vector<int> projectIds = vector<int>(), int hoursWorked = 0)
        : Object(id), m_employeeName(employeeName), m_jobTitle(jobTitle), m_phoneNum(phoneNum), m_projectIdList(projectIds), m_hoursWorked(hoursWorked) {}

    string getName() const { return m_employeeName; }
    void setName(string str) { this->m_employeeName = str; }
    string getJobTitle() const { return m_jobTitle; }
    void setJobTitle(string str) { this->m_jobTitle = str; }
    string getPhoneNum() const { return m_phoneNum; }
    void setPhoneNum(string str) { this->m_phoneNum = str; }
    vector<int> getProjectIdList() const { return m_projectIdList;  };
    void setProjectIdList(vector<int> list) { this->m_projectIdList = list; }

    virtual void showInfo();
private:
    string m_employeeName;
    string m_jobTitle;
    string m_phoneNum;
    vector<int> m_projectIdList;
    int m_hoursWorked;
};
