#include <stdio.h>
#include<string.h>
#include "screen.h"
#include "buffer.h"

#define MAX_LINES 100 // 최대 줄 수

int main() {
    enable_ansi_support(); // ANSI 활성화

    // 콘솔 크기 가져오기
    int rows, cols;
    get_console_size(&rows, &cols);

    // 화면 초기화
    clear_screen();

    // 제목 출력
    const char *title = "Visual Text editor -- version 0.0.1";
    move_cursor(rows / 2, (cols - strlen(title)) / 2); // 화면 중앙
    printf("%s", title);

    // 상태 바 출력
    set_reverse_video();
    move_cursor(rows - 2, 0); // 하단 두 번째 줄
    printf("[No Name] - 0 lines");
    reset_video();

    // 도움말 바 출력
    move_cursor(rows - 1, 0); // 맨 마지막 줄
    printf("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");

    // 갭 버퍼 초기화
    GapBuffer *gb = init_gap_buffer(100);

    // 입력 처리 변수
    char c;
    int current_line = 1;      // 현재 줄 번호
    int cursor_position = 0;   // 현재 줄에서의 커서 위치

    move_cursor(current_line, 1); // 첫 번째 줄로 커서 이동

    while (1) {
        c = getchar(); // 사용자 입력 받기

        if (c == 17) { // Ctrl-Q로 종료
            break;
        } else if (c == '\b') { // 백스페이스로 삭제
            if (cursor_position > 0) {
                delete_char(gb);
                cursor_position--;
                move_cursor(current_line, cursor_position + 1); // 커서를 현재 위치로 이동
                printf(" "); // 이전 문자를 지움
                move_cursor(current_line, cursor_position + 1); // 커서를 다시 복원
            }
        } else if (c == '\n') { // 엔터 키로 줄 변경
            if (current_line < MAX_LINES && current_line < rows - 2) {
                current_line++;        // 줄 번호 증가
                cursor_position = 0;   // 줄 시작으로 커서 이동
                move_cursor(current_line, 1); // 다음 줄로 커서 이동
            }
        } else {
            insert_char(gb, c);        // 문자 삽입
            move_cursor(current_line, cursor_position + 1); // 커서를 현재 위치로 이동
            printf("%c", c);           // 입력 문자 출력
            cursor_position++;
        }
    }

    // 갭 버퍼 해제
    free_gap_buffer(gb);

    return 0;
}
