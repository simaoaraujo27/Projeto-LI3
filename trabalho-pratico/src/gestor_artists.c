#include "gestor_artists.h"

void parseArtists(FILE *fp, GHashTable *artistsTable) {
  char *line = NULL;

  size_t len = 0;
  char *id;
  Artists *artist = NULL;
  while (getline(&line, &len, fp) != -1) {
    Artists *artist = separateArtists(line);
    id = getArtistId(artist);
    remove_quotes(id);
    // Insere na HashTable usando o artist->name como key
    g_hash_table_insert(artistsTable, id, artist);
  }
  //destroyArtist(artist);
  free(line);
  free(id);
}