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
	string getJobTitle() const { return m_jobTitle; }
	string getPhoneNum() const { return m_phoneNum; }
	vector<int> getProjectIdList() const { return m_projectIdList;  };

	virtual void showInfo();
private:
	string m_employeeName;
	string m_jobTitle;
	string m_phoneNum;
	vector<int> m_projectIdList;
	int m_hoursWorked;
};
