#include "query4.h"
#include "gestor_musics.h"
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
  int semana =
      timeStamp / 7; // preciso mudar para arrajar ja que uma semana começa no
                     // domingo enquanto que assim esta a começar numa segunda

  remove_quotes(musicId);
  gboolean found1 =
      lookUpMusicsHashTable(gestorMusics, musicId, &value0, &orig_key0);

  if (found1) {
    char *artistId = getMusicArtistId(orig_key0);
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
            incrementArtistDurationPerWeek(orig_key, duration, semana);/* nao esta a somar */
        int tamanhoTops10 = Tops10->len;
        if (semana >= tamanhoTops10) {
          g_array_set_size(getGArrayTops10(gestorArtists), (guint)(semana + 1));
          for (int i = tamanhoTops10; i < (int)Tops10->len; i++) {
            g_array_index(Tops10, MinHeap *, i) =
                NULL; // Inicializa cada posição com NULL
          }
          tamanhoTops10 = Tops10->len;
        }
        MinHeap *heap = g_array_index(Tops10, MinHeap *, semana);
        if (heap != NULL) {
          HeapNode *minNode = getMinHeapFstHeapNode(heap);
          int durationMinNode = getHeapNodeDuration(minNode);
          insertMinHeap(heap, totalDuration, durationMinNode, minNode,
                        currentArtist);
        } else {
          heap = createMinHeap();
          insertMinHeap(heap, totalDuration, 0, NULL, currentArtist);
        }
      }
      lentghArtistId -= 12;
    }
  }
}

void query4(gestorArtists *gestorArtists) { /* tem de percorrer o GArray e
                                               aumentar em 1 num contador */
  GArray *Tops10 = getGArrayTops10(gestorArtists);

  int tamanhoTops10 = Tops10->len;
  gpointer orig_key;
  gpointer value;
  int maisVezesNoTop10 = 0;
  char *artistMaisVezesNoTop10 = NULL;
  for (int i = 0; i < tamanhoTops10; i++) {
    MinHeap *heap = g_array_index(Tops10, MinHeap *, i);
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
            artistMaisVezesNoTop10 = strdup(currentArtist);
          }
        }
      }
    }
  }
  printf("%s %d\n", artistMaisVezesNoTop10, maisVezesNoTop10);
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