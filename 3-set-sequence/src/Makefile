.PHONY: clean, mrproper

.SUFFIXES:

CC = gcc
CFLAGS = -std=c99 -g -O0
EXEC = main

all: bits link sentinel

bits: main.c set_bits.c set_errno.c
	$(CC) $^ -o $(EXEC)_bits $(CFLAGS) -DBITS

link: main.c link.c set_link.c set_errno.c
	$(CC) $^ -o $(EXEC)_link $(CFLAGS)

sentinel: main.c set_sentinel.c set_errno.c
	$(CC) $^ -o $(EXEC)_sentinel $(CFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf *.bak rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)_*