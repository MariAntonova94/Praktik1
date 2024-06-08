#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

// Задание констант для игры Pong
#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_LENGTH 3
#define BALL_START_X (FIELD_WIDTH / 2)
#define BALL_START_Y (FIELD_HEIGHT / 2)
#define WIN_SCORE 21

// Глобальные переменные для хранения состояния игры
int score_player1 = 0, score_player2 = 0;
int ball_x, ball_y, paddle1_y, paddle2_y;
int ball_dx = 1, ball_dy = 1;

// Инициализация окна ncurses
void init_ncurses() {
    initscr();              // Инициализация структуры данных ncurses
    cbreak();               // Ввод символов без буферизации
    noecho();               // Отключение вывода вводимых символов
    curs_set(FALSE);        // Скрытие курсора
    keypad(stdscr, TRUE);   // Включение обработки функциональных клавиш
    timeout(0);             // Неблокирующее чтение с клавиатуры
    ////
}

// Очистка окна и отображение рамки
void draw_border() {
    clear();                    // Очистка экрана
    border('|', '|', '-', '-', '+', '+', '+', '+'); // Отрисовка рамки
    refresh();                  // Обновление экрана
}

// Отображение ракеток и мяча
void draw_game() {
    mvprintw(paddle1_y, 1, "|");           // Отрисовка левой ракетки
    mvprintw(paddle1_y + 1, 1, "|");
    mvprintw(paddle1_y + 2, 1, "|");

    mvprintw(paddle2_y, FIELD_WIDTH - 2, "|");  // Отрисовка правой ракетки
    mvprintw(paddle2_y + 1, FIELD_WIDTH - 2, "|");
    mvprintw(paddle2_y + 2, FIELD_WIDTH - 2, "|");

    mvprintw(ball_y, ball_x, "O");          // Отрисовка мяча
    refresh();                              // Обновление экрана
}

// Обновление позиций мяча и ракеток
void update_game() {
    ball_x += ball_dx;                      // Обновление координат мяча
    ball_y += ball_dy;

    // Проверка столкновений мяча с верхней и нижней границами поля
    if (ball_y <= 0 || ball_y >= FIELD_HEIGHT - 1)
        ball_dy = -ball_dy;

    // Проверка столкновений мяча с ракетками
    if (ball_x == 2 && (ball_y >= paddle1_y && ball_y <= paddle1_y + PADDLE_LENGTH))
        ball_dx = -ball_dx;

    if (ball_x == FIELD_WIDTH - 3 && (ball_y >= paddle2_y && ball_y <= paddle2_y + PADDLE_LENGTH))
        ball_dx = -ball_dx;

    // Проверка забития головы
    if (ball_x <= 0) {
        score_player2++;
        ball_x = BALL_START_X;
        ball_y = BALL_START_Y;
    }

    if (ball_x >= FIELD_WIDTH - 1) {
        score_player1++;
        ball_x = BALL_START_X;
        ball_y = BALL_START_Y;
    }
}

// Основной цикл игры
void game_loop() {
    while (score_player1 < WIN_SCORE && score_player2 < WIN_SCORE) {
        draw_border();          // Отображение рамки
        draw_game();            // Отображение игровых элементов
        usleep(100000);         // Задержка для контроля скорости игры
        update_game();          // Обновление состояния игры

        // Обработка ввода с клавиатуры для движения ракеток
        int key = getch();
        switch (key) {
            case 'a':
                if (paddle1_y > 1) paddle1_y--;
                break;
            case 'z':
                if (paddle1_y < FIELD_HEIGHT - PADDLE_LENGTH - 1) paddle1_y++;
                break;
            case 'k':
                if (paddle2_y > 1) paddle2_y--;
                break;
            case 'm':
                if (paddle2_y < FIELD_HEIGHT - PADDLE_LENGTH - 1) paddle2_y++;
                break;
            case 'q':
                endwin();           // Завершение ncurses
                exit(EXIT_SUCCESS); // Выход из программы
                break;
        }
    }

    // Вывод поздравления с победой
    if (score_player1 >= WIN_SCORE)
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 10, "Player 1 wins!");
    else
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 10, "Player 2 wins!");
    
    mvprintw(FIELD_HEIGHT / 2 + 1, FIELD_WIDTH / 2 - 15, "Press 'q' to quit.");
    refresh();

    // Ожидание нажатия 'q' для завершения программы
    while (getch() != 'q') {}
    endwin();                   // Завершение ncurses
}

int main() {
    ball_x = BALL_START_X;      // Инициализация начальных координат мяча
    ball_y = BALL_START_Y;
    paddle1_y = FIELD_HEIGHT / 2 - PADDLE_LENGTH / 2; // Инициализация начальных координат ракеток
    paddle2_y = FIELD_HEIGHT / 2 - PADDLE_LENGTH / 2;

    init_ncurses();             // Инициализация ncurses
    game_loop();                // Запуск основного цикла игры

    return 0;
}
  
Подробное объяснение кода:
Инициализация ncurses (init_ncurses):

initscr(): Функция инициализирует экран для работы с ncurses. Она возвращает указатель на тип WINDOW, который используется для работы с экраном.
cbreak(), noecho(), curs_set(FALSE), keypad(stdscr, TRUE), timeout(0): Эти функции настраивают режим терминала для интерактивной игры: отключают буферизацию ввода, скрывают отображение вводимых символов, скрывают курсор, включают обработку функциональных клавиш и устанавливают неблокирующее чтение с клавиатуры.
Отображение игрового поля (draw_border и draw_game):

clear(): Очищает экран.
border(): Рисует рамку вокруг игрового поля.
mvprintw(): Печатает символы в указанном месте на экране.
Обновление состояния игры (update_game):

Обновляет позиции мяча (ball_x и ball_y) в зависимости от его текущего направления (ball_dx и ball_dy).
Проверяет столкновения мяча с границами поля и ракетками.
Обновляет счет игроков и возвращает мяч в центр поля при забитии головы.
Обработка ввода с клавиатуры (game_loop):

Основной цикл игры, который выполняется до тех пор, пока один из игроков не достигнет заданного счета (WIN_SCORE).
getch(): Читает символ с клавиатуры.
switch и case: Обрабатывают ввод пользователя для управления ракетками (`'a'













  Шаг 1: Инициализация и отрисовка игрового поля
c
Копировать код
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

// Задание констант для игры Pong
#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_LENGTH 3
#define BALL_START_X (FIELD_WIDTH / 2)
#define BALL_START_Y (FIELD_HEIGHT / 2)
#define WIN_SCORE 21

// Глобальные переменные для хранения состояния игры
int score_player1 = 0, score_player2 = 0;
int ball_x, ball_y, paddle1_y, paddle2_y;
int ball_dx = 1, ball_dy = 1;

// Инициализация окна ncurses
void init_ncurses() {
    initscr();              // Инициализация структуры данных ncurses
    cbreak();               // Ввод символов без буферизации
    noecho();               // Отключение вывода вводимых символов
    curs_set(FALSE);        // Скрытие курсора
    keypad(stdscr, TRUE);   // Включение обработки функциональных клавиш
    timeout(0);             // Неблокирующее чтение с клавиатуры
}

// Очистка окна и отображение рамки
void draw_border() {
    clear();                    // Очистка экрана
    border('|', '|', '-', '-', '+', '+', '+', '+'); // Отрисовка рамки
    refresh();                  // Обновление экрана
}

// Отображение ракеток и мяча
void draw_game() {
    mvprintw(paddle1_y, 1, "|");           // Отрисовка левой ракетки
    mvprintw(paddle1_y + 1, 1, "|");
    mvprintw(paddle1_y + 2, 1, "|");

    mvprintw(paddle2_y, FIELD_WIDTH - 2, "|");  // Отрисовка правой ракетки
    mvprintw(paddle2_y + 1, FIELD_WIDTH - 2, "|");
    mvprintw(paddle2_y + 2, FIELD_WIDTH - 2, "|");

    mvprintw(ball_y, ball_x, "O");          // Отрисовка мяча
    refresh();                              // Обновление экрана
}
Комментарии:

init_ncurses(): Функция инициализирует ncurses для работы с терминалом. Это включает ввод без буферизации, отключение отображения вводимых символов, скрытие курсора и настройку неблокирующего ввода с клавиатуры.

draw_border(): Функция отвечает за отрисовку рамки игрового поля с помощью функции border() из библиотеки ncurses. Она очищает экран, рисует рамку и обновляет его для отображения изменений.

draw_game(): Функция отображает игровые элементы: ракетки и мяч. Она использует mvprintw() для размещения символов на экране в указанных координатах.

Шаг 2: Обновление состояния игры и обработка ввода
c
Копировать код
// Обновление позиций мяча и ракеток
void update_game() {
    ball_x += ball_dx;                      // Обновление координат мяча
    ball_y += ball_dy;

    // Проверка столкновений мяча с верхней и нижней границами поля
    if (ball_y <= 0 || ball_y >= FIELD_HEIGHT - 1)
        ball_dy = -ball_dy;

    // Проверка столкновений мяча с ракетками
    if (ball_x == 2 && (ball_y >= paddle1_y && ball_y <= paddle1_y + PADDLE_LENGTH))
        ball_dx = -ball_dx;

    if (ball_x == FIELD_WIDTH - 3 && (ball_y >= paddle2_y && ball_y <= paddle2_y + PADDLE_LENGTH))
        ball_dx = -ball_dx;

    // Проверка забития головы
    if (ball_x <= 0) {
        score_player2++;
        ball_x = BALL_START_X;
        ball_y = BALL_START_Y;
    }

    if (ball_x >= FIELD_WIDTH - 1) {
        score_player1++;
        ball_x = BALL_START_X;
        ball_y = BALL_START_Y;
    }
}

// Основной цикл игры
void game_loop() {
    while (score_player1 < WIN_SCORE && score_player2 < WIN_SCORE) {
        draw_border();          // Отображение рамки
        draw_game();            // Отображение игровых элементов
        usleep(100000);         // Задержка для контроля скорости игры
        update_game();          // Обновление состояния игры

        // Обработка ввода с клавиатуры для движения ракеток
        int key = getch();
        switch (key) {
            case 'a':
                if (paddle1_y > 1) paddle1_y--;
                break;
            case 'z':
                if (paddle1_y < FIELD_HEIGHT - PADDLE_LENGTH - 1) paddle1_y++;
                break;
            case 'k':
                if (paddle2_y > 1) paddle2_y--;
                break;
            case 'm':
                if (paddle2_y < FIELD_HEIGHT - PADDLE_LENGTH - 1) paddle2_y++;
                break;
            case 'q':
                endwin();           // Завершение ncurses
                exit(EXIT_SUCCESS); // Выход из программы
                break;
        }
    }

    // Вывод поздравления с победой
    if (score_player1 >= WIN_SCORE)
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 10, "Player 1 wins!");
    else
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 10, "Player 2 wins!");
    
    mvprintw(FIELD_HEIGHT / 2 + 1, FIELD_WIDTH / 2 - 15, "Press 'q' to quit.");
    refresh();

    // Ожидание нажатия 'q' для завершения программы
    while (getch() != 'q') {}
    endwin();                   // Завершение ncurses
}

int main() {
    ball_x = BALL_START_X;      // Инициализация начальных координат мяча
    ball_y = BALL_START_Y;
    paddle1_y = FIELD_HEIGHT / 2 - PADDLE_LENGTH / 2; // Инициализация начальных координат ракеток
    paddle2_y = FIELD_HEIGHT / 2 - PADDLE_LENGTH / 2;

    init_ncurses();             // Инициализация ncurses
    game_loop();                // Запуск основного цикла игры

    return 0;
}
Комментарии:

update_game(): Функция обновляет координаты мяча и проверяет столкновения с границами поля и ракетками. Также она обрабатывает забитие голов и перезапуск мяча.

game_loop(): Основной игровой цикл, который продолжается до достижения одним из игроков победы (21 очко). В цикле вызываются функции для отрисовки, обновления состояния и обработки ввода с клавиатуры.

В main(): Инициализируются начальные координаты мяча и ракеток, запускается и завершается ncurses, запускается основной игровой цикл.

Почему так сделано:
Использование ncurses: Эта библиотека предоставляет удобные средства для работы с терминалом, позволяя реализовать символьную графику




































Для реализации игры Pong в интерактивном режиме через терминал с использованием библиотеки ncurses, давайте создадим файл src/pong_interactive.c и пошагово разберем, как он работает:

c
Копировать код
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

// Задание констант для игры Pong
#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define PADDLE_LENGTH 3
#define BALL_START_X (FIELD_WIDTH / 2)
#define BALL_START_Y (FIELD_HEIGHT / 2)
#define WIN_SCORE 21

// Глобальные переменные для хранения состояния игры
int score_player1 = 0, score_player2 = 0;
int ball_x, ball_y, paddle1_y, paddle2_y;
int ball_dx = 1, ball_dy = 1;

// Инициализация окна ncurses
void init_ncurses() {
    initscr();              // Инициализация структуры данных ncurses
    cbreak();               // Ввод символов без буферизации
    noecho();               // Отключение вывода вводимых символов
    curs_set(FALSE);        // Скрытие курсора
    keypad(stdscr, TRUE);   // Включение обработки функциональных клавиш
    timeout(0);             // Неблокирующее чтение с клавиатуры
}

// Очистка окна и отображение рамки
void draw_border() {
    clear();                    // Очистка экрана
    border('|', '|', '-', '-', '+', '+', '+', '+'); // Отрисовка рамки
    refresh();                  // Обновление экрана
}

// Отображение ракеток и мяча
void draw_game() {
    mvprintw(paddle1_y, 1, "|");           // Отрисовка левой ракетки
    mvprintw(paddle1_y + 1, 1, "|");
    mvprintw(paddle1_y + 2, 1, "|");

    mvprintw(paddle2_y, FIELD_WIDTH - 2, "|");  // Отрисовка правой ракетки
    mvprintw(paddle2_y + 1, FIELD_WIDTH - 2, "|");
    mvprintw(paddle2_y + 2, FIELD_WIDTH - 2, "|");

    mvprintw(ball_y, ball_x, "O");          // Отрисовка мяча
    refresh();                              // Обновление экрана
}

// Обновление позиций мяча и ракеток
void update_game() {
    ball_x += ball_dx;                      // Обновление координат мяча
    ball_y += ball_dy;

    // Проверка столкновений мяча с верхней и нижней границами поля
    if (ball_y <= 0 || ball_y >= FIELD_HEIGHT - 1)
        ball_dy = -ball_dy;

    // Проверка столкновений мяча с ракетками
    if (ball_x == 2 && (ball_y >= paddle1_y && ball_y <= paddle1_y + PADDLE_LENGTH))
        ball_dx = -ball_dx;

    if (ball_x == FIELD_WIDTH - 3 && (ball_y >= paddle2_y && ball_y <= paddle2_y + PADDLE_LENGTH))
        ball_dx = -ball_dx;

    // Проверка забития головы
    if (ball_x <= 0) {
        score_player2++;
        ball_x = BALL_START_X;
        ball_y = BALL_START_Y;
    }

    if (ball_x >= FIELD_WIDTH - 1) {
        score_player1++;
        ball_x = BALL_START_X;
        ball_y = BALL_START_Y;
    }
}

// Основной цикл игры
void game_loop() {
    while (score_player1 < WIN_SCORE && score_player2 < WIN_SCORE) {
        draw_border();          // Отображение рамки
        draw_game();            // Отображение игровых элементов
        usleep(100000);         // Задержка для контроля скорости игры
        update_game();          // Обновление состояния игры

        // Обработка ввода с клавиатуры для движения ракеток
        int key = getch();
        switch (key) {
            case 'a':
                if (paddle1_y > 1) paddle1_y--;
                break;
            case 'z':
                if (paddle1_y < FIELD_HEIGHT - PADDLE_LENGTH - 1) paddle1_y++;
                break;
            case 'k':
                if (paddle2_y > 1) paddle2_y--;
                break;
            case 'm':
                if (paddle2_y < FIELD_HEIGHT - PADDLE_LENGTH - 1) paddle2_y++;
                break;
            case 'q':
                endwin();           // Завершение ncurses
                exit(EXIT_SUCCESS); // Выход из программы
                break;
        }
    }

    // Вывод поздравления с победой
    if (score_player1 >= WIN_SCORE)
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 10, "Player 1 wins!");
    else
        mvprintw(FIELD_HEIGHT / 2, FIELD_WIDTH / 2 - 10, "Player 2 wins!");
    
    mvprintw(FIELD_HEIGHT / 2 + 1, FIELD_WIDTH / 2 - 15, "Press 'q' to quit.");
    refresh();

    // Ожидание нажатия 'q' для завершения программы
    while (getch() != 'q') {}
    endwin();                   // Завершение ncurses
}

int main() {
    ball_x = BALL_START_X;      // Инициализация начальных координат мяча
    ball_y = BALL_START_Y;
    paddle1_y = FIELD_HEIGHT / 2 - PADDLE_LENGTH / 2; // Инициализация начальных координат ракеток
    paddle2_y = FIELD_HEIGHT / 2 - PADDLE_LENGTH / 2;

    init_ncurses();             // Инициализация ncurses
    game_loop();                // Запуск основного цикла игры

    return 0;
}
Подробное объяснение кода:
Инициализация ncurses (init_ncurses):

initscr(): Инициализирует экран ncurses.
cbreak(), noecho(), curs_set(FALSE): Устанавливают неканонический режим ввода (без буферизации и без вывода вводимых символов, скрытие курсора).
keypad(stdscr, TRUE): Включает обработку функциональных клавиш (стрелки, F1-F12 и т.д.).
timeout(0): Устанавливает неблокирующее чтение с клавиатуры.
Отображение игрового поля (draw_border и draw_game):

clear(): Очищает экран.
border(): Рисует рамку игрового поля.
mvprintw(): Размещает символы на экране в указанных координатах.
refresh(): Обновляет экран для отображения изменений.
Обновление состояния игры (update_game):

ball_dx и ball_dy: Управляют скоростью движения мяча.
Проверяет столкновения мяча с границами поля и ракетками.
Обновляет счет и возвращает мяч в центр поля при забитии головы.
Основной цикл игры (game_loop):

Пока ни один из игроков не достигнет заданного счета (WIN_SCORE), игра продолжается.
Выводит текущее состояние игры на экран.
Читает ввод с клавиатуры для управления ракетками ('a' и 'z' для левой, 'k' и 'm' для правой).
Завершение игры (main):

Инициализирует начальные координаты мяча и ракеток.
Запускает основной