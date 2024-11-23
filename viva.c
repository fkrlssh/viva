#include <stdio.h>
#include <conio.h> 
#include<string.h>
#include "screen.h"
#include "buffer.h"
#include "cursor.h"

#define MAX_LINES 100

int main() {
    enable_ansi_support();

    int rows, cols;
    get_console_size(&rows, &cols);

    clear_screen();

    const char *title = "Visual Text editor -- version 0.0.1";
    move_cursor(rows / 2, (cols - strlen(title)) / 2);
    printf("%s", title);

    set_reverse_video();
    move_cursor(rows - 2, 0);
    printf("[No Name] - 0 lines");
    reset_video();

    move_cursor(rows - 1, 0);
    printf("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");

    GapBuffer *gb = init_gap_buffer(100);
    CursorState cursor;
    init_cursor(&cursor, rows, cols);

    int c;
    update_cursor(&cursor);

    while (1) {
        c = _getch(); // 키 입력 받기 (Windows 전용)

        if (c == 17) { // Ctrl-Q로 종료
            break;
        } else if (c == '\b') { // Backspace
            if (cursor.cursor_position > 0) {
                delete_char(gb);
                cursor.cursor_position--;
                update_cursor(&cursor);
                printf(" ");
                update_cursor(&cursor);
            }
        } else if (c == '\r') { // Enter
            if (cursor.current_line < MAX_LINES && cursor.current_line < rows - 2) {
                cursor.current_line++;
                cursor.cursor_position = 0;
                update_cursor(&cursor);
            }
        } else if (c == 224) { // 특수 키 처리 (화살표 등)
            c = _getch(); // 두 번째 키 코드 읽기
            if (c == 72) { // ↑ 위쪽 화살표
                handle_arrow_key(&cursor, 'A');
            } else if (c == 80) { // ↓ 아래쪽 화살표
                handle_arrow_key(&cursor, 'B');
            } else if (c == 75) { // ← 왼쪽 화살표
                handle_arrow_key(&cursor, 'D');
            } else if (c == 77) { // → 오른쪽 화살표
                handle_arrow_key(&cursor, 'C');
            }
            update_cursor(&cursor);
        } else {
            insert_char(gb, c);
            printf("%c", c);
            cursor.cursor_position++;
            update_cursor(&cursor);
        }
    }

    free_gap_buffer(gb);
    return 0;
}
