#ifndef EDITOR_H
#define EDITOR_H

#include "buffer.h"
#include "cursor.h"

typedef struct {
    GapBuffer *buffer;
    CursorState cursor;
    char file_name[256];
    int rows, cols;
    int scroll_offset; // 현재 스크롤 오프셋
} Editor;

void init_editor(Editor *editor);
void load_file(Editor *editor, const char *file_name);
int process_input(Editor *editor, char input);
void cleanup_editor(Editor *editor);
void draw_status_bar(Editor *editor);
void render_screen(Editor *editor);
void save_file(Editor *editor); // 추가된 함수 선언

#endif // EDITOR_H
