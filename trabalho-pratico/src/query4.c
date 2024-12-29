#include "query4.h"
#include "gestor_musics.h"
#include "gestor_prints.h"
#include "inputResult.h"
#include "minHeap.h"
#include "utils.h"
#include <assert.h>
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* se o artista ja esta na minHeap trocar so o valor */

void armazenarValores(char *musicId, int duration,
                      int timeStamp /* esta em dias ate ao dia 9 / 9 / 2024 */,
                      gestorMusics *gestorMusics, gestorArtists *gestorArtists,
                      GArray *Tops10) {
  gpointer value0;
  gpointer orig_key0;
  int semana = 0;
  if (timeStamp >= 2)
    semana = (timeStamp + 4) / 7;
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
      currentArtist = strdup(strsep(&artistId, "'")); // Separa o ID do artista
      currentArtist[8] = '\0'; // Limita o ID a 8 caracteres
      gboolean found = lookUpArtistsHashTable(gestorArtists, currentArtist,
                                              &orig_key, &value);
      if (found) {
        int totalDuration =
            incrementArtistDurationPerWeek(orig_key, duration, semana);
        /* if (strcmp("A0003542", currentArtist) == 0)
            printf("%d\n", totalDuration); */
        int tamanhoTops10 = Tops10->len;
        if (semana >= tamanhoTops10) {
          // Ajusta o tamanho do array dinamicamente
          g_array_set_size(Tops10,
                           (guint)(semana + 1)); // Inclui a posição `semana`

          // Inicializa novas posições com NULL
          for (int i = tamanhoTops10; i <= semana; i++) {
            g_array_index(Tops10, MinHeap *, i) = NULL;
          }

          tamanhoTops10 = Tops10->len; // Atualiza o tamanho
        }

        MinHeap *heap = g_array_index(Tops10, MinHeap *, semana);
        if (heap != NULL) {
          int indiceMinNode = 0;
          HeapNode minNode = menorHeapNode(heap, &indiceMinNode);
          int durationMinNode = getHeapNodeDuration(&minNode);
          insertMinHeap(heap, totalDuration, durationMinNode, &minNode,
                        currentArtist, indiceMinNode);
          g_array_index(Tops10, MinHeap *, semana) = heap;
          heap = g_array_index(Tops10, MinHeap *, semana);
          minNode = menorHeapNode(heap, &indiceMinNode);
        } else {
          heap = createMinHeap();
          insertMinHeap(heap, totalDuration, 0, NULL, currentArtist, 0);
          g_array_index(Tops10, MinHeap *, semana) = heap;
        }
      }
      lentghArtistId -= 12;
      free(currentArtist);
      currentArtist = NULL;
    }

    free(copia);
  }
}

void query4(gestorArtists *gestorArtists, char *DataFim, char *DataInicio,
            int contadorOutputs, int TemS) { /* tem de percorrer o GArray e
aumentar em 1 num contador */
  GArray *Tops10 = getGArrayTops10(gestorArtists);
  FILE *newFile = createFile(contadorOutputs);

  int semanaInicio = 0, semanaFim = 0;
  if (DataInicio == NULL && DataFim == NULL) {
    semanaInicio = 0;
    semanaFim = Tops10->len + 1;
  } else {
    semanaInicio = (calcularDiasAte_9_9_2024(DataInicio) + 5) / 7;
    semanaFim = (calcularDiasAte_9_9_2024(DataFim) + 5) / 7;
    if (semanaInicio >= (int)Tops10->len)
      semanaInicio = (int)Tops10->len;
    if (semanaFim >= (int)Tops10->len && semanaInicio >= (int)Tops10->len) {
      fprintf(newFile, "\n");
      fclose(newFile);
      return;
    }
  }
  /* printf("semanaInicio = %d semanaFim = %d strsemanaFim %s\n", semanaInicio,
         semanaFim, DataFim); */
  gpointer orig_key;
  gpointer value;
  int maisVezesNoTop10 = 0;
  char *artistMaisVezesNoTop10 = NULL;
  MinHeap *heap = NULL;

  for (int i = semanaInicio; i <= semanaFim; i++) {
    heap = g_array_index(Tops10, MinHeap *, i);
    if (heap != NULL) {
      for (int j = 0; j < getMinHeapSize(heap); j++) {
        HeapNode *node = getMinHeapHeapNode(heap, j);
        char *currentArtist = getHeapNodeArtistId(node);
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

  printQuery4(newFile, TemS, artistMaisVezesNoTop10, getArtistTypeStr(orig_key),
              maisVezesNoTop10);
  free(artistMaisVezesNoTop10);
  colocaZeroVezesTop10(gestorArtists);
}

/*
enquanto é feito o parser de history:
  - ver o music_id
    - atraves do music_id sacar o artist_id da musica
  - ver a duration
  - ver o timestamp (data)

atraves do timestamp:
distancia em dias entre a data limite (9 de setembro) e a data que queremos
calcular e depois dividir por 7 -> da o indice da semana a ver no array
dinamico

array dinamico de minheaps de structs -> cada struct tem o artist_id e a
duracao total nessa semana cada posicao do array corresponde a uma semana; a
minheap é atraves da duracão (o menor fica no inicio) e tem tamanho 10

*/
