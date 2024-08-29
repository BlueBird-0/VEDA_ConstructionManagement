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
//printf("%5s | %10s | %14s | %10s\n", "고객ID", "고객명", "전화번호", "주소");

void Client::showInfo() {
    cout << setw(6) << setfill(' ') << right << id() << " | ";
    cout << setw(10) << setfill(' ') << right << getClientName() << " | ";
    cout << setw(14) << getPhoneNum() << right << " | ";
    cout << setw(10) << getAddress() << right << endl;
}
