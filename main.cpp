#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

// 주소 정보를 저장할 구조체
struct AddressInfo {
    string name;
    string address;
    string phoneNumber;
    string email;

    AddressInfo(string n, string a, string p, string e) : name(n), address(a), phoneNumber(p), email(e) {}
};

// 연결 리스트의 노드
class Node {
public:
    AddressInfo info;
    Node *next;

    Node(AddressInfo info) : info(info), next(nullptr) {}
};

// 주소록을 관리하는 클래스
class AddressBook {
private:
    Node *head;

    // 주어진 이름을 가진 노드를 찾는 함수
    Node *findNode(string name) {
        Node *current = head;
        while (current != nullptr) {
            if (current->info.name == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    AddressBook() : head(nullptr) {}


    // 주소록에 주소 정보 추가
    void addAddress(AddressInfo info) {
        Node *newNode = new Node(info);
        newNode->next = head;
        head = newNode;
    }

    // 주소록에서 주소 정보 삭제
    bool removeAddress(string name) {
        Node *current = head;
        Node *prev = nullptr;

        while (current != nullptr) {
            if (current->info.name == name) {
                if (prev == nullptr) {
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // 주소 정보 검색
    bool searchAddress(string name) {
        Node *node = findNode(name);
        if (node != nullptr) {
            cout << "이름: " << node->info.name << endl;
            cout << "주소: " << node->info.address << endl;
            cout << "휴대폰 번호: " << node->info.phoneNumber << endl;
            cout << "Email: " << node->info.email << endl;
            return true;
        } else {
            cout << "찾을 수 없음." << endl;
            return false;
        }
    }

    // 파일에서 주소록 데이터 불러오기
    void loadFromFile(string filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, address, phone, email;

            getline(ss, name, ',');
            getline(ss, address, ',');
            getline(ss, phone, ',');
            getline(ss, email);

            addAddress(AddressInfo(name, address, phone, email));
        }
    }

    void printAllAddresses() {
        Node *current = head;
        while (current != nullptr) {
            cout << "이름: " << current->info.name << endl;
            cout << "주소: " << current->info.address << endl;
            cout << "휴대폰번호: " << current->info.phoneNumber << endl;
            cout << "Email: " << current->info.email << endl;
            cout << "----------------------------------" << endl;
            current = current->next;
        }
    }

    //이름순 정렬
    void sortByName() {
        if (head == nullptr || head->next == nullptr) {
            return; // 리스트가 비어 있거나 하나의 노드만 있는 경우 정렬할 필요 없음
        }

        bool swapped;
        do {
            swapped = false;
            Node *current = head;
            while (current->next != nullptr) {
                if (current->info.name > current->next->info.name) {
                    swap(current->info, current->next->info);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
    void sortByNumber() {
        if (head == nullptr || head->next == nullptr) {
            return; // 리스트가 비어 있거나 하나의 노드만 있는 경우 정렬할 필요 없음
        }

        bool swapped;
        do {
            swapped = false;
            Node *current = head;
            while (current->next != nullptr) {
                if (current->info.phoneNumber > current->next->info.phoneNumber) {
                    swap(current->info, current->next->info);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        Node* current = head;
        while (current != nullptr) {
            file << current->info.name << ","
                 << current->info.address << ","
                 << current->info.phoneNumber << ","
                 << current->info.email << endl;
            current = current->next;
        }
    }

    // 소멸자: 모든 노드 메모리 해제
    ~AddressBook() {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }
};

// 주소록 서비스 실행 함수
void runAddressBookService() {
    AddressBook myBook;

    string filename = "AddressBook.txt";
    myBook.loadFromFile(filename);

    int choice;
    string name, address, phoneNumber, email;

    while (true) {
        cout << "1. 주소록 검색\n2. 주소록 추가\n3. 삭제\n4. 이름순 정렬\n5. 번호순 정렬\n9. 전체보기\n0. 종료\n선택: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cin과 getline 사이의 버퍼 비우기

        switch (choice) {
            case 1:
                cout << "이름: ";
                getline(cin, name);
                if (!myBook.searchAddress(name)) {
                    cout << "주소록에 없습니다." << endl;
                }
                break;
            case 2:
                cout << "이름: ";
                getline(cin, name);
                cout << "주소: ";
                getline(cin, address);
                cout << "휴대폰 번호: ";
                getline(cin, phoneNumber);
                cout << "Enter email: ";
                getline(cin, email);
                myBook.addAddress(AddressInfo(name, address, phoneNumber, email));
                break;
            case 3:
                cout << "이름: ";
                getline(cin, name);
                if (myBook.removeAddress(name)) {
                    cout << "삭제완료." << endl;
                } else {
                    cout << "찾을 수 없음." << endl;
                }
                break;
            case 4: // 이름순 정렬
                myBook.sortByName();
                myBook.printAllAddresses();
                break;
            case 5: // 이름순 정렬
                myBook.sortByNumber();
                myBook.printAllAddresses();
                break;
            case 0:
                myBook.saveToFile("AddressBook.txt");
                cout << "저장을 완료했습니다. " << filename << endl;
                return;
            default:
                cout << "유효하지 않습니다." << endl;
                break;
        }
    }
}


int main() {
    runAddressBookService();
    return 0;
}
