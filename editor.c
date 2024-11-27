#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "editor.h"
#include "buffer.h"
#include "cursor.h"
#include "data.h"
#include "screen.h"

void init_editor(Editor *editor) {
    enable_ansi_support();
    get_console_size(&editor->rows, &editor->cols);
    editor->buffer = init_gap_buffer(100);
    init_cursor(&editor->cursor, editor->rows, editor->cols);
    editor->scroll_offset = 0;
    strcpy(editor->file_name, "[No Name]");
    clear_screen();

    move_cursor(editor->rows / 2, (editor->cols - 28) / 2);
    printf("Visual Text Editor -- version 0.0.1");

    draw_status_bar(editor);
}

void draw_status_bar(Editor *editor) {
    set_reverse_video();
    move_cursor(editor->rows - 2, 0);
    printf("%-*s", editor->cols, "");
    move_cursor(editor->rows - 1, 0);
    printf("%-*s", editor->cols, "");

    move_cursor(editor->rows - 2, 0);
    printf("%s - %d lines", editor->file_name, editor->buffer->buffer_size);

    move_cursor(editor->rows - 1, 0);
    printf("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");
    reset_video();
}

void render_screen(Editor *editor) {
    int visible_lines = editor->rows - 3;
    int start_line = editor->scroll_offset;
    int line = 0;

    move_cursor(0, 0);

    for (int i = 0; i < editor->buffer->buffer_size; i++) {
        if (line >= start_line && line < start_line + visible_lines) {
            if (editor->buffer->buffer[i] == '\n') {
                line++;
                printf("\n");
            } else if (editor->buffer->buffer[i] != '\0') {
                putchar(editor->buffer->buffer[i]);
            }
        } else if (line >= start_line + visible_lines) {
            break;
        }
    }

    draw_status_bar(editor);
    update_cursor(&editor->cursor);
}

int process_input(Editor *editor, char input) {
    if (input == 17) { // Ctrl-Q: 종료
        return 1;
    } else if (input == 19) { // Ctrl-S: 저장
        save_file(editor);
        return 0; // 출력 없이 저장만 수행
    } else if (input == '\b') { // 백스페이스
        if (editor->cursor.cursor_position > 0) {
            delete_char(editor->buffer);
            editor->cursor.cursor_position--;
        }
    } else if (input == '\r') { // 줄바꿈
        insert_char(editor->buffer, '\n');
        editor->cursor.current_line++;
        editor->cursor.cursor_position = 0;

        if (editor->cursor.current_line >= editor->scroll_offset + (editor->rows - 3)) {
            editor->scroll_offset++;
        }
    } else if (input == 224 || input == 0) { // 특수 키 처리
        char arrow_key = _getch();
        handle_arrow_key(&editor->cursor, arrow_key, editor->rows - 2);
        if (editor->cursor.current_line < editor->scroll_offset) {
            editor->scroll_offset--;
        } else if (editor->cursor.current_line >= editor->scroll_offset + (editor->rows - 3)) {
            editor->scroll_offset++;
        }
    } else { // 일반 입력
        insert_char(editor->buffer, input);
        editor->cursor.cursor_position++;

        if (editor->cursor.current_line >= editor->scroll_offset + (editor->rows - 3)) {
            editor->scroll_offset++;
        }
    }

    render_screen(editor); // 입력 처리 후 화면 갱신
    return 0;
}


void load_file(Editor *editor, const char *file_name) {
    strcpy(editor->file_name, file_name);
    load_buffer_from_file(file_name, editor->buffer);
    render_screen(editor);
}


void cleanup_editor(Editor *editor) {
    free_gap_buffer(editor->buffer);
}


void save_file(Editor *editor) {
    if (strcmp(editor->file_name, "[No Name]") == 0) {
        char new_file_name[256];
        printf("Enter file name to save: ");
        fgets(new_file_name, 256, stdin);
        new_file_name[strcspn(new_file_name, "\n")] = '\0'; // 줄바꿈 제거
        strcpy(editor->file_name, new_file_name);
    }

    save_buffer_to_file(editor->file_name, editor->buffer);

    // 상태바에 저장 메시지 표시
    draw_status_bar(editor);
    move_cursor(editor->rows - 2, 0);
    printf("File saved: %s", editor->file_name);
}