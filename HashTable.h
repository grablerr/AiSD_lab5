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

		HashTable& operator=(const HashTable& other) {
			if (this != &other) {
				delete[] table;
				size = other.size;
				capacity = other.capacity;
				table = new Node[capacity];
				for (int i = 0; i < capacity; ++i) {
					table[i] = other.table[i];
				}
			}
			return *this;
		}

		void print() const;

		void insert(int key, const T& value);

		void insert_or_assign(int key, const T& value);

		bool contains(const T& value) const;

		T* search(int key);

		bool erase(int key);

		int count(int key) const;
	};

	template<typename T>
	inline int HashTable<T>::hash(int key) const {
		const double A = 0.6180339887;
		return static_cast<int>(capacity * (key * A - static_cast<int>(key * A)));
	}

	template<typename T>
	inline int HashTable<T>::findPos(int key) const {
		int hashValue = hash(key);
		int initialPos = hashValue % capacity;
		int pos = initialPos;

		do {
			if (table[pos].key == key && !table[pos].deleted) {
				return pos;
			}
			if (table[pos].deleted) {
				break;
			}
			pos = (pos + 1) % capacity;
		} while (pos != initialPos);

		return -1;
	}

	template<typename T>
	inline void HashTable<T>::resize(int newSize) {
		Node* newTable = new Node[newSize];
		for (int i = 0; i < capacity; ++i) {
			if (!table[i].deleted) {
				int newPos = hash(table[i].key) % newSize;
				while (!newTable[newPos].deleted) {
					newPos = (newPos + 1) % newSize;
				}
				newTable[newPos] = table[i];
			}
		}
		delete[] table;
		table = newTable;
		capacity = newSize;
	}

	template<typename T>
	inline HashTable<T>::HashTable(int initialSize): size(0), capacity(initialSize) {
		table = new Node[capacity];
	}

	template<typename T>
	inline HashTable<T>::HashTable(const HashTable& other) : size(other.size), capacity(other.capacity) {
		table = new Node[capacity];
		for (int i = 0; i < capacity; ++i) {
			table[i] = other.table[i];
		}
	}

	template<typename T>
	inline HashTable<T>::~HashTable() {
		delete[] table;
	}

	template<typename T>
	inline void HashTable<T>::print() const {
		for (int i = 0; i < capacity; ++i) {
			if (!table[i].deleted) {
				cout << "Key: " << table[i].key << ", Value: " << table[i].value << endl;
			}
		}
	}

	template<typename T>
	inline void HashTable<T>::insert(int key, const T& value) {
		if (size >= 0.7 * capacity) {
			resize(2 * capacity);
		}
		int pos = hash(key) % capacity;
		while (!table[pos].deleted && table[pos].key != key) {
			pos = (pos + 1) % capacity;
		}
		if (table[pos].deleted) {
			++size;
		}
		table[pos] = Node(key, value);
		table[pos].deleted = false;
	}

	template<typename T>
	inline void HashTable<T>::insert_or_assign(int key, const T& value) {
		if (size >= 0.7 * capacity) {
			resize(2 * capacity);
		}
		int pos = hash(key) % capacity;
		int initialPos = pos;
		do {
			if (table[pos].key == key && !table[pos].deleted) {
				table[pos].value = value;
				return;
			}
			pos = (pos + 1) % capacity;
		} while (pos != initialPos && !table[pos].deleted);

		if (table[pos].deleted) {
			++size;
		}
		table[pos] = Node(key, value);
		table[pos].deleted = false;
	}

	template<typename T>
	inline bool HashTable<T>::contains(const T& value) const {
		for (int i = 0; i < capacity; ++i) {
			if (!table[i].deleted && table[i].value == value) {
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline T* HashTable<T>::search(int key) {
		int pos = findPos(key);
		if (pos != -1) {
			return &(table[pos].value);
		}
		return nullptr;
	}

	template<typename T>
	inline bool HashTable<T>::erase(int key) {
		int pos = findPos(key);
		if (pos != -1) {
			table[pos].deleted = true;
			--size;
			return true;
		}
		return false;
	}

	template<typename T>
	inline int HashTable<T>::count(int key) const {
		int cnt = 0;
		int pos = hash(key) % capacity;
		while (!table[pos].deleted && (table[pos].key != key || table[pos].deleted)) {
			if (table[pos].key == key) {
				++cnt;
			}
			pos = (pos + 1) % capacity;
		}
		return cnt;
	}
}
