#include "employee.h"
#include <iostream>

void Employee::showInfo()
{
	cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "ID: " << getId() << endl;
	cout << "�̸�: " << getName() << endl;
	cout << "��å: " << getJobTitle() << endl;
	cout << "����ó: " << getPhoneNum() << endl;
	cout << "���� ������ƮID: ";
	for (auto projectID : getProjectIdList())
	{
		cout << projectID << ", ";
	}

    cout << endl << endl;
}
