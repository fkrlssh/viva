#ifndef BUFFER_H
#define BUFFER_H

// GapBuffer 구조체: 텍스트 에디터에서 효율적인 편집을 위해 갭 버퍼를 사용합니다.
typedef struct {
    char *buffer;      // 버퍼의 전체 데이터
    int buffer_size;   // 버퍼의 크기
    int gap_start;     // 갭 시작 위치
    int gap_end;       // 갭 끝 위치
} GapBuffer;

// GapBuffer를 초기화하는 함수 (특정 크기로 초기화)
GapBuffer *init_gap_buffer(int size);

// GapBuffer에 문자를 삽입하는 함수
void insert_char(GapBuffer *gb, char c);

// GapBuffer에서 문자를 삭제하는 함수
void delete_char(GapBuffer *gb);

// GapBuffer의 메모리를 해제하는 함수
void free_gap_buffer(GapBuffer *gb);

#endif // BUFFER_H
