#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__

#include <map>
#include <vector>
#include "client.h"

using namespace std;

class ClientManager {
public:
    ClientManager();
    ~ClientManager();

    void create();
    void remove(int);
    void modify(int);
    Client* search(int);
    int makeId();
    void displayInfo(int key = 0);
    vector<string> parseCSV(istream&, char);

    bool displayMenu();

private:
    map<int, Client*> clientList;
};

#endif    // __CLIENT_MANAGER_H__
