.PHONY: clean, mrproper

.SUFFIXES:

CC = gcc
CFLAGS = -std=c99 -g -O0
EXEC = main

all: link

link: link.c set_link.c set_errno.c filter.c main.c
	$(CC) $^ -o $(EXEC)_link $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf *.bak rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)_*