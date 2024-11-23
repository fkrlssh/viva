#ifndef BUFFER_H
#define BUFFER_H

// 갭 버퍼 구조체 정의
typedef struct {
    char *buffer;        // 전체 버퍼
    int buffer_size;     // 버퍼 크기
    int gap_start;       // 갭 시작 인덱스
    int gap_end;         // 갭 끝 인덱스
} GapBuffer;

// 갭 버퍼 함수 선언
GapBuffer *init_gap_buffer(int size);     // 갭 버퍼 초기화
void insert_char(GapBuffer *gb, char c); // 문자 삽입
void delete_char(GapBuffer *gb);         // 문자 삭제
void move_gap(GapBuffer *gb, int new_position); // 갭 이동
void print_gap_buffer(GapBuffer *gb);    // 갭 버퍼 내용 출력
void debug_gap_buffer(GapBuffer *gb);    // 디버깅용 버퍼 상태 출력
void free_gap_buffer(GapBuffer *gb);     // 갭 버퍼 해제

#endif // BUFFER_H
