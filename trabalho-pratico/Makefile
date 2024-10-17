CC = gcc
CFLAGS = -Iinclude $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell pkg-config --libs glib-2.0)

all: main

main: src/main.o src/musics.o src/users.o src/artists.o
	$(CC) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

src/musics.o: src/musics.c
	$(CC) $(CFLAGS) -c $< -o $@

src/users.o: src/users.c
	$(CC) $(CFLAGS) -c $< -o $@

src/artists.o: src/artists.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o main src/artists.o src/main.o src/musics.o src/users.o
