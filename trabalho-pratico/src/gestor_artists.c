#include "gestor_artists.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

// Função para libertar a estrutura gestorArtists e seus recursos
void freeGestorArtists(gestorArtists *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(gestor->errorsFile);
    free(gestor);
  }
}

// Função para processar o ficheiro de artistas usando gestorArtists
void parseArtists(FILE *fp, gestorArtists *gestor) {
  char *line = NULL;
  size_t len = 0;
  Artists *artist = NULL;

  // Ignora a primeira linha (cabeçalho)
  assert(getline(&line, &len, fp) != -1);

  while (getline(&line, &len, fp) != -1) {
    if (line != NULL) {
      char *line_copy = strdup(line); // Duplicação segura da linha
      if (!line_copy) {
        fprintf(stderr, "Erro ao duplicar a linha\n");
        continue;
      }

      artist = separateArtists(line_copy);

      char *idConstituentLine = pegarArtistIdConstituent(artist);
      char *idConstituentCSV = pegarArtistIdConstituent(artist);
      char *type = pegarArtistType(artist);

      if (validateArtistLine(idConstituentLine, type) &&
          validateCSVList(idConstituentCSV)) {

        // Insere na hash table se for válido
        char *id = getArtistId(artist);
        remove_quotes(id);

        // Verifica se a chave já existe e libera o valor antigo, se necessário
        Artists *existing_artist =
            g_hash_table_lookup(gestor->artistsTable, id);
        if (existing_artist != NULL) {
          destroyArtist(existing_artist); // Libera o artista duplicado
        }

        g_hash_table_insert(gestor->artistsTable, id, artist);
      } else {
        fprintf(gestor->errorsFile, "%s", line);
        destroyArtist(artist);
      }
      // Liberta a linha duplicada
      free(line_copy);
      free(idConstituentLine);
      free(idConstituentCSV);
      free(type);
      
    }
  }
  free(line);
}

GHashTable *getArtistTable(gestorArtists *gestorArtist) {
  return gestorArtist->artistsTable;
}
