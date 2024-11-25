#include <stdio.h>
#include <string.h>
#include <conio.h>  // Windows 키 입력 처리
#include "screen.h"
#include "data.h"
#include "cursor.h"

#define MAX_LINES 100

void prompt_file_name(char *file_name) {
    move_cursor(25, 0); // 메시지 표시 위치
    printf("Enter file name: ");
    fgets(file_name, 256, stdin);
    file_name[strcspn(file_name, "\n")] = '\0'; // 줄 바꿈 제거
    clear_screen();
}

int main(int argc, char *argv[]) {
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

    char c;
    char file_name[256] = "[No Name]";
    update_cursor(&cursor);

    // 초기 파일 로드 또는 새 파일 생성
    if (argc > 1) {
        load_buffer_from_file(argv[1], gb);
        strcpy(file_name, argv[1]);
    }

    while (1) {
        c = _getch();

        if (c == 17) { // Ctrl-Q로 종료
            break;
        } else if (c == '\b') {
            if (cursor.cursor_position > 0) {
                delete_char(gb);
                cursor.cursor_position--;
                update_cursor(&cursor);
                printf(" ");
                update_cursor(&cursor);
            }
        } else if (c == '\r') {
            cursor.current_line++;
            cursor.cursor_position = 0;
            update_cursor(&cursor);
        } else if (c == 224) {
            c = _getch();
            if (c == 72) handle_arrow_key(&cursor, 'A'); // ↑
            if (c == 80) handle_arrow_key(&cursor, 'B'); // ↓
            if (c == 75) handle_arrow_key(&cursor, 'D'); // ←
            if (c == 77) handle_arrow_key(&cursor, 'C'); // →
            update_cursor(&cursor);
        } else if (c == 19) { // Ctrl-S: 저장
            if (strcmp(file_name, "[No Name]") == 0) {
                // 파일 이름이 없으면 사용자에게 요청
                prompt_file_name(file_name);
            }
            save_buffer_to_file(file_name, gb);
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
