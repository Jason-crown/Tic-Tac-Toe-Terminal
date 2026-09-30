CC = gcc
CFLAGS = -std=c99 -Wextra -pedantic -Wall
TARGET = tic
OBJ = main.o stage.o input.o logic.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

%.o: %.c tic.h
	$(CC) $(CFLAGS) -c $<

clean:
	del $(OBJ) $(TARGET)

.PHONY: 
	all clean

run: $(TARGET)
	./$(TARGET)