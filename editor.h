#ifndef EDITOR_H
#define EDITOR_H

#include "buffer.h"
#include "cursor.h"

#ifdef _WIN32
    #define get_input() _getch()
#else
    int get_input();
#endif

typedef struct {
    GapBuffer *buffer;
    CursorState cursor;
    char file_name[256];
    int rows, cols;
    int scroll_offset;
} Editor;

void init_editor(Editor *editor);
void load_file(Editor *editor, const char *file_name);
int process_input(Editor *editor, int input);
void cleanup_editor(Editor *editor);
void draw_status_bar(Editor *editor);
void render_screen(Editor *editor);
void handle_input(Editor *editor, int width, int height);
void save_file(Editor *editor, const char *file_name);

#endif
