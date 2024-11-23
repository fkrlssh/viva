# 변수 선언
CC = gcc
CFLAGS = -Wall -g
TARGET = viva.exe
OBJS = viva.o buffer.o screen.o

# 기본 목표
all: $(TARGET)

# 실행 파일 생성
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 개별 파일 컴파일
viva.o: viva.c screen.h buffer.h
	$(CC) $(CFLAGS) -c viva.c

buffer.o: buffer.c buffer.h
	$(CC) $(CFLAGS) -c buffer.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

# 실행
run: $(TARGET)
	./$(TARGET)

# 정리
clean:
	del /f $(TARGET) $(OBJS)
