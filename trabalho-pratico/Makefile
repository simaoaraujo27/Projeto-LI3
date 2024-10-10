CC=gcc
CFLAGS=-Iinclude
LDFLAGS=

all: main

main: src/main.o src/musics.o src/users.o src/artists.o
		$(CC) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c

src/musics.o: src/musics.c

src/users.o: src/users.c

src/artists.o: src/artists.c

clean:
		rm -f *.o main src/artists.o src/main.o src/musics.o src/users.o