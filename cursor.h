#ifndef CURSOR_H
#define CURSOR_H

typedef struct {
    int current_line;
    int cursor_position;
    int max_lines;
    int max_cols;
} CursorState;

void init_cursor(CursorState *cursor, int max_lines, int max_cols);
void handle_arrow_key(CursorState *cursor, char direction, int max_lines);
void update_cursor(CursorState *cursor);

#endif // CURSOR_H
