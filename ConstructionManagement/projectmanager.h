#ifndef __PROJECT_MANAGER_H__
#define __PROJECT_MANAGER_H__

#include <map>
#include <vector>
#include "project.h"

using namespace std;

class ProjectManager {
public:
    ProjectManager();
    ~ProjectManager();

    void create();
    void remove(int);
    void modify(int);
    Project* search(int);
    int makeId();
    void displayInfo();
    vector<string> parseCSV(istream&, char);

    bool displayMenu();

private:
    map<int, Project*> projectList;
};

#endif    // __PROJECT_MANAGER_H__
