#include <stdio.h>       // Включение стандартной библиотеки ввода-вывода
#include <stdlib.h>      // Включение стандартной библиотеки для функций работы с памятью, процессов и т.д.
#include <unistd.h>      // Включение стандартной библиотеки для работы с POSIX API
#include <termios.h>     // Включение библиотеки для управления режимами терминала
#include <sys/select.h>  // Включение библиотеки для функций мультиплексирования ввода-вывода

// Определение размеров игрового поля и ракеток
#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define ROCKET_HEIGHT 3
#define WINSCORE 21
#define ROCKET1_X 2                // Позиция первой ракетки по X (левая сторона)
#define ROCKET2_X (FIELD_WIDTH - 3) // Позиция второй ракетки по X (правая сторона)
#define BALL_START_X (FIELD_WIDTH / 2) // Начальная позиция мяча по X
#define BALL_START_Y (FIELD_HEIGHT / 2) // Начальная позиция мяча по Y

// Объявление глобальных переменных
char move;              // Переменная для хранения последнего нажатого символа
int sc, ball_coord_x, ball_coord_y, rocket_coord1, rocket_coord2, vector_x, vector_y; // Координаты и векторы движения мяча и ракеток
int score_player1 = 0;  // Счет игрока 1
int score_player2 = 0;  // Счет игрока 2

struct termios orig_termios; // Структура для хранения исходных настроек терминала

// Прототипы функций
void first_player_move();     // Функция для обработки хода первого игрока
void second_player_move();    // Функция для обработки хода второго игрока
void ball_position();         // Функция для обработки движения мяча
void draw_field();            // Функция для отрисовки игрового поля
void reset_terminal_mode();   // Функция для восстановления исходных настроек терминала
void set_conio_terminal_mode(); // Функция для установки неканонического режима терминала
int kbhit();                  // Функция для проверки нажатия клавиши
char getch();                 // Функция для чтения символа с клавиатуры

// Основная функция
int main(void) {
    // Начальные позиции ракеток и мяча
    rocket_coord1 = FIELD_HEIGHT / 2 - ROCKET_HEIGHT / 2; // Центрирование первой ракетки
    rocket_coord2 = FIELD_HEIGHT / 2 - ROCKET_HEIGHT / 2; // Центрирование второй ракетки
    ball_coord_x = BALL_START_X; // Центрирование мяча по X
    ball_coord_y = BALL_START_Y; // Центрирование мяча по Y
    vector_x = 1; // начальное направление мяча по горизонтали (вправо)
    vector_y = 1; // начальное направление мяча по вертикали (вниз)

    set_conio_terminal_mode(); // Установка неканонического режима терминала для ввода с клавиатуры

    // Главный игровой цикл
    while (score_player1 < WINSCORE && score_player2 < WINSCORE) {
        draw_field(); // Отрисовка игрового поля
        if (kbhit()) { // Проверка, была ли нажата клавиша
            move = getch(); // Чтение нажатой клавиши
            first_player_move(); // Обработка хода первого игрока
            second_player_move(); // Обработка хода второго игрока
        }
        ball_position(); // Обработка движения мяча
        usleep(100000); // Задержка для замедления игры (0.1 секунды)
    }

    printf("\033[2J\033[H"); // Очистка экрана
    if (score_player1 == WINSCORE) { // Проверка, выиграл ли первый игрок
        printf("Player 1 wins!\n");
    } else { // Иначе выиграл второй игрок
        printf("Player 2 wins!\n");
    }

    reset_terminal_mode(); // Восстановление исходных настроек терминала
    return 0;
}

// Функция для обработки хода первого игрока
void first_player_move() {
    // Перемещение первой ракетки вверх
    if (move == 'a' && rocket_coord1 > 0) {
        rocket_coord1--;
    // Перемещение первой ракетки вниз
    } else if (move == 'z' && rocket_coord1 < FIELD_HEIGHT - ROCKET_HEIGHT) {
        rocket_coord1++;
    }
}

// Функция для обработки хода второго игрока
void second_player_move() {
    // Перемещение второй ракетки вверх
    if (move == 'k' && rocket_coord2 > 0) {
        rocket_coord2--;
    // Перемещение второй ракетки вниз
    } else if (move == 'm' && rocket_coord2 < FIELD_HEIGHT - ROCKET_HEIGHT) {
        rocket_coord2++;
    }
}

// Функция для обработки движения мяча
void ball_position() {
    // Проверка на попадание в верхнюю или нижнюю границу поля
    if (ball_coord_y <= 0 || ball_coord_y >= FIELD_HEIGHT - 1) {
        vector_y = -vector_y; // Изменение направления по вертикали
    }
    
    // Проверка на попадание в ракетку первого игрока
    if (ball_coord_x == ROCKET1_X + 1 && ball_coord_y >= rocket_coord1 && ball_coord_y < rocket_coord1 + ROCKET_HEIGHT) {
        vector_x = -vector_x; // Изменение направления по горизонтали
    }
    
    // Проверка на попадание в ракетку второго игрока
    if (ball_coord_x == ROCKET2_X - 1 && ball_coord_y >= rocket_coord2 && ball_coord_y < rocket_coord2 + ROCKET_HEIGHT) {
        vector_x = -vector_x; // Изменение направления по горизонтали
    }
    
    // Проверка на пропуск ракетки и увеличение счета
    if (ball_coord_x <= 0) {
        score_player2++; // Увеличение счета второго игрока
        ball_coord_x = BALL_START_X; // Возврат мяча в центр
        ball_coord_y = BALL_START_Y;
        vector_x = 1; // Смена направления
        vector_y = 1;
    } else if (ball_coord_x >= FIELD_WIDTH - 1) {
        score_player1++; // Увеличение счета первого игрока
        ball_coord_x = BALL_START_X; // Возврат мяча в центр
        ball_coord_y = BALL_START_Y;
        vector_x = -1; // Смена направления
        vector_y = 1;
    } else {
        ball_coord_x += vector_x; // Перемещение мяча по X
        ball_coord_y += vector_y; // Перемещение мяча по Y
    }
}

// Функция для отрисовки игрового поля
void draw_field() {
    printf("\033[2J\033[H"); // Очистка экрана

    // Проход по всем координатам поля
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // Рисование верхней и нижней границы
            if (y == 0 || y == FIELD_HEIGHT - 1) {
                putchar('-'); // верхняя и нижняя границы
            } else if (x == 0 || x == FIELD_WIDTH - 1) {
                putchar('|'); // левая и правая границы
            } 
            // Рисование ракеток
            else if ((x == ROCKET1_X && y >= rocket_coord1 && y < rocket_coord1 + ROCKET_HEIGHT) ||
                (x == ROCKET2_X && y >= rocket_coord2 && y < rocket_coord2 + ROCKET_HEIGHT)) {
                putchar('|');
            } 
            // Рисование мяча
            else if (x == ball_coord_x && y == ball_coord_y) {
                putchar('O');
            } 
            // Рисование центральной линии
            else if (x == FIELD_WIDTH / 2) {
                putchar('|');
            } else {
                putchar(' ');
            }
        }
        putchar('\n'); // Перевод строки после каждого ряда
    }
    // Вывод счета игроков
    printf("Score: Player 1 - %d | Player 2 - %d\n", score_player1, score_player2);
}

// Настройки терминала для неканонического режима
void reset_terminal_mode() {
    tcsetattr(0, TCSANOW, &orig_termios); // Восстановление исходных настроек терминала
}

void set_conio_terminal_mode() {
    struct termios new_termios;

    // копирование текущих настроек терминала для изменения и последующего восстановления
    tcgetattr(0, &orig_termios);
    new_termios = orig_termios;

    // регистрация функции для восстановления настроек терминала при выходе
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios); // Установка терминала в неканонический режим
    tcsetattr(0, TCSANOW, &new_termios); // Применение новых настроек терминала
}

// Проверка наличия нажатия клавиши
int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds); // Очистка набора дескрипторов
    FD_SET(0, &fds); // Добавление стандартного ввода в набор дескрипторов
    return select(1, &fds, NULL, NULL, &tv); // Проверка состояния дескрипторов
}

// Чтение символа с клавиатуры
char getch() {
    char buf = 0;
    if (read(0, &buf, 1) < 0) { // Чтение одного символа из стандартного ввода
        perror("read()"); // Вывод ошибки при неудачном чтении
        exit(EXIT_FAILURE); // Завершение программы с ошибкой
    }
    return buf; // Возврат прочитанного символа
}
