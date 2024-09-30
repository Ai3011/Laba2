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

    // Очистка массива
    void clear() {
        size = 0;
    }

    // Загрузка данных из файла с очисткой массива перед этим
    void loadFromFile(const string& filename) {
        clear(); // Очищаем массив перед загрузкой данных

        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        string line;
        while (getline(file, line)) add(line);
        file.close();
    }

    // Сохранение данных в файл с очисткой массива после этого
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        for (size_t i = 0; i < size; ++i) {
            file << data[i] << endl;
        }
        file.close();

        // Очищаем массив после сохранения
        const_cast<StringArray*>(this)->clear(); // Используем const_cast для изменения массива в константном методе
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

// Узел односвязного списка
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

    // Добавление элемента в начало списка
    void addHead(const string& element) {
        Node* newNode = new Node(element);
        newNode->next = head;
        head = newNode;
        if (!tail) tail = head;
    }

    // Добавление элемента в конец списка
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

    // Удаление головы списка
    void removeHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
    }

    // Удаление хвоста списка
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

    // Вывод элементов списка на экран
    void read() const {
        Node* current = head;
        size_t index = 0;
        while (current) {
            cout << index++ << ": " << current->data << endl;
            current = current->next;
        }
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        // Очистка существующего списка
        while (head) {
            removeHead();
        }

        // Чтение данных из файла
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        string line;
        while (getline(file, line)) {
            addTail(line); // Добавление строки в конец списка
        }
        file.close();
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        Node* current = head;
        while (current) {
            file << current->data << endl;
            current = current->next;
        }
        file.close();

        // Очистка списка после сохранения
        const_cast<LinkedList*>(this)->clear();  // Используем const_cast, чтобы очистить список
    }

    // Очистка всего списка
    void clear() {
        while (head) {
            removeHead();
        }
    }
};

// Узел двусвязного списка
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
        clear(); // Очистка списка в деструкторе
    }

    // Добавление элемента в начало списка
    void addHead(const string& element) {
        DoubleNode* newNode = new DoubleNode(element);
        newNode->next = head;
        if (head) head->prev = newNode;
        head = newNode;
        if (!tail) tail = head;
    }

    // Добавление элемента в конец списка
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

    // Удаление головы списка
    void removeHead() {
        if (!head) return;
        DoubleNode* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    // Удаление хвоста списка
    void removeTail() {
        if (!tail) return;
        DoubleNode* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    // Вывод элементов списка на экран
    void read() const {
        DoubleNode* current = head;
        size_t index = 0;
        while (current) {
            cout << index++ << ": " << current->data << endl;
            current = current->next;
        }
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        // Очистка существующего списка
        clear();

        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        string line;
        while (getline(file, line)) {
            addTail(line); // Добавление строки в конец списка
        }
        file.close();
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Unable to open file");
        DoubleNode* current = head;
        while (current) {
            file << current->data << endl;
            current = current->next;
        }
        file.close();

        // Очистка списка после сохранения
        const_cast<DoublyLinkedList*>(this)->clear();  // Используем const_cast, чтобы вызвать очистку для константного объекта
    }

    // Очистка всего списка
    void clear() {
        while (head) {
            removeHead();
        }
    }
};


struct Stack {
    LinkedList list;

    // Добавление элемента в стек
    void push(const string& element) {
        list.addHead(element);
    }

    // Удаление элемента из стека
    void pop() {
        list.removeHead();
    }

    // Вывод содержимого стека
    void read() const {
        list.read();
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        list.loadFromFile(filename); // Делегирование функции LinkedList
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        list.saveToFile(filename); // Делегирование функции LinkedList
    }

    // Очистка стека
    void clear() {
        while (list.head) {
            list.removeHead();
        }
    }
};


struct Queue {
    LinkedList list;

    // Добавление элемента в очередь
    void push(const string& element) {
        list.addTail(element);
    }

    // Удаление элемента из очереди
    void pop() {
        list.removeHead();
    }

    // Вывод содержимого очереди
    void read() const {
        list.read();
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        list.loadFromFile(filename); // Делегирование функции LinkedList
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        list.saveToFile(filename); // Делегирование функции LinkedList
    }

    // Очистка очереди
    void clear() {
        while (list.head) {
            list.removeHead();
        }
    }
};

// Структура узла AVL-дерева
struct AVLNode {
    int key;              // Ключ (значение) узла
    AVLNode* left;        // Указатель на левое поддерево
    AVLNode* right;       // Указатель на правое поддерево
    int height;           // Высота узла
};

// Структура для узла очереди
struct QueueNode {
    AVLNode* treeNode;    // Указатель на узел дерева
    QueueNode* next;      // Указатель на следующий элемент очереди
};

// Самописная очередь
struct QueueForAvl {
    QueueNode* front;     // Начало очереди
    QueueNode* rear;      // Конец очереди
    int count;            // Счетчик узлов в очереди

    // Инициализация пустой очереди
    QueueForAvl() : front(nullptr), rear(nullptr), count(0) {}

    // Проверка, пуста ли очередь
    bool isEmpty() {
        return count == 0;  // Проверяем по счетчику
    }

    // Добавление узла дерева в очередь
    void enqueue(AVLNode* node) {
        QueueNode* newNode = new QueueNode();
        newNode->treeNode = node;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count++; // Увеличиваем счетчик
    }

    // Удаление узла из очереди и возвращение его
    AVLNode* dequeue() {
        if (isEmpty()) return nullptr;

        QueueNode* temp = front;
        AVLNode* result = front->treeNode;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        count--; // Уменьшаем счетчик
        return result;
    }

    // Метод получения размера очереди
    int size() const {
        return count; // Возвращаем текущее значение счетчика
    }
};

// Функция вывода дерева по уровням
void avlPrintByLevels(AVLNode* root) {
    if (!root) {
        cout << "Дерево пустое." << endl; // Сообщение, если дерево пустое
        return;
    }

    QueueForAvl q;           // Инициализируем очередь
    q.enqueue(root);         // Добавляем корень дерева в очередь

    while (!q.isEmpty()) {
        int levelSize = q.size(); // Получаем количество узлов на текущем уровне

        // Флаг, указывающий, была ли выведена хотя бы одна реальная нода
        bool hasNodes = false;

        // Проходим по всем узлам текущего уровня
        for (int i = 0; i < levelSize; ++i) {
            AVLNode* currentNode = q.dequeue(); // Берём узел из очереди

            // Если узел существует, выводим его ключ
            if (currentNode) {
                cout << currentNode->key << "\t"; // Выводим ключ текущего узла
                hasNodes = true; // Обозначаем, что есть узел для вывода
                // Добавляем потомков в очередь
                q.enqueue(currentNode->left);
                q.enqueue(currentNode->right);
            }
            else {
                cout << "-\t"; // Если узел отсутствует, выводим прочерк
                q.enqueue(nullptr); // Добавляем пустые узлы для возможных потомков
                q.enqueue(nullptr);
            }
        }

        // Если на уровне не было реальных узлов, прекращаем вывод
        if (!hasNodes) break;

        cout << endl; // Переход на новую строку после вывода одного уровня
    }
}



// Инициализация нового узла
AVLNode* avlCreateNode(int key) {
    AVLNode* node = new AVLNode(); // Выделяем память под новый узел
    node->key = key;               // Инициализируем ключ узла
    node->left = nullptr;          // Левый потомок отсутствует
    node->right = nullptr;         // Правый потомок отсутствует
    node->height = 1;              // Высота нового узла (так как он листовой)
    return node;                   // Возвращаем указатель на созданный узел
}

// Высота узла
int avlHeight(AVLNode* node) {
    return node ? node->height : 0;  // Если узел не nullptr, возвращаем его высоту, иначе 0 (высота пустого дерева)
}

// Баланс узла
int avlBalanceFactor(AVLNode* node) {
    return avlHeight(node->right) - avlHeight(node->left);  // Разница между высотой правого и левого поддеревьев
}

// Обновление высоты узла
void avlUpdateHeight(AVLNode* node) {
    int leftHeight = avlHeight(node->left);  // Получаем высоту левого поддерева
    int rightHeight = avlHeight(node->right); // Получаем высоту правого поддерева
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // Новая высота текущего узла — максимум из высот потомков + 1
}

// Правый поворот
AVLNode* avlRotateRight(AVLNode* p) {
    AVLNode* q = p->left;           // Берём левое поддерево узла p
    p->left = q->right;             // Переносим правое поддерево узла q на место левого поддерева узла p
    q->right = p;                   // Делаем p правым потомком узла q
    avlUpdateHeight(p);             // Обновляем высоту узла p
    avlUpdateHeight(q);             // Обновляем высоту узла q
    return q;                       // Возвращаем новый корень поддерева (узел q)
}

// Левый поворот
AVLNode* avlRotateLeft(AVLNode* q) {
    AVLNode* p = q->right;          // Берём правое поддерево узла q
    q->right = p->left;             // Переносим левое поддерево узла p на место правого поддерева узла q
    p->left = q;                    // Делаем q левым потомком узла p
    avlUpdateHeight(q);             // Обновляем высоту узла q
    avlUpdateHeight(p);             // Обновляем высоту узла p
    return p;                       // Возвращаем новый корень поддерева (узел p)
}

// Балансировка узла
AVLNode* avlBalance(AVLNode* node) {
    avlUpdateHeight(node);          // Обновляем высоту текущего узла
    if (avlBalanceFactor(node) == 2) {  // Если балансировка нарушена: правое поддерево слишком высокое
        if (avlBalanceFactor(node->right) < 0)  // Если правый потомок имеет левое смещение
            node->right = avlRotateRight(node->right);  // Выполняем правый поворот правого поддерева
        return avlRotateLeft(node);    // Выполняем левый поворот текущего узла
    }
    if (avlBalanceFactor(node) == -2) { // Если балансировка нарушена: левое поддерево слишком высокое
        if (avlBalanceFactor(node->left) > 0)  // Если левый потомок имеет правое смещение
            node->left = avlRotateLeft(node->left);  // Выполняем левый поворот левого поддерева
        return avlRotateRight(node);   // Выполняем правый поворот текущего узла
    }
    return node;                       // Возвращаем сбалансированный узел
}

// Вставка узла в дерево
AVLNode* avlInsert(AVLNode* node, int key) {
    if (node == nullptr) return avlCreateNode(key);  // Если узел пустой, создаем новый с переданным ключом
    if (key < node->key)                             // Если ключ меньше текущего, идём в левое поддерево
        node->left = avlInsert(node->left, key);     // Рекурсивно вставляем ключ в левое поддерево
    else                                             // Если ключ больше или равен текущему
        node->right = avlInsert(node->right, key);   // Рекурсивно вставляем ключ в правое поддерево
    return avlBalance(node);                         // После вставки выполняем балансировку
}

// Поиск минимального узла
AVLNode* avlFindMin(AVLNode* node) {
    return node->left ? avlFindMin(node->left) : node;  // Ищем минимальный элемент, спускаясь по левым потомкам
}

// Удаление минимального узла
AVLNode* avlRemoveMin(AVLNode* node) {
    if (!node->left) return node->right;  // Если нет левого поддерева, возвращаем правое поддерево
    node->left = avlRemoveMin(node->left); // Рекурсивно удаляем минимальный узел в левом поддереве
    return avlBalance(node);               // Выполняем балансировку после удаления
}

// Удаление узла с ключом
AVLNode* avlRemove(AVLNode* node, int key) {
    if (node == nullptr) return nullptr;           // Если узел пустой, возвращаем nullptr
    if (key < node->key)                           // Если ключ меньше текущего, идём в левое поддерево
        node->left = avlRemove(node->left, key);   // Рекурсивно удаляем узел в левом поддереве
    else if (key > node->key)                      // Если ключ больше текущего, идём в правое поддерево
        node->right = avlRemove(node->right, key); // Рекурсивно удаляем узел в правом поддереве
    else {                                         // Если нашли узел с нужным ключом
        AVLNode* left = node->left;                // Сохраняем левое поддерево
        AVLNode* right = node->right;              // Сохраняем правое поддерево
        delete node;                               // Удаляем текущий узел
        if (!right) return left;                   // Если нет правого поддерева, возвращаем левое
        AVLNode* min = avlFindMin(right);          // Находим минимальный узел в правом поддереве
        min->right = avlRemoveMin(right);          // Удаляем минимальный узел из правого поддерева
        min->left = left;                          // Присоединяем левое поддерево к минимальному узлу
        return avlBalance(min);                    // Выполняем балансировку после удаления
    }
    return avlBalance(node);                       // Возвращаем сбалансированный узел
}

// Очистка дерева (удаление всех узлов)
void avlClear(AVLNode*& node) {
    if (node) {
        avlClear(node->left);  // Рекурсивно удаляем левое поддерево
        avlClear(node->right); // Рекурсивно удаляем правое поддерево
        delete node;           // Удаляем текущий узел
        node = nullptr;        // Устанавливаем указатель на узел в nullptr
    }
}



// Сохранение дерева в файл и его очистка
void avlSaveToFile(AVLNode*& node, ofstream& file) {
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file for writing.");
    }
    if (node) {
        file << node->key << " ";
        avlSaveToFile(node->left, file);
        avlSaveToFile(node->right, file);
    }
    avlClear(node);  // Очищаем дерево после сохранения
}

// Загрузка дерева из файла (с предварительной очисткой)
AVLNode* avlLoadFromFile(AVLNode*& node, ifstream& file) {
    avlClear(node);  // Очищаем дерево перед загрузкой
    int key;
    while (file >> key) {
        node = avlInsert(node, key);  // Вставляем ключи по мере чтения
    }
    return node;
}

int main() {
    setlocale(LC_ALL, "RU");
    StringArray arr;
    LinkedList linkedList;
    DoublyLinkedList doublyLinkedList;
    Stack stack;
    Queue queue;
    AVLNode* avlTree = nullptr;

    string command;
    while (true) {
        cout << "\nВведите команду (array, list, doubly_list, stack, queue, avl, exit): ";
        getline(cin, command);

        // Работа с массивом
        if (command == "array") {
            string arrayCommand;
            while (true) {
                cout << "Команды для массива (add, insert, get, remove, replace, read, lenght, save, load, exit): ";
                getline(cin, arrayCommand);

                if (arrayCommand == "add") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    arr.add(element);
                }
                else if (arrayCommand == "lenght") {
                    string element;
                    cout << "Длина массива : " << arr.length() << endl;
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
                else if (arrayCommand == "load") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        arr.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
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
        // Работа с односвязным списком
        else if (command == "list") {
            string listCommand;
            while (true) {
                cout << "Команды для односвязного списка (addHead, addTail, removeHead, removeTail, read, save, load, exit): ";
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
                else if (listCommand == "save") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        linkedList.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (listCommand == "load") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        linkedList.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (listCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        //Двусвязный список
        else if (command == "doubly_list") {
            string doublyListCommand;
            while (true) {
                cout << "Команды для двусвязного списка (addHead, addTail, removeHead, removeTail, read, save, load, exit): ";
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
                else if (doublyListCommand == "save") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        doublyLinkedList.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (doublyListCommand == "load") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        doublyLinkedList.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (doublyListCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        //Стек
        else if (command == "stack") {
            string stackCommand;
            while (true) {
                cout << "Команды для стека (push, pop, read, save, load, exit): ";
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
                else if (stackCommand == "save") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        stack.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (stackCommand == "load") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        stack.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (stackCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        //Очередь
        else if (command == "queue") {
            string queueCommand;
            while (true) {
                cout << "Команды для очереди (push, pop, read, save, load, exit): ";
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
                else if (queueCommand == "save") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        queue.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (queueCommand == "load") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        queue.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (queueCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }

        // Команды для работы с AVL-деревом
        else if (command == "avl") {
            string avlCommand;
            while (true) {
                cout << "Команды для AVL-дерева (add, remove, print, save, load, exit): ";
                getline(cin, avlCommand);

                if (avlCommand == "add") {
                    int key;
                    cout << "Введите ключ: ";
                    cin >> key;
                    cin.ignore();
                    avlTree = avlInsert(avlTree, key);
                }
                else if (avlCommand == "remove") {
                    int key;
                    cout << "Введите ключ для удаления: ";
                    cin >> key;
                    cin.ignore();
                    avlTree = avlRemove(avlTree, key);
                }
                else if (avlCommand == "print") {
                    cout << "Дерево (in-order): \n ";
                    avlPrintByLevels(avlTree);
                    cout << endl;
                }
                else if (avlCommand == "save") {
                    string filename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, filename);
                    ofstream file(filename);
                    if (file.is_open()) {
                        avlSaveToFile(avlTree, file);
                        file.close();
                        cout << "Дерево сохранено в файл." << endl;
                    }
                    else {
                        cout << "Ошибка открытия файла!" << endl;
                    }
                }
                else if (avlCommand == "load") {
                    string filename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, filename);
                    ifstream file(filename);
                    if (file.is_open()) {
                        avlTree = avlLoadFromFile(avlTree, file);
                        file.close();
                        cout << "Дерево загружено из файла." << endl;
                    }
                    else {
                        cout << "Ошибка открытия файла!" << endl;
                    }
                }
                else if (avlCommand == "exit") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        // Завершение программы
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Неизвестная команда." << endl;
        }
    }

    return 0;
}
