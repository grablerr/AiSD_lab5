#include "HashTable.h"
#include <string>

using namespace HT;
using namespace std;

void tests() {
    HashTable<int> ht(5);

    ht.insert(1, 100);
    ht.insert(6, 200);
    ht.insert(11, 300);
    ht.insert(16, 400);

    cout << "After handling collisions:" << endl;
    ht.print();

    ht.insert(21, 500);
    ht.insert(26, 600);
    ht.insert(31, 700);
    ht.insert(36, 800);
    ht.insert(41, 900);

    cout << "\nAfter reaching 70% load factor:" << endl;
    
    ht.print();
}

unsigned int pearson_hash(const string& str) {
    static const unsigned char table[256] = {};

    unsigned int hash = 0;
    for (char ch : str) {
        hash = table[hash ^ ch];
    }
    return hash;
}

template<typename T>
bool compare_hashes(const HashTable<T>& hashTable, const string& str) {
    unsigned int inputHash = pearson_hash(str);
    const string* savedValue = const_cast<HashTable<T>&>(hashTable).search(inputHash);

    if (savedValue && *savedValue == str) {
        return true;
    }
    return false;
}

int main() {

    HashTable<string> hashTable;

    string userInput;
    cout << "Enter a string to hash: ";
    getline(cin, userInput);

    unsigned int hashValue = pearson_hash(userInput);
    hashTable.insert(hashValue, userInput);

    string anotherString;
    cout << "Enter another string to compare: ";
    getline(cin, anotherString);

    bool isEqual = compare_hashes(hashTable, anotherString);

    if (isEqual) {
        cout << "The hashes are equal." << endl;
    }
    else {
        cout << "The hashes are not equal." << endl;
    }

    return 0;
}
