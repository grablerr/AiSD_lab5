#include <iostream>
#include <cstdlib>

using namespace std;

namespace HT {
    template<typename T>
    class HashTable {
    private:
        struct Node {
            int key;
            T value;
            bool deleted;

            Node() : key(0), deleted(true) {}
            Node(int k, const T& v) : key(k), value(v), deleted(false) {}
        };

        Node* table;
        int size;
        int capacity;

        int hash(int key) const;

        int findPos(int key) const;

        void resize(int newSize);

    public:
        HashTable(int initialSize = 10);

        HashTable(const HashTable& other);

        ~HashTable();

        HashTable& operator=(const HashTable& other);

        void print() const;

        void insert(int key, const T& value);

        void insert_or_assign(int key, const T& value);

        bool contains(const T& value) const;

        T* search(int key);

        bool erase(int key);

        int count(int key) const;
    };
}
