#ifndef EXPENSEMANAGER_H
#define EXPENSEMANAGER_H

#include <vector>
#include <string>
#include "expense.h"
#include "manager.h"
#include <map>

using namespace std;

class ExpenseManager : public Manager
{
private:
    vector<Expense> m_expenses;

public:
    ExpenseManager();
    ~ExpenseManager();

    void create();  // 새로운 비용 항목 생성
    void modify(int projectID, int materialID);  // 비용 항목 수정
    void remove(int projectID, int materialID);  // 비용 항목 삭제

    vector<int> searchByProjectID(int projectID);  // 프로젝트 ID로 검색
    vector<int> searchByMaterialID(int materialID);  // 자재 ID로 검색

    void displayInfo();  // 모든 비용 정보 표시
    void displayMenu();  // 메뉴 표시 및 사용자 인터페이스 제공

private:
    vector<string> parseCSV(istream& str, char delimiter);  // CSV 파일 파싱
};

#endif // EXPENSEMANAGER_H
