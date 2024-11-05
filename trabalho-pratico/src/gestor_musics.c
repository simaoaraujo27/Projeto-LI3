#include "gestor_musics.h"

void parseMusics(FILE *fp, GHashTable *musicsTable) {
  char *line = NULL;
  size_t len = 0;
  char *id;
  Musics *music = NULL;
  while (getline(&line, &len, fp) != -1) {
    music = separateMusics(line);
    // Insere na HashTable usando o music->id como key
    id = getMusicId(music);
    g_hash_table_insert(musicsTable, id, music);
  }
  //destroyMusic(music);
  free(line);
  free(id);
}