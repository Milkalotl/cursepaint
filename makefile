CC := gcc
CFLAGS := -Wall -g -lncurses

.PHONY: all

all: cpaint
	./cpaint

cpaint: cursepaint.o fileio.o
	$(CC) $(CFLAGS) -o cpaint cursepaint.o fileio.o

cursepaint.o: cursepaint.c cursepaint.h
	$(CC) $(CFLAGS) -c cursepaint.c
fileio.o: fileio.c fileio.h
	$(CC) $(CFLAGS) -c fileio.c


boobies.o: boobies.c
	echo boobies
