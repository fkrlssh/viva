#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

// 갭 버퍼 초기화 함수
GapBuffer *init_gap_buffer(int size) {
    GapBuffer *gb = (GapBuffer *)malloc(sizeof(GapBuffer));
    gb->buffer = (char *)malloc(size * sizeof(char));
    gb->buffer_size = size;
    gb->gap_start = 0;
    gb->gap_end = size - 1;
    memset(gb->buffer, 0, size);
    return gb;
}

// 갭 버퍼에 문자 삽입
void insert_char(GapBuffer *gb, char c) {
    if (gb->gap_start == gb->gap_end) {
        // 갭이 꽉 찼으면 크기 확장
        int new_size = gb->buffer_size * 2;
        char *new_buffer = (char *)malloc(new_size * sizeof(char));
        int new_gap_end = new_size - (gb->buffer_size - gb->gap_end);

        // 기존 버퍼 복사
        memcpy(new_buffer, gb->buffer, gb->gap_start);
        memcpy(new_buffer + new_gap_end, gb->buffer + gb->gap_end, gb->buffer_size - gb->gap_end);

        // 기존 버퍼 해제
        free(gb->buffer);

        // 새로운 버퍼 설정
        gb->buffer = new_buffer;
        gb->gap_end = new_gap_end;
        gb->buffer_size = new_size;
    }

    // 문자 삽입
    gb->buffer[gb->gap_start++] = c;
}

// 갭 버퍼에서 문자 삭제
void delete_char(GapBuffer *gb) {
    if (gb->gap_start > 0) {
        gb->gap_start--;
    }
}

// 갭 이동 (커서 이동)
void move_gap(GapBuffer *gb, int new_position) {
    if (new_position < gb->gap_start) {
        // 갭을 왼쪽으로 이동
        while (gb->gap_start > new_position) {
            gb->buffer[--gb->gap_end] = gb->buffer[--gb->gap_start];
        }
    } else {
        // 갭을 오른쪽으로 이동
        while (gb->gap_start < new_position) {
            gb->buffer[gb->gap_start++] = gb->buffer[gb->gap_end++];
        }
    }
}

// 갭 버퍼 내용 출력
void print_gap_buffer(GapBuffer *gb) {
    for (int i = 0; i < gb->buffer_size; i++) {
        if (i >= gb->gap_start && i < gb->gap_end) {
            printf("_"); // 갭 표시
        } else {
            char c = gb->buffer[i];
            if (c != 0) { // NULL 문자는 출력하지 않음
                printf("%c", c);
            }
        }
    }
    printf("\n");
}

// 디버깅용 갭 버퍼 상태 출력
void debug_gap_buffer(GapBuffer *gb) {
    printf("Buffer size: %d\n", gb->buffer_size);
    printf("Gap start: %d\n", gb->gap_start);
    printf("Gap end: %d\n", gb->gap_end);
    printf("Buffer content: ");
    print_gap_buffer(gb);
}

// 갭 버퍼 해제
void free_gap_buffer(GapBuffer *gb) {
    free(gb->buffer);
    free(gb);
}
