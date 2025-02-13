# Двоичное дерево поиска: Программа для работы с бинарными файлами

## Описание

Данная программа реализует бинарное дерево поиска (BST), позволяющее выполнять операции поиска, вставки, удаления элементов, а также выводить наименьшие 10 элементов из дерева. Программа считывает данные из бинарного файла, содержащего 32-битные целые числа (`int32`), и предоставляет пользователю интерфейс для взаимодействия с деревом.

Каждая операция отображает время выполнения, что позволяет оценить производительность дерева при различных действиях.

## Требования

- **Компилятор C++**: Поддерживающий стандарт C++11 или выше (например, `g++`, `clang++`).
- **Операционная система**: Windows, Linux, macOS или любая другая ОС с поддержкой C++.

## Сборка

1. **Скачайте исходный код** программы и сохраните его в файл, например, `main.cpp`.

2. **Откройте терминал** или командную строку и перейдите в директорию с исходным кодом.

3. **Скомпилируйте программу** с помощью компилятора C++. Например, используя `g++`:

   ```bash
   g++ -o bst_program four.cpp
   ```

   Где `four.cpp` — имя файла с исходным кодом, а `bst_program` — имя создаваемого исполняемого файла.

## Использование

Запустите программу, передав в качестве аргумента имя входного бинарного файла:

```bash
./bst_program input_file.bin
```

готовые тест кейсы лежат в папке Task48

### Интерфейс пользователя

После запуска программа загрузит данные из указанного файла в бинарном формате и предложит меню для выбора операций:

```
Select operation:
1. Search
2. Insert
3. Remove
4. Get 10 smallest elements
5. Print tree
6. Exit
Choice:
```

#### Доступные операции:

1. **Поиск элемента**

   Позволяет найти элемент в дереве по заданному ключу.

2. **Вставка элемента**

   Вставляет новый элемент с указанным ключом в дерево.

3. **Удаление элемента**

   Удаляет элемент с заданным ключом из дерева.

4. **Получить 10 наименьших элементов**

   Выводит 10 наименьших элементов дерева.

5. **Печать структуры дерева**

   Отображает структуру дерева в консоль с возможностью ограничения глубины отображения.

6. **Выход**

   Завершает работу программы.

Каждая операция отображает время выполнения с точностью до шести знаков после запятой.

### Пример использования

**Поиск элемента:**

```
Select operation:
1. Search
2. Insert
3. Remove
4. Get 10 smallest elements
5. Print tree
6. Exit
Choice: 1
Enter element to search: 42
Element found in tree.
Operation time: 0.000123 seconds
```

**Вставка элемента:**

```
Select operation:
1. Search
2. Insert
3. Remove
4. Get 10 smallest elements
5. Print tree
6. Exit
Choice: 2
Enter element to insert: 55
Element inserted.
Operation time: 0.000456 seconds
```

## Структура файла

Входной файл должен быть бинарным и содержать 32-битные целые числа (`int32`) в формате, совместимом с платформой, на которой выполняется программа. Программа последовательно считывает числа из файла и вставляет их в дерево.

### Пример создания бинарного файла

Вот пример того, как можно создать бинарный файл с числами на языке C++:

```cpp
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::vector<int32_t> numbers = {5, 3, 8, 1, 4, 7, 10};
    std::ofstream outFile("data.bin", std::ios::binary);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }
    for (int32_t num : numbers) {
        outFile.write(reinterpret_cast<char*>(&num), sizeof(num));
    }
    outFile.close();
    return 0;
}
```

## Функциональность

- **Чтение из файла:** Программа открывает бинарный файл, считывает все числа и строит бинарное дерево поиска.
  
- **Интерфейс пользователя:** Предоставляет меню для выбора операций над деревом.

- **Операции над деревом:**
  - **Поиск элемента:** Находит заданный элемент в дереве.
  - **Вставка элемента:** Вставляет новый элемент в дерево.
  - **Удаление элемента:** Удаляет существующий элемент из дерева.
  - **Получение 10 наименьших элементов:** Извлекает и выводит 10 наименьших элементов дерева.
  - **Печать структуры дерева:** Выводит графическое представление дерева в консоль с возможностью ограничения глубины отображения.
  
- **Измерение времени:** Каждая операция измеряется по времени выполнения и выводится пользователю.
