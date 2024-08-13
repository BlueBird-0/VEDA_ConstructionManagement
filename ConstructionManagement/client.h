#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>

using namespace std;

class Client {
public:
    Client(int m_clientId = 0, string m_clientName = "", string m_phoneNum = "", string m_address = "");

    string getClientName() const;
    void setClientName(string&);
    string getPhoneNum() const;
    void setPhoneNum(string&);
    string getAddress() const;
    void setAddress(string&);
 
    int id() const;


private:
    int m_clientId;
    string m_clientName;
    string m_phoneNum;
    string m_address;


};
#endif          // __CLIENT_H__

