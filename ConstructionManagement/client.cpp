#include "client.h"

#include <iostream>
#include <iomanip>

using namespace std;

Client::Client(int clientId, string clientName, string phoneNum, string address)
    : m_clientId(clientId), m_clientName(clientName), m_phoneNum(phoneNum), m_address(address)
{
}

string Client::getClientName() const
{
    return m_clientName;
}

void Client::setClientName(string& clientName)
{
    m_clientName = clientName;
}

string Client::getPhoneNum() const
{
    return m_phoneNum;
}

void Client::setPhoneNum(string& phoneNum)
{
    m_phoneNum = phoneNum;
}

string Client::getAddress() const
{
    return m_address;
}

void Client::setAddress(string& address)
{
    m_address = address;
}


int Client::id() const
{
    return m_clientId;
}

void Client::showInfo() {
    cout << setw(5) << setfill('0') << right << id() << " | " << left;
    cout << setw(12) << setfill(' ') << getClientName() << " | ";
    cout << setw(12) << getPhoneNum() << " | ";
    cout << getAddress() << endl;
}
