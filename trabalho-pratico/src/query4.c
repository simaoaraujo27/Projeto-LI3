#include "query4.h"
#include "gestor_musics.h"
#include "inputResult.h"
#include "output_Result.h"
#include "top10Query4.h"
#include "utils.h"
#include <assert.h>
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// para cada musica que esta no historico incrementa a duracao por semana de todos os seus artistas
void armazenarValores(char *musicId, int duration, int timeStamp,
                      gestorMusics *gestorMusics, gestorArtists *gestorArtists,
                      GArray *Tops10) {
  gpointer value0;
  gpointer orig_key0;
  int semana = 0;
  if (timeStamp >= 2)
    semana = (timeStamp + 5) / 7;
  remove_quotes(musicId);
  gboolean found1 =
      lookUpMusicsHashTable(gestorMusics, musicId, &value0, &orig_key0);

  if (found1) {
    char *artistId = getMusicArtistId(orig_key0);
    char *copia = artistId;
    remove_quotes(artistId);
    removeFstLast(artistId);

    int lentghArtistId = (int)strlen(artistId);

    char *currentArtist = NULL;
    gpointer orig_key;
    gpointer value;

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
        int totalDuration =
            incrementArtistDurationPerWeek(orig_key, duration, semana);
        int tamanhoTops10 = Tops10->len;
        if (semana >= tamanhoTops10) {
          g_array_set_size(Tops10, (guint)(semana + 1));
          for (int i = tamanhoTops10; i <= semana; i++) {
            g_array_index(Tops10, ArrayTop10 *, i) = NULL;
          }

          tamanhoTops10 = Tops10->len;
        }
        // ve se este artist entra/pode entrar no top10 desta semana
        ArrayTop10 *top10 = g_array_index(Tops10, ArrayTop10 *, semana);
        if (top10 != NULL) {
          int indiceMinNode = 0;
          NodoArray minNode = menorNodoArray(top10, &indiceMinNode);
          int durationMinNode = getNodoArrayDuration(&minNode);
          insertArrayTop10(top10, totalDuration, durationMinNode, &minNode,
                           currentArtist, indiceMinNode);
          ArrayTop10 *new = cloneArrayTop10(top10);
          g_array_index(Tops10, ArrayTop10 *, semana) = new;
          freeArrayTop10(top10);
        } else {
          top10 = createArrayTop10();
          insertArrayTop10(top10, totalDuration, 0, NULL, currentArtist, 0);
          ArrayTop10 *new = cloneArrayTop10(top10);
          g_array_index(Tops10, ArrayTop10 *, semana) = new;
          freeArrayTop10(top10);
        }
      }
      lentghArtistId -= 12;
      free(currentArtist);
    }

    free(copia);
  }
}

void query4(gestorArtists *gestorArtists, char *DataFim, char *DataInicio,
            int contadorOutputs, int TemS) {
  GArray *Tops10 = getGArrayTops10(gestorArtists);
  FILE *newFile = createFile(contadorOutputs);

  // calcula a semana inicial e a semana final
  int semanaInicio = 0, semanaFim = 0;
  if (DataInicio == NULL && DataFim == NULL) {
    semanaInicio = 0;
    semanaFim = Tops10->len + 1;
  } else {
    semanaInicio = (calcularDiasAte_9_9_2024(DataInicio) + 5) / 7;
    semanaFim = (calcularDiasAte_9_9_2024(DataFim) + 5) / 7;
    if (semanaInicio >= (int)Tops10->len)
      semanaInicio = (int)Tops10->len;
    if ((semanaFim >= (int)Tops10->len && semanaInicio >= (int)Tops10->len) ||
        (semanaFim < semanaInicio)) {
      fprintf(newFile, "\n");
      fclose(newFile);
      return;
    }
  }

  // vê qual é o artist que esteve mais vezes no top 10 durante as semanas em questão
  gpointer orig_key;
  gpointer value;
  int maisVezesNoTop10 = 0;
  char *artistMaisVezesNoTop10 = NULL;
  ArrayTop10 *top10 = NULL;

  for (int i = semanaInicio; i <= semanaFim; i++) {
    top10 = g_array_index(Tops10, ArrayTop10 *, i);
    if (top10 != NULL) {
      for (int j = 0; j < getArrayTop10Size(top10); j++) {
        NodoArray *node = getArrayTop10NodoArray(top10, j);
        char *currentArtist = getNodoArrayArtistId(node);
        gboolean found = lookUpArtistsHashTable(gestorArtists, currentArtist,
                                                &orig_key, &value);

        if (found) {
          int vezesAtuais = incrementArtistVezesNoTop10(orig_key);
          if (vezesAtuais > maisVezesNoTop10) {
            maisVezesNoTop10 = vezesAtuais;
            if (artistMaisVezesNoTop10 != NULL) {
              free(artistMaisVezesNoTop10);
            }
            artistMaisVezesNoTop10 = strdup(currentArtist);

          } else if (vezesAtuais == maisVezesNoTop10 &&
                     strcmp(artistMaisVezesNoTop10, currentArtist) > 0) {
            maisVezesNoTop10 = vezesAtuais;
            if (artistMaisVezesNoTop10 != NULL) {
              free(artistMaisVezesNoTop10);
            }
            artistMaisVezesNoTop10 = strdup(currentArtist);
          }
        }
        free(currentArtist);
      }
    }
  }
  lookUpArtistsHashTable(gestorArtists, artistMaisVezesNoTop10, &orig_key,
                         &value);

  char *type = getArtistTypeStr(orig_key);

  printQuery4(newFile, TemS, artistMaisVezesNoTop10, type, maisVezesNoTop10);
  free(type);
  free(artistMaisVezesNoTop10);
  colocaZeroVezesTop10(gestorArtists);
}
