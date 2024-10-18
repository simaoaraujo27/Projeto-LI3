#include "artists.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum tipoArtista { Individual, Grupo };

struct artists {
  int id;                // identificador único do artista
  char *name;            // nome do artista
  char *description;     // descrição do artista
  int recipe_per_stream; // dinheiro auferido de cada vez que uma das músicas
                         // do artista é reproduzida
  char *id_constituent;  // lista de identificadores únicos dos seus
                         // constituintes, no caso de se tratar de um artista
                         // coletivo. Este campo pode ser uma lista vazia.
  char *country;         // nacionalidade do artista.
  enum tipoArtista tipo; // tipo de artista, i.e., individual ou grupo musical,
                         // caso individual = True, grupo = False
};

Artists *separateArtists(char *line) {
  // Separa a linha e guarda os respetivos dados na struct artistas

  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  artist->id = atoi(strsep(&line, ";"));
  artist->name = strdup(strsep(&line, ";"));
  artist->description = strdup(strsep(&line, ";"));
  artist->recipe_per_stream = atoi(strsep(&line, ";"));
  artist->id_constituent = strdup(strsep(&line, ";"));
  artist->country = strdup(strsep(&line, ";"));
  if (!strcmp(strsep(&line, "\n"), "individual"))
    artist->tipo = Individual;
  else
    artist->tipo = Grupo;

  return artist;
}

bool validateArtist(Artists *artist) {
  return ((artist->tipo == Individual && strlen(artist->id_constituent) == 0) ||
          (artist->tipo == Grupo && strlen(artist->id_constituent) != 0));
}

void parseArtists(FILE *fp, GHashTable *artistsTable) {
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1) {
    Artists *artist = separateArtists(line);
    // Insere na HashTable usando o artist->name como key
    g_hash_table_insert(artistsTable, artist->name, artist);
  }

  free(line);
}

void destroyArtist(gpointer user) { return; }

char *getArtistName(Artists *artist) { return strdup(artist->name); }
