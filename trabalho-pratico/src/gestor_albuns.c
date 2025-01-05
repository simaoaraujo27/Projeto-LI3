#include "gestor_albuns.h"
#include "albuns.h"
#include "erros.h"
#include "gestores.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <glib.h>
#include <stdio.h>

struct gestorAlbuns {
  GHashTable *albunsTable;
};

// inicializa o gestor albuns e a sua hashtable
gestorAlbuns *initGestorAlbuns() {
  GHashTable *albunsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyAlbum);

  gestorAlbuns *gestorAlbuns = malloc(sizeof(struct gestorAlbuns));
  if (!gestorAlbuns)
    return NULL;

  gestorAlbuns->albunsTable = albunsTable;
  return gestorAlbuns;
}

void freeGestorAlbuns(gestorAlbuns *gestor) {
  if (gestor) {
    g_hash_table_destroy(gestor->albunsTable);
    free(gestor);
  }
}

// insere o album na hashtable
void parserAlbum(GHashTable *albunsTable, Albuns *album, Gestores *gestor,
                 char *line, char *copia, gestorArtists *gestorArtists) {
  if (validateAlbumsLine(copia, gestorArtists)) {
    char *id = getAlbumId(album);
    remove_quotes(id);
    g_hash_table_insert(albunsTable, id, album);
  } else {
    WriteErrorsFile(getGestorFicheiroErrosCSV(gestor), "albuns", line);
  }
}

// função que insere todos os albuns na hashtable
int GestorAlbuns(Gestores *gestor, char *albunsPath) {
  FILE *fp = fopen(albunsPath, "r");
  gestorAlbuns *gestorAlbuns = getGestorAlbum(gestor);
  gestorArtists *gestorArtists = getGestorArtist(gestor);

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
        parserAlbum(gestorAlbuns->albunsTable, album, gestor, line, copia,
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

// função que vê se um album esta na hashtable
gboolean lookUpAlbunsHashTable(gestorAlbuns *gestorAlbuns, char *key,
                               gpointer *value, gpointer *orig_key) {
  gboolean found = g_hash_table_lookup_extended(gestorAlbuns->albunsTable, key,
                                                orig_key, value);
  return found;
}