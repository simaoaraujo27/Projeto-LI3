#include "gestor_musics.h"
#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestores.h"
#include "query2.h"
#include "validation.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct gestorMusics {
  GHashTable *musicsTable;
  GHashTable *genresTable;
  int *nGeneros;
};

gestorMusics *initGestorMusics() {
  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);
  GHashTable *genresTable = g_hash_table_new(g_str_hash, g_str_equal);
  gestorMusics *gestorMusic = malloc(sizeof(gestorMusics));
  if (!gestorMusic)
    return NULL;

  gestorMusic->musicsTable = musicsTable;
  gestorMusic->genresTable = genresTable;
  gestorMusic->nGeneros = malloc(sizeof(int *));
  *(gestorMusic->nGeneros) = 0;
  return gestorMusic;
}

void freeGestorMusics(gestorMusics *gestor) {
  if (gestor) {
    g_hash_table_destroy(gestor->musicsTable);
    g_hash_table_destroy(gestor->genresTable);
    free(gestor->nGeneros);
    free(gestor);
  }
}

void addGenre(GHashTable *genresTable, int *nGeneros, char *genre) {
  if (!g_hash_table_contains(genresTable, genre)) {
    g_hash_table_insert(genresTable, (gpointer)genre, NULL);
    (*nGeneros)++;
  }
}

char **insertGenreToArray(gestorMusics *gestorMusics, int numGeneros) {
  char **valuesArray = (char **)malloc(numGeneros * sizeof(char *));
  if (valuesArray == NULL) {
    perror("Falha na alocação de memória para o array");
    exit(1);
  }

  GHashTableIter iter;
  g_hash_table_iter_init(&iter, gestorMusics->genresTable);

  gpointer key1;
  gpointer value1;
  int i = 0;

  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    if (key1 != NULL) {
      valuesArray[i] = "";
      char *genre = strdup((char *)key1);
      if (genre == NULL) {
        perror("Falha na alocação de memória para a string");
        return NULL;
      }
      valuesArray[i++] = genre;
    }
  }

  return valuesArray;
}

void parserMusic(char *copia, Gestores *gestor, char *line, Musics *music,
                 GHashTable *musicsTable, GHashTable *genresTable,
                 int *nGeneros) {
  gestorArtists *gestorArtist = getGestorArtist(gestor);
  gestorAlbuns *gestorAlbuns = getGestorAlbum(gestor);
  char *id;
  char *genre;
  if (validateMusicsLine(copia, gestorArtist, gestorAlbuns)) {
    music = separateMusics(line);
    int duration = getMusicDuration(music);
    id = getMusicId(music);
    g_hash_table_insert(musicsTable, id, music);

    char *artistId = getMusicArtistId(music);

    remove_quotes(artistId);
    removeFstLast(artistId);

    char *originalArtistId = strdup(artistId);
    char *artistIdCopy = originalArtistId;

    int lengthArtistId = (int)strlen(artistIdCopy);
    char *currentArtist = NULL;
    gpointer orig_key;
    gpointer value;

    while (lengthArtistId > 0) {
      if (lengthArtistId == (int)strlen(artistIdCopy)) {
        artistIdCopy = artistIdCopy + 1;
      } else
        artistIdCopy = artistIdCopy + 3;

      char *temp = strsep(&artistIdCopy, "'");
      if (temp) {
        currentArtist = strdup(temp);
        currentArtist[8] = '\0';
      }

      gboolean found = lookUpArtistsHashTable(gestorArtist, currentArtist,
                                              &orig_key, &value);
      if (found) {
        int discografiaAntiga = getArtistDiscografia(orig_key);
        setArtistDiscografia(orig_key, discografiaAntiga + duration);
      }
      lengthArtistId -= 12;

      free(currentArtist);
      currentArtist = NULL;
    }

    free(originalArtistId);
    free(artistId);

    genre = getMusicGenre(music);
    addGenre(genresTable, nGeneros, genre);
    free(genre);
    genre = NULL;
  } else {
    WriteErrorsFile(getGestorFicheiroErrosCSV(gestor), "musics", line);
  }
}

int GestorMusics(Gestores *gestor, char *musicsPath) {
  gestorMusics *gestorMusic = getGestorMusic(gestor);
  FILE *fp = fopen(musicsPath, "r");
  if (fp) {
    char *line = NULL;
    size_t len = 0;
    Musics *music = NULL;

    assert(getline(&line, &len, fp) != -1);

    while (getline(&line, &len, fp) != -1) {
      char *copia = strdup(line);
      parserMusic(copia, gestor, line, music, gestorMusic->musicsTable,
                  gestorMusic->genresTable, gestorMusic->nGeneros);
      free(copia);
    }
    free(line);
    fclose(fp);
  } else {
    perror("Error opening musics file");
    return 0;
  }
  return 1;
}

int getMusicsNGenres(gestorMusics *gestorMusic) {
  int *i = gestorMusic->nGeneros;
  return *i;
}

gboolean lookUpMusicsHashTable(gestorMusics *gestorMusic, char *line,
                               gpointer *value, gpointer *orig_key) {
  gboolean found = g_hash_table_lookup_extended(gestorMusic->musicsTable, line,
                                                value, orig_key);
  return found;
}

void incrementRecipeArtist(char *musicId, gestorMusics *gestorMusics,
                           gestorArtists *gestorArtists) {
  gpointer value0;
  gpointer orig_key0;

  remove_quotes(musicId);
  gboolean found1 =
      lookUpMusicsHashTable(gestorMusics, musicId, &value0, &orig_key0);

  if (found1) {

    char *artistId = getMusicArtistId(orig_key0);
    char *artistIdOriginal = artistId;
    remove_quotes(artistId);
    removeFstLast(artistId);

    int lentghArtistId = (int)strlen(artistId);

    char *currentArtist = NULL;
    gpointer orig_key;
    gpointer value;
    gpointer orig_key1;
    gpointer value1;

    while (lentghArtistId > 0) {
      if (lentghArtistId == (int)strlen(artistId)) {
        artistId = artistId + 1;
      } else
        artistId = artistId + 3;
      currentArtist = strdup(strsep(&artistId, "'"));
      currentArtist[8] = '\0';
      gboolean found = lookUpArtistsHashTable(gestorArtists, currentArtist,
                                              &orig_key, &value);
      if (found) {
        char *type = getArtistTypeStr(orig_key);
        float recipe_Per_Stream = getArtistRecipePerStream(orig_key);
        float receitaTotal = recipe_Per_Stream;
        float receitaAntiga = getArtistReceitaTotal(orig_key);
        float receitaAtualizada = receitaAntiga + receitaTotal;
        setArtistReceitaTotal(orig_key, receitaAtualizada);
        if (strcmp(type, "group") == 0) {
          int NumComponentesBanda = getArtistTamanhoGrupo(orig_key);
          char *idComponentes = getArtistIdConstituent(orig_key);
          char *idComponentesOriginal = idComponentes;
          remove_quotes(idComponentes);
          removeFstLast(idComponentes);
          int TamanhoIdComponentes = (int)strlen(idComponentes);
          while (TamanhoIdComponentes > 0) {
            if (TamanhoIdComponentes == (int)strlen(idComponentes)) {
              idComponentes = idComponentes + 1;
            } else
              idComponentes = idComponentes + 3;
            char *currentComponent = strdup(strsep(&idComponentes, "'"));
            currentComponent[8] = '\0';
            lookUpArtistsHashTable(gestorArtists, currentComponent, &orig_key1,
                                   &value1);
            float receitaAntigaComp = getArtistReceitaTotal(orig_key1);
            setArtistReceitaTotal(
                orig_key1, receitaAntigaComp +
                               (receitaTotal / (float)NumComponentesBanda));
            TamanhoIdComponentes -= 12;
            free(currentComponent);
          }
          free(idComponentesOriginal);
        }
        free(type);
      }
      lentghArtistId -= 12;
      free(currentArtist);
      currentArtist = NULL;
    }

    free(artistIdOriginal);
  }
}
