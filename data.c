#include <stdio.h>
#include <string.h>
#include "data.h"

// 버퍼 내용을 파일에 저장
void save_buffer_to_file(const char *file_name, GapBuffer *gb) {
    FILE *file = fopen(file_name, "w");
    if (!file) {
        printf("Error: Cannot save file %s\n", file_name);
        return;
    }

    for (int i = 0; i < gb->buffer_size; i++) {
        if (i < gb->gap_start || i >= gb->gap_end) {
            fputc(gb->buffer[i], file);
        }
    }
    fclose(file);
    printf("File saved: %s\n", file_name);
}

// 버퍼 내용을 파일에서 로드
void load_buffer_from_file(const char *file_name, GapBuffer *gb) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Error: Cannot open file %s\n", file_name);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        for (int i = 0; line[i] != '\0'; i++) {
            insert_char(gb, line[i]);
        }
    }
    fclose(file);
    printf("File loaded: %s\n", file_name);
}
