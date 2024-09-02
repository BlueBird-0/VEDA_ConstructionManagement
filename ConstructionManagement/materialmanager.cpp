#include "materialmanager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

MaterialManager::MaterialManager() {
    ifstream file("materiallist.txt");  // "materiallist.txt" 파일을 읽기 위해 연다.
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');  // CSV 형식으로 데이터를 읽어온다.
            if (row.size() > 0) {
                int id = stoi(row[0]);  // 첫 번째 열을 정수형 ID로 변환
                int unitPrice = stoi(row[3]);  // 네 번째 열을 실수형 단가로 변환
                int stock = stoi(row[4]);  // 다섯 번째 열을 정수형 재고량으로 변환
                int orderQuantity = stoi(row[5]);  // 여섯 번째 열을 정수형 주문량으로 변환
                Material* m = new Material(id, row[1], row[2], unitPrice, stock, orderQuantity);  // 자재 객체 생성
                materialList[id] = m;  // ID를 키로 하여 materialList에 자재를 저장
            }
        }
    }
    file.close();  // 파일 닫기
}

MaterialManager::~MaterialManager() {
    ofstream file("materiallist.txt");  // "materiallist.txt" 파일을 쓰기 위해 연다.
    if (!file.fail()) {
        for (const auto& pair : materialList) {
            Material* m = pair.second;
            file << m->getId() << "," << m->getName() << "," << m->getSupplier() << ","
                 << m->getUnitPrice() << "," << m->getStock() << "," << m->getOrderQuantity() << endl;
        }
    }
    file.close();  // 파일 닫기

    for (auto& pair : materialList) {
        delete pair.second;  // 동적으로 할당된 자재 객체 삭제
    }
}

void MaterialManager::create() {
    string name, supplier;
    int stock, orderQuantity, unitPrice;
    setCmdColor(0);
    printf("%2s)  %10s | %16s | %12s | %10s | %10s\n", "예","자재명", "공급업체", "단가(₩)", "재고량(EA)", "주문량(EA)");
    printf("%2s | %10s | %16s | %12s | %10s | %10s\n", "","시멘트", "ABC 건축자재", "50000", "200", "500");
    printf("\n");
    setCmdColor();
    cout << "자재명: ";
    cin >> name;
    cout << "공급업체: ";
    cin >> supplier;
    cout << "단가: ";
    cin >> unitPrice;
    cout << "재고량: ";
    cin >> stock;
    cout << "주문량: ";
    cin >> orderQuantity;

    int id = makeId();  // 새로운 자재 ID 생성
    Material* material = new Material(id, name, supplier, unitPrice, stock, orderQuantity);
    materialList[id] = material;  // 자재 리스트에 추가

    cout << "자재가 성공적으로 추가되었습니다!" << endl;
}

void MaterialManager::remove(int id) {
    auto it = materialList.find(id);
    if (it != materialList.end()) {
        delete it->second;  // 동적으로 할당된 자재 객체 삭제
        materialList.erase(it);  // 자재 리스트에서 삭제
        cout << "자재가 성공적으로 삭제되었습니다!" << endl;
    } else {
        cout << "자재ID " << id << "을(를) 찾을 수 없습니다..." << endl;
    }
}

Material* MaterialManager::search(int id) {
    auto it = materialList.find(id);
    if (it != materialList.end()) {
        return it->second;  // 자재 찾기 성공
    } else {
        cout << "자재ID " << id << "을(를) 찾을 수 없습니다..." << endl;
        return nullptr;  // 자재 찾기 실패
    }
}

void MaterialManager::modify(int id) {
    Material* material = search(id);
    if (material) {
        string name, supplier;
        int stock, orderQuantity, unitPrice;

        cout << "현재 자재명: " << material->getName() << endl;
        cout << "현재 공급업체: " << material->getSupplier() << endl;
        cout << "현재 단가: " << material->getUnitPrice() << endl;
        cout << "현재 재고량: " << material->getStock() << endl;
        cout << "현재 주문량: " << material->getOrderQuantity() << endl;

        cout << "새로운 자재명을 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
        cin.ignore();
        getline(cin, name);
        if (!name.empty()) material->setName(name);

        cout << "새로운 공급업체를 입력해주세요. (아니면 Enter키를 눌러 현재 상태 유지): ";
        getline(cin, supplier);
        if (!supplier.empty()) material->setSupplier(supplier);

        cout << "새로운 단가를 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
        cin >> unitPrice;
        if (unitPrice >= 0) material->setUnitPrice(unitPrice);

        cout << "새로운 재고량을 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
        cin >> stock;
        if (stock >= 0) material->setStock(stock);

        cout << "새로운 주문량을 입력해주세요. (아니면 -1를 입력하여 현재 상태 유지): ";
        cin >> orderQuantity;
        if (orderQuantity >= 0) material->setOrderQuantity(orderQuantity);

        cout << "성공적으로 수정되었습니다!" << endl;
    }
}

void MaterialManager::displayInfo() {
    setCmdColor(1);
	if (!materialList.empty()) {
		printf("%6s | %10s | %16s | %12s | %10s | %10s\n", "자재ID", "자재명", "공급업체", "단가(₩)", "재고량(EA)", "주문량(EA)");

		for (const auto& pair : materialList) {
			Material* m = pair.second;
			cout << setw(6) << m->getId() << " | ";  // 자재 ID 출력
			cout << setw(10) << m->getName() << " | ";  // 자재명 출력
			cout << setw(10) << m->getSupplier() << " | ";  // 공급업체명 출력
			cout << setw(12) << fixed << m->getUnitPrice() << " | ";  // 단가 출력
			cout << setw(6) << m->getStock() << " | ";  // 재고량 출력
			cout << setw(6) << m->getOrderQuantity() << endl;  // 주문량 출력
		}
	}
	else {
		setCmdColor(2);
		cout << "등록된 자재가 없습니다." << endl;
	}
    setCmdColor();

}

void MaterialManager::displayMenu() {
    int id;
    bool running = true;
    string choice;

    while (running) {
        cout << "\033[2J\033[1;1H";  // 화면을 지우고 커서를 맨 위로 이동
        cout << "\033[30;94m┌───────────────────────────────────────────┐ \033[0m" << endl;
        cout << "\033[30;94m│                 \033[30;93m자재관리\033[0m                  \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│───────────────────────────────────────────│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m1. 자재 전체조회\033[0m                         \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m2. 자재 등록\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m3. 자재 삭제\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;97m4. 자재 수정\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m│  \033[30;91mexit. 나가기\033[0m                             \033[30;94m│ \033[0m" << endl;
        cout << "\033[30;94m└───────────────────────────────────────────┘ \033[0m" << endl;
        cout << "어떤 항목을 선택하시겠습니까? ";
        cin >> choice;

        if (choice == "1") {
            displayInfo();  // 자재 정보를 출력
        }
        else if (choice == "2") {
            create();  // 자재를 생성하여 리스트에 추가
        }
        else if (choice == "3") {
            cout << "삭제할 자재ID를 입력해주세요: ";
            cin >> id;
            remove(id);  // 자재를 삭제
        }
        else if (choice == "4") {
            cout << "수정할 자재ID를 입력해주세요: ";
            cin >> id;
            modify(id);  // 자재를 수정
        }
        else if (choice == "5" || choice =="exit" ) {
            running = false;  // 프로그램 종료
        }
        else {
            setCmdColor(2);
            cout << "잘못된 선택입니다. 다시 입력해주세요." << endl;
            setCmdColor();
        }

        if (running) {
            cout << "\n계속하려면 Enter 키를 눌러주세요...";
            cin.ignore();
            cin.get();  // Enter 입력을 기다림
        }
    }
}

int MaterialManager::makeId() {
    int maxId = 0;
    for (const auto& pair : materialList) {
        if (pair.first > maxId) {
            maxId = pair.first;
        }
    }
    return maxId + 1;  // 새로운 ID 생성
}

vector<string> MaterialManager::parseCSV(istream& str, char delimiter) {
    vector<string> result;
    string line;
    if (getline(str, line)) {
        stringstream ss(line);
        string item;
        while (getline(ss, item, delimiter)) {
            result.push_back(item);
        }
    }
    return result;  // CSV 파싱 결과 반환
}

void MaterialManager::showAllDatas(){

}
