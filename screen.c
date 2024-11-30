#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#define get_input() _getch()  // 윈도우에서는 _getch 사용
#else

#include <termios.h>
#include <unistd.h>

// 리눅스, 맥 환경에서 사용자 입력을 받기 위한 함수
int get_input() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#include "screen.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

void enable_ansi_support() {
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;

    if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    }
    #endif
}

void clear_screen() {
    printf("\033[2J\033[H"); 
}

void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row + 1, col + 1);
}

void set_reverse_video() {
    printf("\033[7m");
}

void reset_video() {
    printf("\033[0m"); 
}

void get_console_size(int *rows, int *cols) {
    #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        *cols = 80;
        *rows = 24;
    }
    #else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *cols = w.ws_col;
    *rows = w.ws_row;
    #endif
}
