CC = gcc
CFLAGS = -Iinclude $(shell pkg-config --cflags glib-2.0) -Wall -Wextra -Werror -O3 -g 
LDFLAGS = $(shell pkg-config --libs glib-2.0) -lm

OBJ_FILES = src/main.o src/gestores.o src/top10Query4.o src/erros.o src/nodo_musica.o src/resumo_users.o src/output_Result.o src/inputResult.o src/parser.o src/query1.o src/query2.o src/query3.o src/query4.o src/query5.o src/query6.o src/gestor_queries.o src/musics.o src/users.o src/artists.o src/validation.o src/utils.o src/gestor_artists.o src/gestor_musics.o src/gestor_users.o src/albuns.o src/history.o src/gestor_albuns.o src/gestor_history.o src/recomendador-linux-x86_64.o src/compare_files.o

all: programa-principal programa-testes programa-interativo

programa-principal: $(OBJ_FILES)
	$(CC) $^ $(LDFLAGS) -o $@

programa-testes: src/programa-testes.o src/compare_files.o
	$(CC) $^ $(LDFLAGS) -o $@

programa-interativo: src/programa-interativo.o
	$(CC) $^ $(LDFLAGS) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@for file in $(OBJ_FILES); do \
		if [ "$$file" != "src/recomendador-linux-x86_64.o" ]; then \
			rm -f $$file; \
		fi \
	done
	rm -f programa-principal programa-testes resultados/*.txt resultados/*.csv
