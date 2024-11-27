#include <stdio.h>
#ifdef _WIN32
#include <conio.h> // Windows 키 입력 처리
#else
#include <termios.h>
#include <unistd.h>
#endif
#include "editor.h"
#include "screen.h"

#ifdef _WIN32
char get_input() {
    return _getch();
}
#else
char get_input() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);            // 현재 터미널 설정 읽기
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);          // CANONICAL 모드 및 ECHO 끄기
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);   // 새 설정 적용
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);   // 원래 설정 복구
    return ch;
}
#endif

int main(int argc, char *argv[]) {
    Editor editor;
    init_editor(&editor);

    if (argc > 1) {
        load_file(&editor, argv[1]);
    }

    while (1) {
        char c = get_input();
        if (process_input(&editor, c)) break;
    }

    cleanup_editor(&editor);
    return 0;
}
