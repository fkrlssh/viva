# 컴파일러와 플래그 설정
CC = gcc
CFLAGS = -Wall -g
TARGET = viva

# 오브젝트 파일
OBJS = viva.o editor.o buffer.o screen.o cursor.o data.o

# 기본 빌드 규칙
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 개별 파일 컴파일 규칙
viva.o: viva.c editor.h
	$(CC) $(CFLAGS) -c viva.c

editor.o: editor.c editor.h buffer.h cursor.h data.h screen.h
	$(CC) $(CFLAGS) -c editor.c

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

cursor.o: cursor.c cursor.h screen.h
	$(CC) $(CFLAGS) -c cursor.c

data.o: data.c data.h buffer.h
	$(CC) $(CFLAGS) -c data.c

# 정리 규칙
clean:
ifeq ($(OS),Windows_NT)
	del /f /q *.o $(TARGET).exe
else
	rm -f *.o $(TARGET)
endif
