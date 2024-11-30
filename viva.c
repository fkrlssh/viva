#include <stdio.h>
#include <string.h>
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    int getch(void) {
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
#include "screen.h"

int main(int argc, char *argv[]) {
    Editor editor;
    init_editor(&editor);

    if (argc > 1) {
        load_file(&editor, argv[1]);
    }

    while (1) {
        int c;
        #ifdef _WIN32
            c = _getch(); 
        #else
            c = getch(); 
        #endif

        if (process_input(&editor, c)) break;
    }

    cleanup_editor(&editor);
    return 0;
}
