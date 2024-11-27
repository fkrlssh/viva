#ifndef BUFFER_H
#define BUFFER_H

typedef struct {
    char *buffer;
    int buffer_size;
    int gap_start;
    int gap_end;
} GapBuffer;

GapBuffer *init_gap_buffer(int size);
void insert_char(GapBuffer *gb, char c);
void delete_char(GapBuffer *gb);
void free_gap_buffer(GapBuffer *gb);

#endif // BUFFER_H
