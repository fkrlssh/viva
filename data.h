#ifndef DATA_H
#define DATA_H

#include "buffer.h" // 갭 버퍼 사용

// 버퍼 내용을 파일에 저장
void save_buffer_to_file(const char *file_name, GapBuffer *gb);

// 버퍼 내용을 파일에서 로드
void load_buffer_from_file(const char *file_name, GapBuffer *gb);

#endif // DATA_H
