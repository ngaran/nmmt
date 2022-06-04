CC=gcc
CFLAGS=-Wall -Wextra
LDFLAGS=
SRC=src/test.c

all: *.o test

*.o: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

test: *.o
	$(CC) $(LDFLAGS) *.o -o test

clean:
	rm -f *.o test

.PHONY: all clean

