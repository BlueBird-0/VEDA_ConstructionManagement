#include "project.h"

#include <iostream>

using namespace std;

Project::Project(int m_projectId = 0, string m_projectName = "", string m_startDate = "", string m_endDate = "", int m_projectBudget = 0)
    : m_projectName(projectName), m_startDate(startDate), m_endDate(endDate), m_projectBudget(projectBudget)
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

void Project::setBudget(int projectBudget)
{
    m_endDate = endDate;
}

int Project::getBudget() const
{
    return m_projectBudget;
}

void Project::setEndDate(string& endDate)
{
    m_endDate = endDate;
}


int Project::id() const
{
    return m_projectId;
}

