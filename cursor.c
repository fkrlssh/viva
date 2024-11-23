#include "cursor.h"
#include <stdio.h>

// 커서 상태 초기화
void init_cursor(CursorState *cursor, int max_lines, int max_cols) {
    cursor->current_line = 1;      // 초기 줄은 1
    cursor->cursor_position = 0;  // 초기 열은 0
    cursor->max_lines = max_lines;
    cursor->max_cols = max_cols;
}

// 화살표 키 입력 처리 및 커서 이동
void handle_arrow_key(CursorState *cursor, char direction) {
    if (direction == 'A') { // ↑ 위쪽 화살표
        if (cursor->current_line > 1) {
            cursor->current_line--;
        }
    } else if (direction == 'B') { // ↓ 아래쪽 화살표
        if (cursor->current_line < cursor->max_lines - 2) {
            cursor->current_line++;
        }
    } else if (direction == 'C') { // → 오른쪽 화살표
        if (cursor->cursor_position < cursor->max_cols - 1) {
            cursor->cursor_position++;
        }
    } else if (direction == 'D') { // ← 왼쪽 화살표
        if (cursor->cursor_position > 0) {
            cursor->cursor_position--;
        }
    }
}

// 커서 상태를 기반으로 실제 터미널 커서 이동
void update_cursor(CursorState *cursor) {
    move_cursor(cursor->current_line, cursor->cursor_position + 1);
}
