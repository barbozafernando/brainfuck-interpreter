CC=gcc
CFLAGS = -Wall -Wextra -std=c11 -g
SRC=interpreter.c main.c
OBJ=interpreter.o main.o
TARGET=interpreter

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
