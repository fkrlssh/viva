#ifndef SCREEN_H
#define SCREEN_H

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void enable_ansi_support();
void clear_screen();
void move_cursor(int row, int col);
void set_reverse_video();
void reset_video();
void get_console_size(int *rows, int *cols);

#endif // SCREEN_H
