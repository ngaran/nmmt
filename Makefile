CC=gcc
CFLAGS=# -Wall -Wextra
LDFLAGS=-lz
SRC=src/test.c src/type.h src/save.h src/save.c

all: *.o nmmt

*.o: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

nmmt: *.o
	$(CC) $(LDFLAGS) *.o -o nmmt

install: nmmt
	cp nmmt /usr/bin

uninstall: /usr/bin/nmmt
	rm nmmt /usr/bin

clean:
	rm -f *.o nmmt

.PHONY: all clean

