#include "gestor_musics.h"
#include "gestor_artists.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct gestorMusics {
  FILE *errorsFile;
  GHashTable *musicsTable;
};

gestorMusics *initGestorMusics(const char *errorsFilePath,
                               GHashTable *musicsTable) {
  gestorMusics *gestor = malloc(sizeof(gestorMusics));
  if (!gestor)
    return NULL;

  gestor->errorsFile = fopen(errorsFilePath, "w");
  if (!gestor->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestor);
    return NULL;
  }

  gestor->musicsTable = musicsTable;
  return gestor;
}

// Função para liberar a estrutura gestorMusics e seus recursos
void freeGestorMusics(gestorMusics *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(gestor->errorsFile);
    free(gestor);
  }
}

void parseMusics(FILE *fp, gestorMusics *gestorMusic,
                 gestorArtists *gestorArtist) {
  char *line = NULL;
  size_t len = 0;
  char *id;
  Musics *music = NULL;

  while (getline(&line, &len, fp) != -1) {
    if (validateMusicsLine(strdup(line), gestorArtist)) {
      music = separateMusics(strdup(line));
      // Insere na HashTable usando o music->id como key
      id = getMusicId(music);
      g_hash_table_insert(gestorMusic->musicsTable, id, music);
    } else {
      // Escreve a linha inválida no ficheiro de erros
      fprintf(gestorMusic->errorsFile, "%s", line);
    }
  }

  free(line);
}

GHashTable *getMusicsTable(gestorMusics *gestorMusic) {
  return gestorMusic->musicsTable;
}