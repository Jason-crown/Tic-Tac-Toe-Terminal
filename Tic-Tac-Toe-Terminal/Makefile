CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic
TARGET = tic
OBJ = main.o stage.o input.o logic.o color.o initialize.o
EXE = tic.exe

ifeq ($(OS), Windows_NT)
	DELETE = del
else 
	DELETE = rm -f
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c tic.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(DELETE) $(OBJ) $(TARGET) 
ifeq ($(OS), Windows_NT)	
	$(DELETE) $(EXE)
endif

.PHONY: 
	all clean

run: $(TARGET)
	./$(TARGET)