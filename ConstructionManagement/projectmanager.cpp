#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "project.h"
#include "projectmanager.h"

ProjectManager::ProjectManager()
{
    ifstream file;
    file.open("projectlist.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = atoi(row[0].c_str());
                Project* p = new Project(id, row[1], row[2], row[3], row[4], stoi(row[5]));
                projectList.insert({ id, p });
            }
        }
    }
    file.close();
}

ProjectManager::~ProjectManager()
{
    ofstream file;
    file.open("projectlist.txt");
    if (!file.fail()) {
        for (const auto& v : projectList) {
            Project* p = v.second;
            file << p->id() << ", " << p->getProjectName() << ", ";
            file << p->getLocation() << ", " << p->getStartDate() << ", ";;
            file << p->getEndDate() << ", " << p->getBudget() << endl;
        }
    }
    file.close();
}

void ProjectManager::create()
{
    string name, location, startDate, endDate;
    string budgetStr;
    cout << "name : "; cin >> name;
    cout << "location : "; cin >> location;
    cout << "startDate : "; cin >> startDate;
    cout << "endDate : "; cin >> endDate;
    cout << "budget : "; cin.ignore(); std::getline(cin, budgetStr, '\n'); //cin >> address;
    int budget = stoi(budgetStr);

    int id = makeId();
    Project* p = new Project(id, name, location, startDate, endDate, budget);
    projectList.insert({ id, p });
}

Project* ProjectManager::search(int id)
{
    return projectList[id];
}

void ProjectManager::remove(int id)
{
    projectList.erase(id);
}

void ProjectManager::modify(int id)
{
    Project* p = search(id);
    cout << "  ID  |     Name     | Location | Start Date | End Date | Budget " << endl;
    cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProjectName() << " | ";
    cout << setw(12) << p->getLocation() << " | ";
    cout << setw(12) << p->getStartDate() << " | ";
    cout << setw(12) << p->getEndDate() << " | ";
    cout << p->getBudget() << endl;

    string name, location, startDate, endDate;
    string budgetStr;


    cout << "name : "; cin >> name;
    cout << "location : "; cin >> location;
    cout << "startDate : "; cin >> startDate;
    cout << "endDate : "; cin >> endDate;
    cout << "budget : "; cin.ignore(); getline(cin, budgetStr, '\n'); //cin >> address;
    int budget = stoi(budgetStr);

    p->setProjectName(name);
    p->setLocation(location);
    p->setStartDate(startDate);
    p->setEndDate(endDate);
    p->setBudget(budget);
    projectList[id] = p;
}

void ProjectManager::displayInfo()
{
    cout << endl << "  ID  |     Name     | Location | Start Date | End Date | Budget " << endl;
    for (const auto& v : projectList) {
        int id = v.first;
        Project* p = search(id);
        cout << setw(5) << setfill('0') << right << p->id() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getProjectName() << " | ";
        cout << setw(12) << p->getLocation() << " | ";
        cout << setw(12) << p->getStartDate() << " | ";
        cout << setw(12) << p->getEndDate() << " | ";
        cout << p->getBudget() << endl;
    }
}

int ProjectManager::makeId()
{
    if (projectList.size() == 0) {
        return 0;
    }
    else {
        auto elem = projectList.end();
        int id = (--elem)->first;
        return ++id;
    }
}

vector<string> ProjectManager::parseCSV(istream& file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}


bool ProjectManager::displayMenu()
{
    int ch, key;
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Project Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Project List                     " << endl;
    cout << "  2. Create Project                            " << endl;
    cout << "  3. Remove Project                           " << endl;
    cout << "  4. Modify Project                           " << endl;
    cout << "  5. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
    cin >> ch;
    switch (ch) {
    case 1: default:
        displayInfo();
        cin.ignore();
        getchar();
        break;
    case 2:
        create();
        break;
    case 3:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        remove(key);
        break;
    case 4:
        displayInfo();
        cout << "   Choose Key : ";
        cin >> key;
        modify(key);
        break;
    case 5:
        return false;
    }
    return true;
}
