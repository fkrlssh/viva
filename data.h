#ifndef DATA_H
#define DATA_H

#include "buffer.h"

void save_buffer_to_file(const char *file_name, GapBuffer *gb);
void load_buffer_from_file(const char *file_name, GapBuffer *gb);

#endif // DATA_H
