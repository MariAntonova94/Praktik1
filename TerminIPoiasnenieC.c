Неделя 1: Основы
1.1 Синтаксис C
Синтаксис языка C определяет правила написания кода. Важно понимать, как правильно писать инструкции и использовать ключевые слова.

Комментарии: Для пояснений в коде используются комментарии.

c
Копировать код
// Это однострочный комментарий
/* Это
   многострочный
   комментарий */
Функции: Основной блок кода, который выполняется, называется функцией. Главная функция программы – main().

c
Копировать код
int main() { // Объявление функции main, которая возвращает целое число
    // Код внутри функции
    return 0; // Возвращаемое значение функции (0 указывает на успешное выполнение)
}
1.2 Переменные и типы данных
Переменные используются для хранения данных. Типы данных указывают, какого типа данные будут храниться.

Целые числа: int

c
Копировать код
int age = 25; // Объявление целочисленной переменной age и присвоение ей значения 25
Числа с плавающей запятой: float, double

c
Копировать код
float height = 5.9; // Объявление переменной height типа float и присвоение ей значения 5.9
double distance = 1234.56; // Объявление переменной distance типа double и присвоение ей значения 1234.56
Символы: char

c
Копировать код
char letter = 'A'; // Объявление переменной letter типа char и присвоение ей значения 'A'
1.3 Операторы
Операторы позволяют выполнять операции над переменными.

Арифметические операторы: +, -, *, /, %

c
Копировать код
int a = 10, b = 3; // Объявление переменных a и b и присвоение им значений 10 и 3
int sum = a + b;    // Сложение a и b, результат присваивается переменной sum
int diff = a - b;   // Вычитание b из a, результат присваивается переменной diff
int product = a * b; // Умножение a на b, результат присваивается переменной product
int quotient = a / b; // Деление a на b, результат присваивается переменной quotient
int remainder = a % b; // Остаток от деления a на b, результат присваивается переменной remainder
Операторы сравнения: ==, !=, <, >, <=, >=

c
Копировать код
int x = 5, y = 10; // Объявление переменных x и y и присвоение им значений 5 и 10
int isEqual = (x == y); // Сравнение x и y на равенство, результат (0 или 1) присваивается переменной isEqual
1.4 Простые программы
Hello, World!: Программа, которая выводит текст на экран.

c
Копировать код
#include <stdio.h> // Подключение библиотеки ввода-вывода

int main() { // Главная функция программы
    printf("Hello, World!\n"); // Вызов функции printf для вывода текста на экран
    return 0; // Завершение функции main с кодом возврата 0
}
Калькулятор: Программа, которая выполняет простые арифметические операции.

c
Копировать код
#include <stdio.h> // Подключение библиотеки ввода-вывода

int main() { // Главная функция программы
    int a, b; // Объявление целочисленных переменных a и b
    char operator; // Объявление переменной operator для хранения символа оператора

    printf("Введите выражение (например, 3 + 2): "); // Вывод приглашения для ввода выражения
    scanf("%d %c %d", &a, &operator, &b); // Считывание двух чисел и оператора

    switch (operator) { // Оператор switch для выполнения действия в зависимости от значения operator
        case '+':
            printf("Результат: %d\n", a + b); // Вывод суммы a и b
            break;
        case '-':
            printf("Результат: %d\n", a - b); // Вывод разности a и b
            break;
        case '*':
            printf("Результат: %d\n", a * b); // Вывод произведения a и b
            break;
        case '/':
            printf("Результат: %d\n", a / b); // Вывод частного a и b
            break;
        default:
            printf("Неверный оператор!\n"); // Вывод сообщения об ошибке, если введен неверный оператор
    }

    return 0; // Завершение функции main с кодом возврата 0
}
Неделя 2: Управляющие конструкции и функции
2.1 Условные операторы
Условные операторы позволяют выполнять код в зависимости от условий.

if, else: Проверка условия и выполнение соответствующего кода.

c
Копировать код
int number = 10; // Объявление переменной number и присвоение ей значения 10

if (number > 5) { // Если number больше 5
    printf("Число больше 5\n"); // Вывод сообщения
} else { // В противном случае
    printf("Число меньше или равно 5\n"); // Вывод другого сообщения
}
switch: Выбор и выполнение одной из нескольких ветвей кода.

c
Копировать код
char grade = 'B'; // Объявление переменной grade и присвоение ей значения 'B'

switch (grade) { // Оператор switch для проверки значения переменной grade
    case 'A':
        printf("Отлично!\n"); // Если grade равен 'A', выводится это сообщение
        break;
    case 'B':
        printf("Хорошо!\n"); // Если grade равен 'B', выводится это сообщение
        break;
    case 'C':
        printf("Удовлетворительно!\n"); // Если grade равен 'C', выводится это сообщение
        break;
    default:
        printf("Неизвестная оценка!\n"); // В любом другом случае выводится это сообщение
}
2.2 Циклы
Циклы позволяют повторять выполнение блока кода.

for: Цикл с заданным числом повторений.

c
Копировать код
for (int i = 0; i < 10; i++) { // Инициализация переменной i, проверка условия и увеличение i на 1 после каждой итерации
    printf("%d\n", i); // Вывод значения i
}
while: Цикл с условием в начале.

c
Копировать код
int i = 0; // Объявление переменной i и присвоение ей значения 0
while (i < 10) { // Выполнение цикла, пока i меньше 10
    printf("%d\n", i); // Вывод значения i
    i++; // Увеличение i на 1 после каждой итерации
}
do-while: Цикл с условием в конце.

c
Копировать код
int i = 0; // Объявление переменной i и присвоение ей значения 0
do {
    printf("%d\n", i); // Вывод значения i
    i++; // Увеличение i на 1 после каждой итерации
} while (i < 10); // Выполнение цикла, пока i меньше 10
2.3 Функции
Функции позволяют разделять код на логические блоки и вызывать их по имени.

Объявление и определение функции:
c
Копировать код
int sum(int a, int b) { // Объявление и определение функции sum, которая принимает два целых числа и возвращает их сумму
    return a + b; // Возвращает сумму a и b
}

int main() {
    int result = sum(3, 4); // Вызов функции sum с аргументами 3 и 4, результат присваивается переменной result
    printf("Сумма: %d\n", result); // Вывод результата
    return 0; // Завершение функции main с кодом возврата 0
}
Неделя 3: Массивы и строки
3.1 Массивы
Массивы позволяют хранить несколько значений одного типа данных в одной переменной.

Одномерные массивы:

c
Копировать код
int numbers[5] = {1, 2, 3, 4, 5}; // Объявление и инициализация массива из 5 целых чисел

for (int i = 0; i < 5; i++) { // Цикл для доступа к элементам массива
    printf("%d\n", numbers[i]); // Вывод значения элемента массива по индексу i
}
Двумерные массивы:

c
Копировать код
int matrix[2][3] = { {1, 2, 3}, {4, 5, 6} }; // Объявление и инициализация двумерного массива

for (int i = 0; i < 2; i++) { // Внешний цикл для строк
    for (int j = 0; j < 3; j++) { // Внутренний цикл для столбцов
        printf("%d ", matrix[i][j]); // Вывод значения элемента массива по индексам i и j
    }
    printf("\n"); // Переход на новую строку после вывода одной строки массива
}
3.2 Строки
Строки в C – это массивы символов, завершающиеся нулевым символом (\0).

Объявление и использование строк:

c
Копировать код
char greeting[] = "Hello"; // Объявление и инициализация строки

printf("%s\n", greeting); // Вывод строки
Ввод и вывод строк:

c
Копировать код
char name[50]; // Объявление массива символов для хранения строки

printf("Введите ваше имя: "); // Вывод приглашения для ввода имени
scanf("%s", name); // Считывание строки с клавиатуры

printf("Привет, %s!\n", name); // Вывод введенного имени
Использование библиотечных функций для работы со строками:

c
Копировать код
#include <string.h> // Подключение библиотеки для работы со строками

char str1[20] = "Hello, "; // Объявление и инициализация строки str1
char str2[] = "World!"; // Объявление и инициализация строки str2

strcat(str1, str2); // Конкатенация (соединение) str2 к str1
printf("%s\n", str1); // Вывод объединенной строки
Неделя 4: Указатели и динамическая память
4.1 Указатели
Указатели хранят адреса переменных и позволяют работать с данными напрямую в памяти.

Объявление и использование указателей:
c
Копировать код
int num = 10; // Объявление переменной num и присвоение ей значения 10
int *ptr = &num; // Объявление указателя ptr и присвоение ему адреса переменной num

printf("Значение num: %d\n", num); // Вывод значения переменной num
printf("Адрес num: %p\n", &num); // Вывод адреса переменной num
printf("Значение через указатель: %d\n", *ptr); // Вывод значения переменной num через указатель ptr
4.2 Арифметика указателей
Указатели можно использовать для доступа к массивам и работы с ними.

Пример работы с массивом через указатель:
c
Копировать код
int arr[] = {1, 2, 3, 4, 5}; // Объявление и инициализация массива
int *ptr = arr; // Присвоение указателю ptr адреса первого элемента массива

for (int i = 0; i < 5; i++) {
    printf("arr[%d] = %d\n", i, *(ptr + i)); // Доступ к элементам массива через указатель
}
4.3 Динамическая память
Динамическое выделение памяти позволяет управлять памятью во время выполнения программы.

malloc и free:
c
Копировать код
int *arr = (int *)malloc(5 * sizeof(int)); // Выделение памяти для массива из 5 элементов

if (arr == NULL) { // Проверка, удалось ли выделить память
    printf("Ошибка выделения памяти\n");
    return 1; // Завершение программы с ошибкой
}

for (int i = 0; i < 5; i++) { // Инициализация массива
    arr[i] = i + 1; // Присвоение значения элементу массива
}

for (int i = 0; i < 5; i++) { // Вывод элементов массива
    printf("%d\n", arr[i]);
}

free(arr); // Освобождение выделенной памяти
4.4 Указатели на функции
Указатели на функции позволяют передавать функции как аргументы другим функциям.

Пример указателя на функцию:
c
Копировать код
int add(int a, int b) { // Функция, которая возвращает сумму двух чисел
    return a + b;
}

int subtract(int a, int b) { // Функция, которая возвращает разность двух чисел
    return a - b;
}

int operate(int a, int b, int (*operation)(int, int)) { // Функция, принимающая указатель на другую функцию
    return operation(a, b); // Вызов функции через указатель
}

int main() {
    int x = 10, y = 5; // Объявление переменных x и y и присвоение им значений 10 и 5

    printf("Сумма: %d\n", operate(x, y, add)); // Вызов функции operate с указателем на функцию add
    printf("Разность: %d\n", operate(x, y, subtract)); // Вызов функции operate с указателем на функцию subtract

    return 0; // Завершение функции main с кодом возврата 0
}
Неделя 5: Структуры и файлы
5.1 Структуры
Структуры позволяют объединять разные типы данных в одной переменной.

Объявление и использование структур:
c
Копировать код
struct Person { // Объявление структуры Person
    char name[50]; // Поле для хранения имени
    int age; // Поле для хранения возраста
    float height; // Поле для хранения роста
};

int main() {
    struct Person person; // Объявление переменной person типа структуры Person

    strcpy(person.name, "John Doe"); // Присвоение значения полю name
    person.age = 30; // Присвоение значения полю age
    person.height = 5.9; // Присвоение значения полю height

    printf("Имя: %s\n", person.name); // Вывод значения поля name
    printf("Возраст: %d\n", person.age); // Вывод значения поля age
    printf("Рост: %.2f\n", person.height); // Вывод значения поля height

    return 0; // Завершение функции main с кодом возврата 0
}
5.2 Работа с файлами
Работа с файлами включает чтение и запись данных в файлы.

Чтение и запись в файл:
c
Копировать код
#include <stdio.h> // Подключение библиотеки ввода-вывода

int main() {
    FILE *file; // Объявление указателя на файл
    char data[50]; // Объявление массива для хранения данных

    // Запись в файл
    file = fopen("example.txt", "w"); // Открытие файла для записи
    if (file == NULL) { // Проверка, удалось ли открыть файл
        printf("Ошибка открытия файла\n");
        return 1; // Завершение программы с ошибкой
    }
    fprintf(file, "Hello, World!\n"); // Запись строки в файл
    fclose(file); // Закрытие файла

    // Чтение из файла
    file = fopen("example.txt", "r"); // Открытие файла для чтения
    if (file == NULL) { // Проверка, удалось ли открыть файл
        printf("Ошибка открытия файла\n");
        return 1; // Завершение программы с ошибкой
    }
    fgets(data, 50, file); // Чтение строки из файла
    printf("Прочитано из файла: %s", data); // Вывод прочитанной строки
    fclose(file); // Закрытие файла

    return 0; // Завершение функции main с кодом возврата 0
}
Неделя 6: Алгоритмы и структуры данных
6.1 Алгоритмы
Изучение и реализация базовых алгоритмов.

Сортировка пузырьком:
c
Копировать код
void bubbleSort(int arr[], int n) { // Функция для сортировки массива пузырьком
    for (int i = 0; i < n-1; i++) { // Внешний цикл
        for (int j = 0; j < n-i-1; j++) { // Внутренний цикл
            if (arr[j] > arr[j+1]) { // Если текущий элемент больше следующего
                int temp = arr[j]; // Обмен элементов
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90}; // Объявление и инициализация массива
    int n = sizeof(arr)/sizeof(arr[0]); // Вычисление размера массива

    bubbleSort(arr, n); // Вызов функции сортировки

    printf("Отсортированный массив: "); // Вывод отсортированного массива
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0; // Завершение функции main с кодом возврата 0
}
6.2 Структуры данных
Изучение и реализация базовых структур данных.

Связный список:
c
Копировать код
struct Node { // Объявление структуры Node
    int data; // Поле для хранения данных
    struct Node *next; // Поле для хранения указателя на следующий элемент списка
};

void printList(struct Node *node) { // Функция для вывода списка
    while (node != NULL) {
        printf("%d ", node->data); // Вывод данных текущего узла
        node = node->next; // Переход к следующему узлу
    }
}

int main() {
    struct Node *head = NULL; // Объявление указателей на узлы
    struct Node *second = NULL;
    struct Node *third = NULL;

    // Выделение памяти для узлов
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));

    head->data = 1; // Присвоение значений узлам
    head->next = second;

    second->data = 2;
    second->next = third;

    third->data = 3;
    third->next = NULL;

    printList(head); // Вызов функции для вывода списка

    // Освобождение памяти
    free(head);
    free(second);
    free(third);

    return 0; // Завершение функции main с кодом возврата 0
}
Следуя этому плану, новички смогут постепенно освоить основы языка C, начиная с базовых концепций и заканчивая более сложными темами, такими как динамическая память и структуры данных.
