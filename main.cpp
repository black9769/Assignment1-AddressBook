#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

//주소 정보를 담을 구조체 생성
struct AddressInfo {
    string name;
    string phoneNumber;
    string mainAddress;
    string subAddress;
};

//문자열을 주소 구조체로 변환
AddressInfo strToStruct(string addressStr);

//문자열로 구분자 나누기
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

class Node {
public:
    AddressInfo addressInfo;
    Node *next;

    Node(AddressInfo addressInfo) : addressInfo(addressInfo), next(nullptr) {}
};


class LinkedList {
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    void append(AddressInfo addressInfo) {
        Node *newNode = new Node(addressInfo);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp =head;
            while (temp-> next != nullptr){
                temp =temp->next;
            }
            temp -> next = newNode;
        }
    }
};

int main() {
    LinkedList AddressList;
    ifstream addressTextBook("AddressBook.txt");
    if (addressTextBook.is_open()) {
        string line;
        while (getline(addressTextBook, line)) {
            AddressInfo addressInfo = strToStruct(line);
            AddressList.append(addressInfo);
        }
    }
    return 0;
}

AddressInfo strToStruct(string addressStr) {
    vector<string> result = split(addressStr, ',');
    AddressInfo addressInfo;

    if (result.size() >= 4) {
        addressInfo.name = result[0];
        addressInfo.phoneNumber = result[1];
        addressInfo.mainAddress = result[3];
        addressInfo.subAddress = result[2];
    }

    return addressInfo;
}

