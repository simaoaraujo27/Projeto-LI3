#include "artists.h"
#include "users.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum tipoArtista { Individual, Grupo };

struct artists {
  char *id;              // identificador único do artista
  char *name;            // nome do artista
  char *description;     // descrição do artista
  int recipe_per_stream; // dinheiro auferido de cada vez que uma das músicas
                         // do artista é reproduzida
  char *id_constituent;  // lista de identificadores únicos dos seus
                         // constituintes, no caso de se tratar de um artista
                         // coletivo. Este campo pode ser uma lista vazia.
  char *country;         // nacionalidade do artista.
  enum tipoArtista tipo; // tipo de artista, i.e., individual ou grupo musical,
  int discografia;       // discografia do artista
};

Artists *separateArtists(char *line) {
  // Separa a linha e guarda os respetivos dados na struct artistas

  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  artist->id = strdup(strsep(&line, ";"));
  artist->name = strdup(strsep(&line, ";"));
  artist->description = strdup(strsep(&line, ";"));
  artist->recipe_per_stream = atoi(strsep(&line, ";"));
  artist->id_constituent = strdup(strsep(&line, ";"));
  artist->country = strdup(strsep(&line, ";"));
  if (!strcmp(strsep(&line, "\n"), "individual"))
    artist->tipo = Individual;
  else
    artist->tipo = Grupo;
  artist->discografia = 0;

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
    remove_quotes(artist->id);
    // Insere na HashTable usando o artist->name como key
    g_hash_table_insert(artistsTable, g_strdup(artist->id), artist);
  }

  free(line);
}

void increment_artist_discografia(gpointer a, int duracao) {
  Artists *artist = (Artists *)a;
  artist->discografia += duracao;
  printf("%d\n", artist->discografia);
}

void destroyArtist(gpointer artist) {
  Artists *a = (Artists *)artist;

  g_free(a->name);
  g_free(a->description);
  g_free(a->id_constituent);
  g_free(a->country);
  g_free(a->id);
  g_free(a);
}

char *getArtistId(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->id);
}

char *getArtistName(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->name);
}

char *getArtistDescription(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->description);
}

int getArtistRecipePerStream(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return (a->recipe_per_stream);
}

char *getArtistIdConstituent(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->id_constituent);
}

char *getArtistCountry(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->country);
}

enum tipoArtista getArtistType(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return (a->tipo);
}

int getArtistDiscografia(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return (a->discografia);
}