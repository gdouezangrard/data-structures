.PHONY: clean, mrproper

.SUFFIXES:

CC = gcc
CFLAGS = -std=c99 -g -O0
EXEC = main

all: main.c
	$(CC) $^ -o $(EXEC) $(CFLAGS)
	./main

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf *.bak rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)