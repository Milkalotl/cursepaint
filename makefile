CC := gcc
CFLAGS := -Wall -g -lncurses

all: test
	./test

test: cursepaint.o
	$(CC) $(CFLAGS) -o test cursepaint.o	

cursepaint.o: cursepaint.c cursepaint.h
	$(CC) $(CFLAGS) -c cursepaint.c
