#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Массив строк
struct StringArray {
    string* data;
    size_t size;
    size_t capacity;

    StringArray(size_t initialCapacity = 10) : size(0), capacity(initialCapacity) {
        data = new string[capacity];
    }

    ~StringArray() {
        delete[] data;
    }

    void add(const string& element) {
        if (size >= capacity) resize();
        data[size++] = element;
    }

    void insert(size_t index, const string& element) {
        if (index > size) throw out_of_range("Index out of range");
        if (size >= capacity) resize();
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = element;
        ++size;
    }

    string get(size_t index) const {
        if (index >= size) throw out_of_range("Index out of range");
        return data[index];
    }

    void remove(size_t index) {
        if (index >= size) throw out_of_range("Index out of range");
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    void replace(size_t index, const string& element) {
        if (index >= size) throw out_of_range("Index out of range");
        data[index] = element;
    }

    size_t length() const {
        return size;
    }

    void read() const {
        for (size_t i = 0; i < size; ++i) {
            cout << i << ": " << data[i] << endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        string line;
        while (getline(file, line)) add(line);
        file.close();
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        for (size_t i = 0; i < size; ++i) {
            file << data[i] << endl;
        }
        file.close();
    }

private:
    void resize() {
        capacity *= 2;
        string* newData = new string[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }
};

// Узел для односвязного списка
struct Node {
    string data;
    Node* next;
    Node(const string& data) : data(data), next(nullptr) {}
};

// Односвязный список
struct LinkedList {
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addHead(const string& element) {
        Node* newNode = new Node(element);
        newNode->next = head;
        head = newNode;
        if (!tail) tail = head;
    }

    void addTail(const string& element) {
        Node* newNode = new Node(element);
        if (tail) {
            tail->next = newNode;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }

    void removeHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
    }

    void removeTail() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }

    void read() const {
        Node* current = head;
        size_t index = 0;
        while (current) {
            cout << index++ << ": " << current->data << endl;
            current = current->next;
        }
    }
};

// Узел для двусвязного списка
struct DoubleNode {
    string data;
    DoubleNode* next;
    DoubleNode* prev;
    DoubleNode(const string& data) : data(data), next(nullptr), prev(nullptr) {}
};

// Двусвязный список
struct DoublyLinkedList {
    DoubleNode* head;
    DoubleNode* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            DoubleNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addHead(const string& element) {
        DoubleNode* newNode = new DoubleNode(element);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
    }

    void addTail(const string& element) {
        DoubleNode* newNode = new DoubleNode(element);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else {
            head = newNode;
        }
        tail = newNode;
    }

    void removeHead() {
        if (!head) return;
        DoubleNode* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    void removeTail() {
        if (!tail) return;
        DoubleNode* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    void read() const {
        DoubleNode* current = head;
        size_t index = 0;
        while (current) {
            cout << index++ << ": " << current->data << endl;
            current = current->next;
        }
    }
};

// Стек
struct Stack {
    LinkedList list;

    void push(const string& element) {
        list.addHead(element);
    }

    void pop() {
        list.removeHead();
    }

    void read() const {
        list.read();
    }
};

// Очередь
struct Queue {
    LinkedList list;

    void push(const string& element) {
        list.addTail(element);
    }

    void pop() {
        list.removeHead();
    }

    void read() const {
        list.read();
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    StringArray arr;
    LinkedList linkedList;
    DoublyLinkedList doublyLinkedList;
    Stack stack;
    Queue queue;

    string filename;
    cout << "Введите имя файла для загрузки (или нажмите Enter для пропуска): ";
    getline(cin, filename);
    if (!filename.empty()) {
        try {
            arr.loadFromFile(filename);
            cout << "Данные загружены из файла." << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }

    string command;
    while (true) {
        cout << "\nВведите команду (array, list, doubly_list, stack, queue, exit): ";
        getline(cin, command);

        if (command == "array") {
            string arrayCommand;
            while (true) {
                cout << "Команды для массива (add, insert, get, remove, replace, read, save, exit): ";
                getline(cin, arrayCommand);

                if (arrayCommand == "add") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    arr.add(element);
                }
                else if (arrayCommand == "insert") {
                    size_t index;
                    string element;
                    cout << "Введите индекс и элемент: ";
                    cin >> index;
                    cin.ignore();
                    getline(cin, element);
                    try {
                        arr.insert(index, element);
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "get") {
                    size_t index;
                    cout << "Введите индекс: ";
                    cin >> index;
                    cin.ignore();
                    try {
                        cout << "Элемент: " << arr.get(index) << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "remove") {
                    size_t index;
                    cout << "Введите индекс: ";
                    cin >> index;
                    cin.ignore();
                    try {
                        arr.remove(index);
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "replace") {
                    size_t index;
                    string element;
                    cout << "Введите индекс и элемент: ";
                    cin >> index;
                    cin.ignore();
                    getline(cin, element);
                    try {
                        arr.replace(index, element);
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "read") {
                    arr.read();
                }
                else if (arrayCommand == "save") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        arr.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        else if (command == "list") {
            string listCommand;
            while (true) {
                cout << "Команды для односвязного списка (addHead, addTail, removeHead, removeTail, read, exit): ";
                getline(cin, listCommand);

                if (listCommand == "addHead") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    linkedList.addHead(element);
                }
                else if (listCommand == "addTail") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    linkedList.addTail(element);
                }
                else if (listCommand == "removeHead") {
                    linkedList.removeHead();
                }
                else if (listCommand == "removeTail") {
                    linkedList.removeTail();
                }
                else if (listCommand == "read") {
                    linkedList.read();
                }
                else if (listCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        else if (command == "doubly_list") {
            string doublyListCommand;
            while (true) {
                cout << "Команды для двусвязного списка (addHead, addTail, removeHead, removeTail, read, exit): ";
                getline(cin, doublyListCommand);

                if (doublyListCommand == "addHead") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    doublyLinkedList.addHead(element);
                }
                else if (doublyListCommand == "addTail") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    doublyLinkedList.addTail(element);
                }
                else if (doublyListCommand == "removeHead") {
                    doublyLinkedList.removeHead();
                }
                else if (doublyListCommand == "removeTail") {
                    doublyLinkedList.removeTail();
                }
                else if (doublyListCommand == "read") {
                    doublyLinkedList.read();
                }
                else if (doublyListCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        else if (command == "stack") {
            string stackCommand;
            while (true) {
                cout << "Команды для стека (push, pop, read, exit): ";
                getline(cin, stackCommand);

                if (stackCommand == "push") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    stack.push(element);
                }
                else if (stackCommand == "pop") {
                    stack.pop();
                }
                else if (stackCommand == "read") {
                    stack.read();
                }
                else if (stackCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        else if (command == "queue") {
            string queueCommand;
            while (true) {
                cout << "Команды для очереди (push, pop, read, exit): ";
                getline(cin, queueCommand);

                if (queueCommand == "push") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    queue.push(element);
                }
                else if (queueCommand == "pop") {
                    queue.pop();
                }
                else if (queueCommand == "read") {
                    queue.read();
                }
                else if (queueCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда." << endl;
        }
    }

    return 0;
}
