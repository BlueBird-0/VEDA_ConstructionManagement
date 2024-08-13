#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <vector>
#include "expense.h"

using namespace std;

class ExpenseManager {
public:
    ExpenseManager();
    ~ExpenseManager();

    void create();                   // 비용 생성
    void modify(int projectID, int materialID); // 비용 수정
    vector<int> searchByProjectID(int projectID);   // 프로젝트 ID로 검색
    vector<int> searchByMaterialID(int materialID); // 자재 ID로 검색
    void displayInfo();              // 모든 비용 정보 출력
    void displayMenu();              // 메뉴 표시 및 사용자 입력 처리

private:
    vector<Expense> m_expenses;      // 비용 목록

    vector<string> parseCSV(istream&, char);
};

#endif // EXPENSEMANAGER_H
