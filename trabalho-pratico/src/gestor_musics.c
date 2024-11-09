#include "gestor_musics.h"
//#include "utils.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void parseMusics(FILE *fp, GHashTable *musicsTable, GHashTable *artistsTable) {
  char *line = NULL;
  size_t len = 0;
  char *id;
  Musics *music = NULL;
  FILE *newFile = fopen("./resultados/musics_errors.csv", "w");
  if (newFile == NULL) {
    perror("Erro ao abrir o ficheiro de erros");
    return;
  }
  getline(&line, &len, fp);
  while (getline(&line, &len, fp) != -1) {
    if (validateMusicsLine(strdup(line), artistsTable)) {

      music = separateMusics(strdup(line));
      // Insere na HashTable usando o music->id como key
      id = getMusicId(music);
      g_hash_table_insert(musicsTable, id, music);
    } else {
      // Escreve a linha inválida no ficheiro de erros
      fprintf(newFile, "%s", line);
    }
  }
  // destroyMusic(music);
  fclose(newFile);
  free(line);
}