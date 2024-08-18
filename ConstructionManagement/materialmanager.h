#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <map>
#include <vector>
#include "material.h"
#include "manager.h"

using namespace std;

class MaterialManager : public Manager
{
public:
    MaterialManager();
    ~MaterialManager();

    void create();                   // 자재 생성
    void remove(int id);             // 자재 삭제
    Material* search(int id);        // 자재 검색
    void modify(int id);             // 자재 수정
    void displayInfo();              // 모든 자재 정보 출력

    void displayMenu();              // 메뉴 표시 및 사용자 입력 처리

private:
    map<int, Material*> materialList;  // 자재 목록을 저장하는 맵

    int makeId();                    // 새로운 고유 ID 생성
    vector<string> parseCSV(istream&, char);
};
#endif // MATERIALMANAGER_H
