#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *artist_id;
  int duration;
} NodoArray;

typedef struct {
  NodoArray data[10];
  int size;
} ArrayTop10;

NodoArray menorNodoArray(ArrayTop10 *top10, int *indice) {
  NodoArray menor = top10->data[0];
  for (int i = 0; i < top10->size; i++) {
    if (top10->data[i].duration < menor.duration) {
      menor = top10->data[i];
      *indice = i;
    } else if (top10->data[i].duration == menor.duration &&
               strcmp(menor.artist_id, top10->data[i].artist_id) < 0) {
      menor = top10->data[i];
      *indice = i;
    }
  }
  return menor;
}

int getArrayTop10Size(ArrayTop10 *h) { return h->size; }

char *getNodoArrayArtistId(NodoArray *NodoArray) {
  return strdup(NodoArray->artist_id);
}

int getNodoArrayDuration(NodoArray *NodoArray) { return NodoArray->duration; }

NodoArray *getArrayTop10NodoArray(ArrayTop10 *ArrayTop10, int i) {
  return &ArrayTop10->data[i];
}

ArrayTop10 *createArrayTop10() {
  ArrayTop10 *top10 = (ArrayTop10 *)malloc(sizeof(ArrayTop10));
  top10->size = 0;
  return top10;
}

int elemArrayTop10(char *currentArtist, NodoArray data[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (strcmp(data[i].artist_id, currentArtist) == 0) {
      return i;
    }
  }
  return -1;
}

// Função para inserir um elemento na min-top10
void insertArrayTop10(ArrayTop10 *top10, int totalDuration, int durationMinNode,
                      NodoArray *minNode, char *currentArtist,
                      int indiceMinNode) {
  if (!top10 || !currentArtist)
    return; // Validações básicas

  int indice = elemArrayTop10(currentArtist, top10->data, top10->size);

  // Verificar se a top10 está cheia
  if (indice != -1) {
    top10->data[indice].duration = totalDuration;
    return;
  }

  if (top10->size == 10) {
    char *NodoArrayArtistId = getNodoArrayArtistId(minNode);
    if (!NodoArrayArtistId)
      return;

    // Substituir o maior elemento (raiz) se o novo for menor
    if ((durationMinNode < totalDuration) ||
        (durationMinNode == totalDuration &&
         strcmp(currentArtist, NodoArrayArtistId) < 0)) {
      if (top10->data[indiceMinNode].artist_id != NULL) {
        free(top10->data[indiceMinNode].artist_id);
      }

      top10->data[indiceMinNode].artist_id = strdup(currentArtist);
      if (!top10->data[indiceMinNode].artist_id) {
        free(NodoArrayArtistId);
        return;
      }
      top10->data[indiceMinNode].duration = totalDuration;
    }
    free(NodoArrayArtistId);
    return;
  }

  int i = top10->size++;
  top10->data[i].artist_id = strdup(currentArtist);

  if (!top10->data[i].artist_id) {
    top10->size--;
    return;
  }
  top10->data[i].duration = totalDuration;
}

void freeArrayTop10(ArrayTop10 *top10) {
  if (top10 != NULL) {
    for (int i = 0; i < top10->size; i++) {
      if (top10->data[i].artist_id != NULL) {
        free(top10->data[i].artist_id);
        top10->data[i].artist_id = NULL;
      }
    }
    free(top10);
    top10 = NULL;
  }
}

ArrayTop10 *cloneArrayTop10(ArrayTop10 *top10) {
  if (!top10) {
    return NULL;
  }
  ArrayTop10 *newtop10 = createArrayTop10();
  if (!newtop10) {
    fprintf(stderr, "Erro ao alocar memória para a nova top10.\n");
    return NULL;
  }
  newtop10->size = top10->size;
  for (int i = 0; i < top10->size; i++) {
    newtop10->data[i].artist_id = strdup(top10->data[i].artist_id);
    if (!newtop10->data[i].artist_id) {
      fprintf(stderr, "Erro ao alocar memória para o artist_id.\n");

      for (int j = 0; j < i; j++) {
        free(newtop10->data[j].artist_id);
      }
      free(newtop10);
      return NULL;
    }
    newtop10->data[i].duration = top10->data[i].duration;
  }
  return newtop10;
}
