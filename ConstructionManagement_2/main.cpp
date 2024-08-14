#include <iostream>
#include "materialmanager.h"
#include "material.h"
#include "expensemanager.h"
#include <vector>

using namespace std;

int main()
{
    //ExpenseManager manager;
    MaterialManager manager;  // MaterialManager 객체 생성

        // 프로그램 메뉴 실행
    manager.displayMenu();

    return 0;

}

