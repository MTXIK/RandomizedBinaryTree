#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>
#include <cstdlib>    // Для использования функции rand()
#include <algorithm>  // Для std::max

// Структура узла бинарного дерева
struct Node {
    int key;        // Значение ключа
    int size;       // Размер поддерева, корнем которого является данный узел (количество узлов в поддереве)
    Node* left;     // Указатель на левый дочерний узел
    Node* right;    // Указатель на правый дочерний узел

    // Конструктор узла, инициализирует ключ и устанавливает размер поддерева равным 1
    Node(int k) : key(k), size(1), left(nullptr), right(nullptr) {}
};

// Функция для получения размера поддерева
int getSize(Node* node) {
    return node ? node->size : 0;
}

// Функция для обновления размера поддерева
void fixSize(Node* node) {
    if (node) {
        node->size = getSize(node->left) + getSize(node->right) + 1;
    }
}

// Функция для выполнения правого поворота вокруг узла p
Node* rotateRight(Node* p) {
    Node* q = p->left; // Узел q становится новым корнем поддерева
    if (!q) return p;  // Если левый дочерний узел отсутствует, поворот невозможен
    p->left = q->right; // Правый дочерний узел q становится левым дочерним узлом p
    q->right = p;       // p становится правым дочерним узлом q
    q->size = p->size;  // Обновляем размер q, так как он теперь корень поддерева
    fixSize(p);         // Обновляем размер p, так как его поддерево изменилось
    return q;           // Возвращаем новый корень поддерева
}

// Функция для выполнения левого поворота вокруг узла q
Node* rotateLeft(Node* q) {
    Node* p = q->right; // Узел p становится новым корнем поддерева
    if (!p) return q;   // Если правый дочерний узел отсутствует, поворот невозможен
    q->right = p->left; // Левый дочерний узел p становится правым дочерним узлом q
    p->left = q;        // q становится левым дочерним узлом p
    p->size = q->size;  // Обновляем размер p, так как он теперь корень поддерева
    fixSize(q);         // Обновляем размер q, так как его поддерево изменилось
    return p;           // Возвращаем новый корень поддерева
}

// Функция вставки узла с ключом key в качестве корня поддерева
Node* insertRoot(Node* p, int key) {
    if (!p) return new Node(key); // Если дерево пустое, создаем новый узел
    if (key < p->key) {
        p->left = insertRoot(p->left, key); // Рекурсивно вставляем в левое поддерево
        return rotateRight(p);                // Выполняем правый поворот, чтобы сделать новый узел корнем
    } else {
        p->right = insertRoot(p->right, key); // Рекурсивно вставляем в правое поддерево
        return rotateLeft(p);                   // Выполняем левый поворот, чтобы сделать новый узел корнем
    }
}

// Функция вставки узла с ключом key в дерево
Node* insert(Node* p, int key) {
    if (!p) return new Node(key); // Если дерево пустое, создаем новый узел
    // С вероятностью 1/(размер поддерева + 1) вставляем узел как корень поддерева
    if (rand() % (p->size + 1) == 0)
        return insertRoot(p, key);
    if (key < p->key)
        p->left = insert(p->left, key);  // Рекурсивно вставляем в левое поддерево
    else
        p->right = insert(p->right, key); // Рекурсивно вставляем в правое поддерево
    fixSize(p); // Обновляем размер поддерева после вставки
    return p;    // Возвращаем корень поддерева
}

// Функция для объединения двух деревьев p и q
Node* join(Node* p, Node* q) {
    if (!p) return q; // Если первое дерево пустое, возвращаем второе
    if (!q) return p; // Если второе дерево пустое, возвращаем первое
    // С вероятностью p->size / (p->size + q->size) делаем p корнем
    if (rand() % (p->size + q->size) < p->size) {
        p->right = join(p->right, q); // Рекурсивно объединяем правое поддерево p с q
        fixSize(p);                   // Обновляем размер поддерева p
        return p;                     // Возвращаем p как корень объединенного дерева
    } else {
        q->left = join(p, q->left); // Иначе делаем q корнем и объединяем левое поддерево q с p
        fixSize(q);                 // Обновляем размер поддерева q
        return q;                   // Возвращаем q как корень объединенного дерева
    }
}

// Функция удаления узла с ключом key из дерева
Node* remove(Node* p, int key) {
    if (!p) return nullptr; // Если дерево пустое, возвращаем nullptr
    if (p->key == key) {
        Node* q = join(p->left, p->right); // Объединяем левое и правое поддеревья
        delete p;                         // Удаляем текущий узел
        return q;                         // Возвращаем объединенное поддерево
    } else if (key < p->key) {
        p->left = remove(p->left, key); // Рекурсивно удаляем из левого поддерева
    } else {
        p->right = remove(p->right, key); // Рекурсивно удаляем из правого поддерева
    }
    fixSize(p); // Обновляем размер поддерева после удаления
    return p;    // Возвращаем корень поддерева
}

// Функция поиска узла с ключом key в дереве
Node* find(Node* p, int key) {
    if (!p) return nullptr;            // Если дерево пустое или достигли листа, возвращаем nullptr
    if (p->key == key) return p;       // Если текущий узел содержит ключ, возвращаем его
    if (key < p->key)
        return find(p->left, key);      // Рекурсивно ищем в левом поддереве
    else
        return find(p->right, key);     // Рекурсивно ищем в правом поддереве
}

// Функция для получения k наименьших элементов в дереве
void getMinElements(Node* p, std::vector<int>& result, int k) {
    if (!p || result.size() >= k) return; // Если дерево пустое или уже собрали k элементов, прекращаем
    getMinElements(p->left, result, k);   // Рекурсивно собираем элементы из левого поддерева
    if (result.size() < k)
        result.push_back(p->key);         // Добавляем текущий ключ, если еще не достигли k
    getMinElements(p->right, result, k);  // Рекурсивно собираем элементы из правого поддерева
}

// Функция для графического вывода дерева в консоль с ограничением глубины
// Если maxDepth = -1, ограничение глубины не применяется
void printTree(const Node* node, const std::string& prefix = "", bool isLeft = true, int currentDepth = 0, int maxDepth = -1) {
    if (!node) return;

    // Если достигли максимальной глубины и maxDepth не равен -1, выводим узел и прекращаем рекурсию
    if (maxDepth != -1 && currentDepth > maxDepth) {
        std::cout << prefix;
        std::cout << (isLeft ? "├── " : "└── ");
        std::cout << node->key << " ..." << std::endl; // "..." указывает на продолжение поддерева
        return;
    }

    // Выводим текущий узел с префиксом и символом для визуального представления
    std::cout << prefix;
    std::cout << (isLeft ? "├── " : "└── ");
    std::cout << node->key << std::endl;

    // Рекурсивно выводим левое и правое поддеревья с увеличением текущей глубины
    printTree(node->left, prefix + (isLeft ? "│   " : "    "), true, currentDepth + 1, maxDepth);
    printTree(node->right, prefix + (isLeft ? "│   " : "    "), false, currentDepth + 1, maxDepth);
}

// Функция для удаления всего дерева и освобождения памяти
void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);   // Рекурсивно удаляем левое поддерево
        deleteTree(node->right);  // Рекурсивно удаляем правое поддерево
        delete node;               // Удаляем текущий узел
    }
}

int main(int argc, char* argv[]) {
    // Проверка наличия аргумента командной строки (имя входного файла)
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    const char* filename = argv[1]; // Имя файла передается как первый аргумент
    std::ifstream file(filename, std::ios::binary); // Открываем файл в бинарном режиме
    if (!file) { // Проверяем, успешно ли открыт файл
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    Node* tree = nullptr; // Инициализируем корень дерева как пустой
    int value;            // Переменная для хранения считанного значения

    // Загрузка элементов из файла в дерево
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        tree = insert(tree, value); // Вставляем считанное значение в дерево
    }
    file.close(); // Закрываем файл после чтения

    // Основной цикл программы для выполнения операций над деревом
    while (true) {
        // Вывод меню выбора операции
        std::cout << "Select operation:\n"
                  << "1. Search\n"
                  << "2. Insert\n"
                  << "3. Remove\n"
                  << "4. Get 10 smallest elements\n"
                  << "5. Print tree\n"
                  << "6. Exit\n"
                  << "Choice: ";
        int choice;
        std::cin >> choice; // Считываем выбор пользователя

        if (choice == 6) break; // Если выбрали 7, выходим из цикла

        auto start = std::chrono::high_resolution_clock::now(); // Запоминаем время начала операции

        if (choice == 1) { // Поиск элемента
            std::cout << "Enter element to search: ";
            int key;
            std::cin >> key; // Считываем ключ для поиска

            Node* result = find(tree, key); // Выполняем поиск
            auto end = std::chrono::high_resolution_clock::now(); // Запоминаем время окончания
            std::chrono::duration<double> duration = end - start; // Вычисляем длительность операции

            if (result) {
                std::cout << "Element found in tree." << std::endl;
            } else {
                std::cout << "Element not found in tree." << std::endl;
            }
            // Выводим время выполнения операции с шестью знаками после запятой
            std::cout << "Operation time: " << std::fixed << std::setprecision(6)
                      << duration.count() << " seconds" << std::endl;

        } else if (choice == 2) { // Вставка элемента
            std::cout << "Enter element to insert: ";
            int key;
            std::cin >> key; // Считываем ключ для вставки

            tree = insert(tree, key); // Вставляем элемент в дерево
            auto end = std::chrono::high_resolution_clock::now(); // Запоминаем время окончания
            std::chrono::duration<double> duration = end - start; // Вычисляем длительность операции

            std::cout << "Element inserted." << std::endl;
            // Выводим время выполнения операции
            std::cout << "Operation time: " << std::fixed << std::setprecision(6)
                      << duration.count() << " seconds" << std::endl;

        } else if (choice == 3) { // Удаление элемента
            std::cout << "Enter element to remove: ";
            int key;
            std::cin >> key; // Считываем ключ для удаления

            tree = remove(tree, key); // Удаляем элемент из дерева
            auto end = std::chrono::high_resolution_clock::now(); // Запоминаем время окончания
            std::chrono::duration<double> duration = end - start; // Вычисляем длительность операции

            std::cout << "Element removed (if it existed)." << std::endl;
            // Выводим время выполнения операции
            std::cout << "Operation time: " << std::fixed << std::setprecision(6)
                      << duration.count() << " seconds" << std::endl;

        } else if (choice == 4) { // Получение 10 наименьших элементов
            std::vector<int> min_elements; // Вектор для хранения результатов
            getMinElements(tree, min_elements, 10); // Получаем 10 наименьших элементов
            auto end = std::chrono::high_resolution_clock::now(); // Запоминаем время окончания
            std::chrono::duration<double> duration = end - start; // Вычисляем длительность операции

            std::cout << "10 smallest elements: ";
            for (int elem : min_elements) { // Выводим элементы
                std::cout << elem << " ";
            }
            std::cout << "\nOperation time: " << std::fixed << std::setprecision(6)
                      << duration.count() << " seconds" << std::endl;

        } else if (choice == 5) { // Печать структуры дерева с ограничением глубины
            std::cout << "Enter maximum depth for printing (-1 for no limit): ";
            int maxDepth;
            std::cin >> maxDepth; // Считываем максимальную глубину

            std::cout << "Tree structure:\n";
            printTree(tree, "", true, 0, maxDepth); // Вызываем функцию для вывода дерева
        } else { // Обработка некорректного выбора
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    // Освобождение памяти, занятой деревом
    deleteTree(tree);

    return 0; // Завершаем программу
}
