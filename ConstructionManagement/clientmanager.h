#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include <map>
#include <vector>
#include "client.h"
#include "manager.h"
#include "projectmanager.h"

using namespace std;

class ClientManager : public Manager
{
public:
    ClientManager();
    ~ClientManager();

    void create();
    void remove(int);
    void modify(int);
    Client* search(int);
    int makeId();
    void displayInfo();
    void displayInfo(int);

    vector<string> parseCSV(istream&, char);

    virtual void displayMenu();
    //bool displayMenu();

    virtual void showAllDatas();

private:
    map<int, Client*> clientList;
};

#endif    // __CLIENT_MANAGER_H__
