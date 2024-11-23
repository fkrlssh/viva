#ifndef SCREEN_H
#define SCREEN_H

// ANSI 활성화를 위한 상수 정의
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// ANSI 활성화 함수
void enable_ansi_support();

// 화면 조작 함수
void clear_screen();
void move_cursor(int row, int col);
void set_reverse_video();
void reset_video();

// 콘솔 크기 가져오기 함수
void get_console_size(int *rows, int *cols);

#endif // SCREEN_H
