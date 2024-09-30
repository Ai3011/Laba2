#include <iostream>
#include <string>

using namespace std;

// Структура для элемента хеш-таблицы (ключ-значение)
struct HashNode {
    string key;       // Ключ
    string value;     // Значение
    HashNode* next;   // Указатель на следующий элемент (для разрешения коллизий)
};

// Структура для динамического массива (аналог вектора)
struct Array {
    HashNode** data;  // Массив указателей на HashNode
    size_t capacity;  // Текущая вместимость массива
    size_t size;      // Текущий размер массива

    // Инициализация массива с заданной вместимостью
    void init(size_t initialCapacity) {
        capacity = initialCapacity;
        size = 0;
        data = new HashNode*[capacity];  // Выделение памяти под массив указателей
        for (size_t i = 0; i < capacity; ++i) {
            data[i] = nullptr;  // Инициализация всех элементов как nullptr
        }
    }

    // Увеличение размера массива (реализация динамического массива)
    void resize(size_t newCapacity) {
        HashNode** newData = new HashNode*[newCapacity];
        for (size_t i = 0; i < newCapacity; ++i) {
            if (i < capacity) {
                newData[i] = data[i];  // Копируем старые данные
            } else {
                newData[i] = nullptr;  // Остальные элементы инициализируем как nullptr
            }
        }
        delete[] data;  // Удаляем старый массив
        data = newData;
        capacity = newCapacity;
    }

    // Очищение массива (удаление всех элементов)
    void clear() {
        for (size_t i = 0; i < capacity; ++i) {
            delete data[i];  // Очищаем память под каждый элемент
        }
        delete[] data;  // Удаляем сам массив
        data = nullptr;
        size = 0;
    }
};

// Хеш-таблица
struct HashTable {
    Array table;     // Динамический массив для хранения цепочек
    size_t tableSize; // Размер таблицы

    // Инициализация таблицы
    void init(size_t size) {
        tableSize = size;
        table.init(size);  // Инициализируем массив для хранения указателей
    }
};

// Простая хеш-функция на основе суммы ASCII-кодов символов
size_t hashFunction(const string& key, size_t tableSize) {
    size_t hash = 0;
    for (size_t i = 0; i < key.length(); ++i) {
        hash += key[i];  // Суммируем ASCII коды символов
    }
    return hash % tableSize;
}

// Функция для создания нового узла
HashNode* createNode(const string& key, const string& value) {
    HashNode* newNode = new HashNode;
    newNode->key = key;
    newNode->value = value;
    newNode->next = nullptr;
    return newNode;
}

// Функция для добавления элемента (ключ-значение)
void insert(HashTable& hashTable, const string& key, const string& value) {
    size_t hashIndex = hashFunction(key, hashTable.tableSize);  // Вычисляем хеш

    // Проверяем, есть ли уже элемент с таким ключом
    HashNode* node = hashTable.table.data[hashIndex];
    while (node != nullptr) {
        if (node->key == key) {
            node->value = value;  // Если ключ уже существует, обновляем значение
            return;
        }
        node = node->next;
    }

    // Ключ не найден, создаем новый элемент
    HashNode* newNode = createNode(key, value);
    newNode->next = hashTable.table.data[hashIndex];  // Добавляем новый элемент в начало списка
    hashTable.table.data[hashIndex] = newNode;
}

string get(const HashTable& hashTable, const string& key) {
    size_t hashIndex = hashFunction(key, hashTable.tableSize);  // Вычисляем хеш

    HashNode* node = hashTable.table.data[hashIndex];  // Ищем элемент по индексу хеша
    while (node != nullptr) {
        if (node->key == key) {
            return node->value;  // Возвращаем значение, если ключ найден
        }
        node = node->next;
    }

    return "Нет данных";  // Если ключ не найден, возвращаем сообщение "Нет данных"
}


// Функция для удаления элемента по ключу
void remove(HashTable& hashTable, const string& key) {
    size_t hashIndex = hashFunction(key, hashTable.tableSize);  // Вычисляем хеш

    HashNode* node = hashTable.table.data[hashIndex];
    HashNode* prev = nullptr;

    // Ищем элемент с заданным ключом
    while (node != nullptr && node->key != key) {
        prev = node;
        node = node->next;
    }

    // Если элемент не найден, ничего не делаем
    if (node == nullptr) {
        return;
    }

    // Если элемент найден, удаляем его
    if (prev == nullptr) {
        // Удаляем первый элемент в списке
        hashTable.table.data[hashIndex] = node->next;
    } else {
        // Удаляем элемент из середины или конца списка
        prev->next = node->next;
    }

    delete node;  // Очищаем память
}

// Функция для очистки хеш-таблицы
void clear(HashTable& hashTable) {
    for (size_t i = 0; i < hashTable.table.capacity; ++i) {
        HashNode* node = hashTable.table.data[i];
        while (node != nullptr) {
            HashNode* temp = node;
            node = node->next;
            delete temp;
        }
        hashTable.table.data[i] = nullptr;
    }
    hashTable.table.clear();
}

// Тестовая программа
int main() {
    HashTable hashTable;
    hashTable.init(10);  // Инициализируем хеш-таблицу с 10 ячейками

    insert(hashTable, "apple", "green");
    insert(hashTable, "banana", "yellow");
    insert(hashTable, "cherry", "red");

    cout << "Цвет apple: " << get(hashTable, "apple") << endl;
    cout << "Цвет banana: " << get(hashTable, "banana") << endl;
    cout << "Цвет cherry: " << get(hashTable, "cherry") << endl;

    remove(hashTable, "banana");
    cout << "Цвет banana после удаления: " << get(hashTable, "banana") << endl;

    clear(hashTable);  // Очистка хеш-таблицы

    return 0;
}
