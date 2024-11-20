CC = gcc
CFLAGS = -Iinclude $(shell pkg-config --cflags glib-2.0) -Wall -Wextra -Werror -O2 -g
LDFLAGS = $(shell pkg-config --libs glib-2.0)

OBJ_FILES = src/main.o src/gestores.o src/gestor_prints.o src/parsers.o src/query1.o src/query2.o src/query3.o src/gestor_queries.o src/musics.o src/users.o src/artists.o src/validation.o src/utils.o src/gestor_artists.o src/gestor_musics.o src/gestor_users.o

all: programa-principal programa-testes

programa-principal: $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

programa-testes: src/programa-testes.o src/compare_files.o
	$(CC) $^ $(LDFLAGS) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o programa-principal programa-testes resultados/*.txt resultados/*.csv
