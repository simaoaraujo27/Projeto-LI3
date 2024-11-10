#include "gestor_artists.h"
#include "utils.h"
#include "validation.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Definição completa da estrutura gestorArtists
struct gestorArtists {
  FILE *errorsFile;
  GHashTable *artistsTable;
};

// Função para inicializar a estrutura gestorArtists
gestorArtists *initGestorArtists(const char *errorsFilePath,
                                 GHashTable *artistsTable) {
  gestorArtists *gestor = malloc(sizeof(gestorArtists));
  if (!gestor)
    return NULL;

  gestor->errorsFile = fopen(errorsFilePath, "w");
  if (!gestor->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestor);
    return NULL;
  }

  gestor->artistsTable = artistsTable;
  return gestor;
}

// Função para liberar a estrutura gestorArtists e seus recursos
void freeGestorArtists(gestorArtists *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(gestor->errorsFile);
    free(gestor);
  }
}

// Função para processar o arquivo de artistas usando gestorArtists
void parseArtists(FILE *fp, gestorArtists *gestor) {
  char *line = NULL;
  size_t len = 0;
  Artists *artist = NULL;

  // Ignora a primeira linha (cabeçalho)
  assert(getline(&line, &len, fp) != -1);

  // Lê o arquivo linha por linha
  while (getline(&line, &len, fp) != -1) {
    if (line != NULL) {
      artist = separateArtists(strdup(line));
      if (validateArtistLine(pegarArtistIdConstituent(artist),
                             pegarArtistType(artist)) &&
          validateCSVList(pegarArtistIdConstituent(artist))) {

        // Insere na hash table se for válido
        char *id = getArtistId(artist);
        remove_quotes(id);
        g_hash_table_insert(gestor->artistsTable, id, artist);
      } else {
        fprintf(gestor->errorsFile, "%s", line);
        destroyArtist(artist);
      }
    }
  }

  free(line);
}

GHashTable *getArtistTable(gestorArtists *gestorArtist) {
  return gestorArtist->artistsTable;
}
