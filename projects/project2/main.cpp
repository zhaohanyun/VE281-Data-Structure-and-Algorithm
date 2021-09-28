#include "hashtable.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    HashTable<int, int> test;
    while(1) {
        string command;
        cin >> command;
        if (command == "EXIT") break;
        if (command == "INSERT") {
            int op1, op2;
            cin >> op1 >> op2;
            test.insert(op1, op2);
        }
        if (command == "ACCESS") {
            int op1, op2;
            cin >> op1 >> op2;
            test[op1] = op2;
        }
        if (command == "ERASE") {
            int op;
            cin >> op;
            test.erase(op);
        }
    }
}