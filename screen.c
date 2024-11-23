#include <stdio.h>
#include <windows.h>
#include "screen.h"

// ANSI 활성화 함수
void enable_ansi_support() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    if (hOut == INVALID_HANDLE_VALUE) return;

    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // ANSI 활성화
    SetConsoleMode(hOut, dwMode);
}

// 화면 지우기
void clear_screen() {
    printf("\033[2J"); // 화면 전체 지우기
    printf("\033[H");  // 커서를 홈 위치(0, 0)로 이동
}

// 커서 이동
void move_cursor(int row, int col) {
    printf("\033[%d;%dH", row, col); // 커서를 (row, col)로 이동
}

// 반전 색상 설정
void set_reverse_video() {
    printf("\033[7m"); // 반전 색상
}

// 색상 및 스타일 초기화
void reset_video() {
    printf("\033[0m"); // 색상 및 스타일 초기화
}

// 콘솔 크기 가져오기
void get_console_size(int *rows, int *cols) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1; // 너비
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // 높이
    } else {
        *cols = 80; // 기본값
        *rows = 24;
    }
}
