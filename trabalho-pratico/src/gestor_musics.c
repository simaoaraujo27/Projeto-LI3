#include "gestor_musics.h"

void parseMusics(FILE *fp, GHashTable *musicsTable) {
  char *line = NULL;
  size_t len = 0;
  char *id;
  while (getline(&line, &len, fp) != -1) {
    Musics *music = separateMusics(line);
    // Insere na HashTable usando o music->id como key
    id = getMusicId(music);
    g_hash_table_insert(musicsTable, id, music);
  }
  free(line);
  free(id);
}