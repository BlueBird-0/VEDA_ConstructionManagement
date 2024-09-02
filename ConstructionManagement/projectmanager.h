#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include <map>
#include <vector>
#include "project.h"
#include "manager.h"

using namespace std;

class ProjectManager : public Manager
{
private:
    void displayNotFoundId(int id);
public:
    ProjectManager();
    ~ProjectManager();

    void create();
    void remove(int);
    void modify(int);
    Project* search(int);
    int makeId();
    void displayInfo();
    void displayInfo(int);

    vector<string> parseCSV(istream&, char);

    virtual void displayMenu();
    //bool displayMenu();

    virtual void showAllDatas();

private:
    map<int, Project*> projectList;
};

#endif    // __PROJECT_MANAGER_H__
