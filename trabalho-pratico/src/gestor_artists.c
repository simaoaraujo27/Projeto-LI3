#include "gestor_artists.h"


void parseArtists(FILE *fp, GHashTable *artistsTable) {
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1) {
    Artists *artist = separateArtists(line);
    char *id = getArtistId(artist);
    remove_quotes(id);
    // Insere na HashTable usando o artist->name como key
    g_hash_table_insert(artistsTable, g_strdup(id), artist);
  }

  free(line);
}