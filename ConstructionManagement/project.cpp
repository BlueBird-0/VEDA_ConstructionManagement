#include "project.h"

#include <iostream>
#include <iomanip>

using namespace std;

Project::Project(int projectId, string projectName, string location, string startDate, string endDate, int projectBudget)
    : m_projectId(projectId), m_projectName(projectName), m_location(location), m_startDate(startDate), m_endDate(endDate), m_projectBudget(projectBudget)
{
}

string Project::getProjectName() const
{
    return m_projectName;
}

void Project::setProjectName(string& projectName)
{
    m_projectName = projectName;
}

string Project::getLocation() const
{
    return m_location;
}

void Project::setLocation(string& location)
{
    m_location = location;
}

string Project::getStartDate() const
{
    return m_startDate;
}

void Project::setStartDate(string& startDate)
{
    m_startDate = startDate;
}

string Project::getEndDate() const
{
    return m_endDate;
}

void Project::setEndDate(string& endDate)
{
    m_endDate = endDate;
}

int Project::getBudget() const
{
    return m_projectBudget;
}

void Project::setBudget(int projectBudget)
{
    m_projectBudget = projectBudget;
}


int Project::id() const
{
    return m_projectId;
}

void Project::showInfo()
{
    cout << setw(5) << setfill('0') << right << id() << " | " << left;
    cout << setw(12) << setfill(' ') << getProjectName() << " | ";
    cout << setw(12) << getLocation() << " | ";
    cout << setw(12) << getStartDate() << " | ";
    cout << setw(12) << getEndDate() << " | ";
    cout << getBudget() << endl;
}