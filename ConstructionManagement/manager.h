#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>

using namespace std;
class Manager
{
private:
    string errorMessage;
public:
    Manager();
    //매니저의 모든 데이터를 cout으로 보여주는 함수를 구현합니다.
    virtual void showAllDatas() = 0;
    //매니저가 최초에 실행되는 함수를 구현합니다.
    virtual void run() = 0;
};

#endif // MANAGER_H
