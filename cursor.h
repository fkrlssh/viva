#ifndef CURSOR_H
#define CURSOR_H

#include "screen.h" // move_cursor 함수 사용을 위해 포함

// 커서 상태 구조체
typedef struct {
    int current_line;      // 현재 줄 번호
    int cursor_position;   // 현재 줄에서의 커서 위치
    int max_lines;         // 최대 줄 수
    int max_cols;          // 최대 열 수
} CursorState;

// 커서 상태 초기화
void init_cursor(CursorState *cursor, int max_lines, int max_cols);

// 화살표 키 입력 처리 및 커서 이동
void handle_arrow_key(CursorState *cursor, char direction);

// 커서 상태를 기반으로 실제 터미널 커서 이동
void update_cursor(CursorState *cursor);

#endif // CURSOR_H
