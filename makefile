CC := gcc
CFLAGS := -Wall -g -lncurses

.PHONY: all

all: cpaint
	./cpaint

cpaint: cursepaint.o
	$(CC) $(CFLAGS) -o cpaint cursepaint.o	

cursepaint.o: cursepaint.c cursepaint.h
	$(CC) $(CFLAGS) -c cursepaint.c
