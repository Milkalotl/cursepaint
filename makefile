CC := gcc
CFLAGS := -Wall -g -lncurses

.PHONY: all

all: cpaint
	./cpaint

cpaint: cursepaint.o fileio.o setup.o
	$(CC) -o cpaint setup.o cursepaint.o fileio.o $(CFLAGS)

cursepaint.o: cursepaint.c cursepaint.h
	$(CC)  -c cursepaint.c $(CFLAGS)
fileio.o: fileio.c fileio.h
	$(CC)  -c fileio.c $(CFLAGS)

setup.o: setup.c setup.h
	$(CC)  -c setup.c $(CFLAGS)



clean:
	rm *.o
	rm cpaint
	echo all done!!
