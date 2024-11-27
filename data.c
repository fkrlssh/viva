#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "buffer.h"

void save_buffer_to_file(const char *file_name, GapBuffer *gb) {
    FILE *file = fopen(file_name, "w");
    if (!file) {
        printf("Error: Cannot save file %s\n", file_name);
        return;
    }

    for (int i = 0; i < gb->gap_start; i++) {
        fputc(gb->buffer[i], file);
    }
    for (int i = gb->gap_end; i < gb->buffer_size; i++) {
        fputc(gb->buffer[i], file);
    }

    fclose(file);
    printf("File saved: %s\n", file_name);
}

void load_buffer_from_file(const char *file_name, GapBuffer *gb) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", file_name);
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        insert_char(gb, ch);
    }

    fclose(file);
    printf("File loaded: %s\n", file_name);
}
