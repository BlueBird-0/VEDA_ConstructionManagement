#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <iostream>
#include "object.h"

using namespace std;

class Project : public Object
{
public:
    Project(int projectId = 0, string projectName = "", string location = "", string startDate = "", string endDate = "", int projectBudget = 0);

    string getProjectName() const;
    void setProjectName(string&);

    string getLocation() const;
    void setLocation(string&);

    string getStartDate() const;
    void setStartDate(string&);

    string getEndDate() const;
    void setEndDate(string&);

    int getBudget() const;
    void setBudget(int);

    int id() const;

    void showInfo();

private:
    int m_projectId;

    string m_projectName;
    string m_location;
    string m_startDate;
    string m_endDate;
    int m_projectBudget;


};
#endif          // __PROJECT_H__
