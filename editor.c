#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <conio.h>
#define get_input() _getch()
#else
#include <termios.h>
#include <unistd.h>

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

#include "editor.h"
#include "buffer.h"
#include "cursor.h"
#include "data.h"
#include "screen.h"

void handle_save(Editor *editor) {
    char file_name[256];
    printf("\nEnter file name to save: ");
    fgets(file_name, 256, stdin);
    file_name[strcspn(file_name, "\n")] = '\0';

    if (strlen(file_name) > 0) {
        save_buffer_to_file(file_name, editor->buffer);
        printf("File saved: %s\n", file_name);
    } else {
        printf("Save cancelled.\n");
    }
}

void init_editor(Editor *editor) {
    enable_ansi_support();
    get_console_size(&editor->rows, &editor->cols);
    editor->buffer = init_gap_buffer(100);
    init_cursor(&editor->cursor, editor->rows, editor->cols);
    strcpy(editor->file_name, "[No Name]");
    clear_screen();
    draw_status_bar(editor);
}

void load_file(Editor *editor, const char *file_name) {
    strcpy(editor->file_name, file_name);
    load_buffer_from_file(file_name, editor->buffer);
    draw_status_bar(editor);
}

int process_input(Editor *editor, int input) {
    if (input == 17) { // Ctrl-Q: 종료
        return 1;
    } else if (input == 19) { // Ctrl-S: 저장
        handle_save(editor);
    } else if (input == '\b') { // 백스페이스
        if (editor->cursor.cursor_position > 0) {
            delete_char(editor->buffer);
            editor->cursor.cursor_position--;
            printf("\b \b");
        }
    } else if (input == '\r') { // Enter
        insert_char(editor->buffer, '\n');
        printf("\n");
        editor->cursor.current_line++;
        editor->cursor.cursor_position = 0;
    } else if (input == 27) { // 특수 키 처리 (Unix 계열에서는 ESC 시퀀스 사용)
        char arrow_key1 = get_input();
        char arrow_key2 = get_input();
        if (arrow_key1 == '[') {
            switch (arrow_key2) {
                case 'A': handle_arrow_key(&editor->cursor, 'A'); break; // ↑
                case 'B': handle_arrow_key(&editor->cursor, 'B'); break; // ↓
                case 'C': handle_arrow_key(&editor->cursor, 'C'); break; // →
                case 'D': handle_arrow_key(&editor->cursor, 'D'); break; // ←
            }
        }
    } else { // 일반 입력
        insert_char(editor->buffer, input);
        printf("%c", input);
        editor->cursor.cursor_position++;
    }

    update_cursor(&editor->cursor);
    return 0;
}

void cleanup_editor(Editor *editor) {
    free_gap_buffer(editor->buffer);
}

void draw_status_bar(Editor *editor) {
    set_reverse_video();
    move_cursor(editor->rows - 2, 0);
    printf("%s - %d lines", editor->file_name, editor->buffer->buffer_size);
    reset_video();

    move_cursor(editor->rows - 1, 0);
    printf("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");
}

void render_screen(Editor *editor) {
    clear_screen();
    draw_status_bar(editor);
}

