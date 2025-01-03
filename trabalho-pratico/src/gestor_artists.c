#include "gestor_artists.h"
#include "artists.h"
#include "top10Query4.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <glib.h>
#include <stdlib.h>
#include <string.h>

struct gestorArtists {
  FILE *errorsFile;
  GHashTable *artistsTable;
  GArray *Tops10;
  GList *listaQuery2;
};

gestorArtists *initGestorArtists(const char *errorsFilePath) {
  GHashTable *artistsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyArtist);
  gestorArtists *gestor = malloc(sizeof(gestorArtists));
  if (!gestor)
    return NULL;

  gestor->errorsFile = fopen(errorsFilePath, "w");
  if (!gestor->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestor);
    return NULL;
  }
  GArray *Tops10 = g_array_new(FALSE, FALSE, sizeof(ArrayTop10 *));
  g_array_set_size(Tops10, 329);
  for (int i = 0; i < (int)Tops10->len; i++) {
    g_array_index(Tops10, ArrayTop10 *, i) = NULL;
  }

  gestor->Tops10 = Tops10;
  gestor->listaQuery2 = NULL;

  gestor->artistsTable = artistsTable;
  return gestor;
}

void freeGArrayQuery4(GArray *Tops10) {
  for (int i = 0; i < (int)Tops10->len; i++) {
    ArrayTop10 *heap = g_array_index(Tops10, ArrayTop10 *, i);
    if (heap != NULL) {
      freeArrayTop10(heap);
    }
  }
  g_array_free(Tops10, false);
}
void freeGestorArtists(struct gestorArtists *gestor) {
  if (gestor != NULL) {
    if (gestor->errorsFile != NULL) {
      fclose(gestor->errorsFile);
    }
    if (gestor->artistsTable != NULL) {
      g_hash_table_destroy(gestor->artistsTable);
    }
    if (gestor->Tops10 != NULL) {
      for (guint i = 0; i < gestor->Tops10->len; i++) {
        ArrayTop10 *elem = g_array_index(gestor->Tops10, ArrayTop10 *, i);
        if (elem != NULL) {
          freeArrayTop10(elem);
        }
      }
      g_array_free(gestor->Tops10, TRUE);
    }
    g_list_free(gestor->listaQuery2);
    free(gestor);
  }
}

void parserArtist(GHashTable *ArtistsTable, Artists *artist, FILE *errorsFile,
                  char *line) {
  char *idConstituentLine = pegarArtistIdConstituent(artist);
  char *idConstituentCSV = pegarArtistIdConstituent(artist);
  char *type = pegarArtistType(artist);

  if (validateArtistLine(idConstituentLine, type) &&
      validateCSVList(idConstituentCSV)) {

    char *id = getArtistId(artist);
    remove_quotes(id);

    Artists *existing_artist = g_hash_table_lookup(ArtistsTable, id);
    if (existing_artist != NULL) {
      destroyArtist(existing_artist);
    }

    g_hash_table_insert(ArtistsTable, id, artist);
  } else {
    fprintf(errorsFile, "%s", line);
    destroyArtist(artist);
  }
  free(idConstituentLine);
  free(idConstituentCSV);
  free(type);
}

int GestorArtists(gestorArtists *gestor, char *artistsPath) {
  FILE *fp = fopen(artistsPath, "r");

  if (fp) {

    char *line = NULL;
    size_t len = 0;
    Artists *artist = NULL;

    assert(getline(&line, &len, fp) != -1);

    while (getline(&line, &len, fp) != -1) {
      if (line != NULL) {
        char *line_copy = strdup(line);
        if (!line_copy) {
          fprintf(stderr, "Erro ao duplicar a linha\n");
          continue;
        }
        artist = separateArtists(line_copy);
        parserArtist(gestor->artistsTable, artist, gestor->errorsFile, line);
        free(line_copy);
      }
    }
    free(line);

    fclose(fp);
  } else {
    perror("Error opening artists file");
    return 0;
  }
  return 1;
}

GArray *getGArrayTops10(gestorArtists *gestorArtists) {
  return gestorArtists->Tops10;
}

gboolean lookUpArtistsHashTable(gestorArtists *gestorArtist, char *key,
                                gpointer *value, gpointer *orig_key) {
  gboolean found = g_hash_table_lookup_extended(gestorArtist->artistsTable, key,
                                                orig_key, value);
  return found;
}

void incrementArtistsNumAlbuns(char *artistId, gestorArtists *gestorArtist) {
  gpointer value;
  gpointer orig_key;
  int num = 0;
  gboolean found =
      lookUpArtistsHashTable(gestorArtist, artistId, &orig_key, &value);
  if (found) {
    num = getArtistNumAlbunsIndividual(orig_key);
    num++;
    alterarArtistNumAlbunsIndividual(orig_key, num);
  }
}

void colocaZeroVezesTop10(gestorArtists *GestorArtists) {
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, GestorArtists->artistsTable);

  gpointer key1;
  gpointer value1;

  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Artists *artist = (Artists *)value1;
    putArtistsVezesTop10Zero(artist);
  }
}

void insertListaQuery2(gestorArtists *gestorArtists, Artists *artist) {
  char *artistId = pegarArtistId(artist);
  remove_quotes(artistId);
  char *currentArtist = NULL;
  gpointer orig_key;
  gpointer value;
  GList *node = gestorArtists->listaQuery2;
  Artists *currentArtistList;
  currentArtist = artistId;
  gboolean found =
      lookUpArtistsHashTable(gestorArtists, currentArtist, &orig_key, &value);
  if (found) {
    int inseriu = 0;
    while (node != NULL && !inseriu) {
      currentArtistList = (Artists *)node->data;
      char *currentArtistListId = getArtistId(currentArtistList);
      if (getArtistDiscografia(currentArtistList) <
              getArtistDiscografia(orig_key) ||
          (getArtistDiscografia(currentArtistList) ==
               getArtistDiscografia(orig_key) &&
           strcmp(currentArtistListId, currentArtist) > 0)) {
        inseriu = 1;
        gestorArtists->listaQuery2 =
            g_list_insert_before(gestorArtists->listaQuery2, node, artist);
      }
      node = node->next;
      free(currentArtistListId);
    }
    if (!inseriu) {
      gestorArtists->listaQuery2 =
          g_list_append(gestorArtists->listaQuery2, artist);
    }
  }
  free(artistId);
}

void CriaListasQuery2(gestorArtists *gestorArtists) {
  GHashTableIter iter;
  g_hash_table_iter_init(&iter, gestorArtists->artistsTable);

  gpointer key1, value1;
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Artists *artist = (Artists *)value1;
    insertListaQuery2(gestorArtists, artist);
  }
}

GList *getGListQuery2GestorArtist(gestorArtists *gestorArtists) {
  return gestorArtists->listaQuery2;
}

