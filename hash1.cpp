#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct HashNode {
    string key;
    string value;
    HashNode* next;
};

// Структура хеш-таблицы
struct HashTable {
    HashNode** table;
    size_t tableSize;

    HashTable(size_t size) : tableSize(size) {
        table = new HashNode * [tableSize];
        for (size_t i = 0; i < tableSize; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (size_t i = 0; i < tableSize; i++) {
            HashNode* node = table[i];
            while (node != nullptr) {
                HashNode* temp = node;
                node = node->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Хеш-функция
    size_t hashFunction(const string& key) const {
        size_t hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % tableSize;
        }
        return hash;
    }

    // Вставка элемента
    void add(const string& key, const string& value) {
        size_t hashIndex = hashFunction(key);
        HashNode* node = table[hashIndex];

        while (node != nullptr) {
            if (node->key == key) {
                node->value = value; // Обновляем значение, если ключ уже существует
                return;
            }
            node = node->next;
        }

        // Добавляем новый узел в начало списка
        HashNode* newNode = new HashNode{ key, value, table[hashIndex] };
        table[hashIndex] = newNode;
    }

    // Получение значения по ключу
    string get(const string& key) const {
        size_t hashIndex = hashFunction(key);
        HashNode* node = table[hashIndex];
        while (node != nullptr) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return ""; // Возвращаем пустую строку, если ключ не найден
    }

    // Удаление элемента
    void remove(const string& key) {
        size_t hashIndex = hashFunction(key);
        HashNode* node = table[hashIndex];
        HashNode* prev = nullptr;

        while (node != nullptr) {
            if (node->key == key) {
                if (prev == nullptr) {
                    table[hashIndex] = node->next; // Удаляем первый узел
                }
                else {
                    prev->next = node->next; // Удаляем узел из списка
                }
                delete node;
                return;
            }
            prev = node;
            node = node->next;
        }
        cout << "Элемент с ключом " << key << " не найден" << endl;
    }

    // Вывод всех элементов хеш-таблицы
    void read() const {
        bool hasData = false; // Флаг, чтобы проверить, есть ли данные для отображения

        for (size_t i = 0; i < tableSize; i++) {
            HashNode* node = table[i];
            while (node != nullptr) {
                cout << "Ключ–Значение: " << node->key << "–" << node->value << endl;
                node = node->next;
                hasData = true; // Устанавливаем флаг, если нашли хотя бы один элемент
            }
        }

        if (!hasData) {
            cout << "Нет данных" << endl; // Если данных нет, выводим сообщение
        }
    }

    // Запись хеш-таблицы в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для записи" << endl;
            return;
        }
        for (size_t i = 0; i < tableSize; i++) {
            HashNode* node = table[i];
            while (node != nullptr) {
                file << node->key << " " << node->value << endl;
                node = node->next;
            }
        }
        file.close();
    }

    // Чтение хеш-таблицы из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Не удалось открыть файл для чтения" << endl;
            return;
        }
        string key, value;
        while (file >> key >> value) {
            add(key, value); // Используем метод add
        }
        file.close();
    }
};

int main() {
    HashTable hashTable(10); // Создание хеш-таблицы
    setlocale(LC_ALL, "RU");

    string hashCommand;
    while (true) {
        cout << "Команды для хеш-таблицы (add, get, remove, read, save, load, exit): ";
        getline(cin, hashCommand);

        if (hashCommand == "add") {
            string key, value;
            cout << "Введите ключ: ";
            getline(cin, key);
            cout << "Введите значение: ";
            getline(cin, value);
            hashTable.add(key, value);
        }
        else if (hashCommand == "get") {
            string key;
            cout << "Введите ключ: ";
            getline(cin, key);
            string value = hashTable.get(key);
            if (value.empty()) {
                cout << "Нет данных для ключа: " << key << endl;
            }
            else {
                cout << "Значение: " << value << endl;
            }
        }
        else if (hashCommand == "remove") {
            string key;
            cout << "Введите ключ: ";
            getline(cin, key);
            hashTable.remove(key);
        }
        else if (hashCommand == "read") {
            hashTable.read();  // Вызов метода read для вывода всех данных
        }
        else if (hashCommand == "save") {
            string filename;
            cout << "Введите имя файла для сохранения: ";
            getline(cin, filename);
            hashTable.saveToFile(filename); // Сохранение в файл
        }
        else if (hashCommand == "load") {
            string filename;
            cout << "Введите имя файла для загрузки: ";
            getline(cin, filename);
            hashTable.loadFromFile(filename); // Загрузка из файла
        }
        else if (hashCommand == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда." << endl;
        }
    }

    return 0;
}
