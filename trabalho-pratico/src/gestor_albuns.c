#include "gestor_albuns.h"
#include "albuns.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>

struct gestorAlbuns {
  FILE *errorsFile;
  GHashTable *albunsTable;
};

gestorAlbuns *initGestorAlbuns(char *errorsFilePath) {
  GHashTable *albunsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyAlbum);

  gestorAlbuns *gestorAlbuns = malloc(sizeof(struct gestorAlbuns));
  if (!gestorAlbuns)
    return NULL;

  gestorAlbuns->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorAlbuns->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorAlbuns);
    return NULL;
  }

  gestorAlbuns->albunsTable = albunsTable;
  return gestorAlbuns;
}

void freeGestorAlbuns(gestorAlbuns *gestor) {
  if (gestor) {
    if (gestor->errorsFile)
      fclose(gestor->errorsFile);
    g_hash_table_destroy(gestor->albunsTable);
    free(gestor);
  }
}

void parserAlbum(GHashTable *albunsTable, Albuns *album, FILE *errorsFile,
                 char *line, char *copia, gestorArtists *gestorArtists) {
  if (validateAlbumsLine(copia, gestorArtists)) {
    char *id = getAlbumId(album);
    remove_quotes(id);
    g_hash_table_insert(albunsTable, id, album);
  } else {
    fprintf(errorsFile, "%s", line);
  }
}

int GestorAlbuns(gestorAlbuns *gestor, char *albunsPath,
                 gestorArtists *gestorArtists) {
  FILE *fp = fopen(albunsPath, "r");

  if (fp) {
    char *line = NULL;
    size_t len = 0;
    Albuns *album = NULL;

    assert(getline(&line, &len, fp) != -1);

    while (getline(&line, &len, fp) != -1) {
      if (line != NULL) {
        char *line_copy = strdup(line);
        if (!line_copy) {
          fprintf(stderr, "Erro ao duplicar a linha\n");
          continue;
        }
        album = separateAlbuns(line_copy, gestorArtists);
        char *copia = strdup(line);
        parserAlbum(gestor->albunsTable, album, gestor->errorsFile, line, copia,
                    gestorArtists);
        free(copia);
        free(line_copy);
      }
    }
    free(line);

    fclose(fp);
  } else {
    perror("Error opening albuns file");
    return 0;
  }
  return 1;
}

gboolean lookUpAlbunsHashTable(gestorAlbuns *gestorAlbuns, char *key,
                               gpointer *value, gpointer *orig_key) {
  gboolean found = g_hash_table_lookup_extended(gestorAlbuns->albunsTable, key,
                                                orig_key, value);
  return found;
}