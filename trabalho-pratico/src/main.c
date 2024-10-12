#include "validation.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *fp = NULL;

  if (argc < 2) {
    fp = stdin;
    fprintf(stderr, "Missing filename.\n");
    return 1;
  } else {
    char *filename = argv[1];
    fp = fopen(filename, "r");
    if (!fp) {
      perror("Error"); // Imprime "Error: No such file or directory"
      return -1;
    }
  }

  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) !=
         -1) { // Nesta funçao, primeiro temos que saber qual o ficheiro que
               // estamos a ler, depois tirar os erros desse ficheiro, depois
               // guardar os dados corretos em uma struct, e essa struct em uma
               // hashtable;
    printf("%s\n", line);
    if (strcmp(argv[1], "artists.csv")) {
      Artists *artista;
      artista = separateArtists(line);
      if (!validate_Artist(artista)) { // funcao nao feita ainda, so declarada
        // coloca-la num ficheiro aparte(fazer depois)
        continue; // para ja da continue ate fazer a linha anterior
      } else {
        // guardar o artista na hashtable
      }
    } else if (strcmp(argv[1], "musics.csv")) {
      Musics *musica;
      musica = separateMusics(line);
      if (!validate_Music(musica)) {
        // coloca-la num ficheiro aparte(fazer depois)
        continue; // para ja da continue ate fazer a linha anterior
      } else {
        // guardar a musica na hashtable
      }
    } else if (strcmp(argv[1], "users.csv")) {
      Users *user;
      user = separateUsers(line);
      if (!validate_User(user)) {
        // coloca-la num ficheiro aparte(fazer depois)
        continue; // para ja da continue ate fazer a linha anterior
      } else {
        // guardar o user na hashtable
      }
    }
  }

  free(line);
  return 0;
}