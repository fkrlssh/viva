#include "cursor.h"
#include "screen.h"

void init_cursor(CursorState *cursor, int max_lines, int max_cols) {
    cursor->current_line = 0;
    cursor->cursor_position = 0;
    cursor->max_lines = max_lines;
    cursor->max_cols = max_cols;
}

void handle_arrow_key(CursorState *cursor, char direction) {
    switch (direction) {
        case 'A': // ↑
            if (cursor->current_line > 0) {
                cursor->current_line--;
            }
            break;
        case 'B': // ↓
            if (cursor->current_line < cursor->max_lines - 3) {
                cursor->current_line++;
            }
            break;
        case 'C': // →
            if (cursor->cursor_position < cursor->max_cols - 1) {
                cursor->cursor_position++;
            }
            break;
        case 'D': // ←
            if (cursor->cursor_position > 0) {
                cursor->cursor_position--;
            }
            break;
    }
}

void update_cursor(CursorState *cursor) {
    move_cursor(cursor->current_line, cursor->cursor_position + 1);
}
