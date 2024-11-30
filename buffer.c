#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

GapBuffer *init_gap_buffer(int size) {
    GapBuffer *gb = malloc(sizeof(GapBuffer));
    if (gb == NULL) {
        fprintf(stderr, "Memory allocation failed for GapBuffer structure.\n");
        exit(EXIT_FAILURE);
    }

    gb->buffer = malloc(size * sizeof(char));
    if (gb->buffer == NULL) {
        fprintf(stderr, "Memory allocation failed for buffer.\n");
        free(gb);
        exit(EXIT_FAILURE);
    }

    gb->buffer_size = size;
    gb->gap_start = 0;
    gb->gap_end = size - 1;
    memset(gb->buffer, 0, size);

    return gb;
}

void insert_char(GapBuffer *gb, char c) {
    if (gb->gap_start == gb->gap_end) {
        int new_size = gb->buffer_size * 2;
        char *new_buffer = malloc(new_size * sizeof(char));
        if (new_buffer == NULL) {
            fprintf(stderr, "Memory allocation failed during buffer resizing.\n");
            exit(EXIT_FAILURE);
        }

        int new_gap_end = new_size - (gb->buffer_size - gb->gap_end);

        memcpy(new_buffer, gb->buffer, gb->gap_start);
        memcpy(new_buffer + new_gap_end, gb->buffer + gb->gap_end, gb->buffer_size - gb->gap_end);

        free(gb->buffer);
        gb->buffer = new_buffer;
        gb->gap_end = new_gap_end;
        gb->buffer_size = new_size;
    }

    gb->buffer[gb->gap_start++] = c;
}

void delete_char(GapBuffer *gb) {
    if (gb->gap_start > 0) {
        gb->gap_start--;
    }
}

void free_gap_buffer(GapBuffer *gb) {
    if (gb->buffer) {
        free(gb->buffer);
    }
    free(gb);
}
