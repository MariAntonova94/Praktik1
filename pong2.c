#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define ROCKET_HEIGHT 3
#define WINSCORE 21
#define ROCKET1_X 2
#define ROCKET2_X (FIELD_WIDTH - 3)
#define BALL_START_X (FIELD_WIDTH / 2)
#define BALL_START_Y (FIELD_HEIGHT / 2)

char move;
int sc, ball_coord_x, ball_coord_y, rocket_coord1, rocket_coord2, vector_x, vector_y;
int score_player1 = 0;
int score_player2 = 0;

struct termios orig_termios;

void first_player_move();
void second_player_move();
void ball_position();
void draw_field();
void reset_terminal_mode();
void set_conio_terminal_mode();
int kbhit();
char getch();

int main(void) {
    rocket_coord1 = FIELD_HEIGHT / 2 - ROCKET_HEIGHT / 2;
    rocket_coord2 = FIELD_HEIGHT / 2 - ROCKET_HEIGHT / 2;
    ball_coord_x = BALL_START_X;
    ball_coord_y = BALL_START_Y;
    vector_x = 1; // начальное направление мяча по горизонтали
    vector_y = 1; // начальное направление мяча по вертикали

    set_conio_terminal_mode();

    while (score_player1 < WINSCORE && score_player2 < WINSCORE) {
        draw_field();
        if (kbhit()) {
            move = getch();
            first_player_move();
            second_player_move();
        }
        ball_position();
        usleep(100000); // задержка для замедления игры
    }

    printf("\033[2J\033[H"); // очистка экрана
    if (score_player1 == WINSCORE) {
        printf("Player 1 wins!\n");
    } else {
        printf("Player 2 wins!\n");
    }

    reset_terminal_mode();
    return 0;
}

// Ход первого игрока
void first_player_move() {
    if (move == 'a' && rocket_coord1 > 0) {
        rocket_coord1--;
    } else if (move == 'z' && rocket_coord1 < FIELD_HEIGHT - ROCKET_HEIGHT) {
        rocket_coord1++;
    }
}

// Ход второго игрока
void second_player_move() {
    if (move == 'k' && rocket_coord2 > 0) {
        rocket_coord2--;
    } else if (move == 'm' && rocket_coord2 < FIELD_HEIGHT - ROCKET_HEIGHT) {
        rocket_coord2++;
    }
}

// Движение мяча
void ball_position() {
    // Проверка на попадание в горизонтальную стену
    if (ball_coord_y <= 0 || ball_coord_y >= FIELD_HEIGHT - 1) {
        vector_y = -vector_y;
    }
    
    // Проверка на попадание в ракетку первого игрока
    if (ball_coord_x == ROCKET1_X + 1 && ball_coord_y >= rocket_coord1 && ball_coord_y < rocket_coord1 + ROCKET_HEIGHT) {
        vector_x = -vector_x;
    }
    
    // Проверка на попадание в ракетку второго игрока
    if (ball_coord_x == ROCKET2_X - 1 && ball_coord_y >= rocket_coord2 && ball_coord_y < rocket_coord2 + ROCKET_HEIGHT) {
        vector_x = -vector_x;
    }
    
    // Проверка на пропуск ракетки
    if (ball_coord_x <= 0) {
        score_player2++;
        ball_coord_x = BALL_START_X;
        ball_coord_y = BALL_START_Y;
        vector_x = 1;
        vector_y = 1;
    } else if (ball_coord_x >= FIELD_WIDTH - 1) {
        score_player1++;
        ball_coord_x = BALL_START_X;
        ball_coord_y = BALL_START_Y;
        vector_x = -1;
        vector_y = 1;
    } else {
        ball_coord_x += vector_x;
        ball_coord_y += vector_y;
    }
}

// Рисование игрового поля
void draw_field() {
    printf("\033[2J\033[H"); // очистка экрана

    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // Рисование рамки
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
        putchar('\n');
    }
    // Вывод счета игроков
    printf("Score: Player 1 - %d | Player 2 - %d\n", score_player1, score_player2);
}

// Настройки терминала для неканонического режима
void reset_terminal_mode() {
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode() {
    struct termios new_termios;

    // копирование текущих настроек терминала для изменения и последующего восстановления
    tcgetattr(0, &orig_termios);
    new_termios = orig_termios;

    // регистрация функции для восстановления настроек терминала при выходе
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

// Проверка наличия нажатия клавиши
int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

// Чтение символа с клавиатуры
char getch() {
    char buf = 0;
    if (read(0, &buf, 1) < 0) {
        perror("read()");
        exit(EXIT_FAILURE);
    }
    return buf;
}


// Обработчики терминала:

// set_conio_terminal_mode и reset_terminal_mode управляют режимом терминала для удобного ввода с клавиатуры.
// Обработка ввода с клавиатуры:

// kbhit проверяет наличие нажатия клавиши.
// getch читает символ с клавиатуры.