CC = gcc
CFLAGS = -Iinclude $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell pkg-config --libs glib-2.0)

all: programa-principal

programa-principal: src/main.o src/musics.o src/users.o src/artists.o src/validation.o src/queries.o src/utils.o src/gestor_artists.o
	$(CC) $^ $(LDFLAGS) -o $@

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

src/musics.o: src/musics.c
	$(CC) $(CFLAGS) -c $< -o $@

src/users.o: src/users.c
	$(CC) $(CFLAGS) -c $< -o $@

src/artists.o: src/artists.c
	$(CC) $(CFLAGS) -c $< -o $@

src/validation.o: src/validation.c
	$(CC) $(CFLAGS) -c $< -o $@

src/queries.o: src/queries.c
	$(CC) $(CFLAGS) -c $< -o $@

src/utils.o: src/utils.c
	$(CC) $(CFLAGS) -c $< -o $@

src/gestor_artists.o: src/gestor_artists.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o  programa-principal src/artists.o src/main.o src/musics.o src/users.o src/validation.o src/queries.o src/utils.o src/gestor_artists.o resultados/*.txt
