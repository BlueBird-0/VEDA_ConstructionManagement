#ifndef __MATERIAL_MANAGER_H__  // 헤더 가드 정의
#define __MATERIAL_MANAGER_H__

#include <map>  // 맵 라이브러리 포함
#include <vector>  // 벡터 라이브러리 포함
#include "material.h"  // Material 클래스 헤더 파일 포함

using namespace std;  // 표준 네임스페이스 사용

// MaterialManager 클래스 선언
class MaterialManager {
public:
    MaterialManager();  // 생성자
    ~MaterialManager();  // 소멸자

    // 멤버 함수 선언
    void create();                   // 자재 생성
    void remove(int id);             // 자재 삭제
    Material* search(int id);        // 자재 검색
    void modify(int id);             // 자재 수정
    void displayInfo();              // 모든 자재 정보 출력

    bool displayMenu();

private:
    map<int, Material*> materialList;  // 자재 포인터를 저장하는 맵

    int makeId();                    // 새로운 고유 ID 생성
    vector<string> parseCSV(istream&, char);
};

#endif    // __MATERIAL_MANAGER_H__
