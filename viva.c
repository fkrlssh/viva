#include <stdio.h>
#include <conio.h>
#include "editor.h"
#include "screen.h"

int main(int argc, char *argv[]) {
    Editor editor;
    init_editor(&editor);

    if (argc > 1) {
        load_file(&editor, argv[1]);
    }

    while (1) {
        char c = _getch();
        if (process_input(&editor, c)) break;
    }

    cleanup_editor(&editor);
    return 0;
}
