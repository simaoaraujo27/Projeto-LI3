#ifndef _TOP10QUERY4_H
#define _TOP10QUERY4_H

#include <stdlib.h>
#include <string.h>

// Estrutura para os nós da top10
typedef struct NodoArray {
  char *artist_id; // ID do artista
  int duration;    // Duração em segundos
} NodoArray;

// Estrutura para a min-top10
typedef struct ArrayTop10 {
  NodoArray data[10]; // Array fixo para os 10 maiores elementos
  int size;           // Número atual de elementos na top10
} ArrayTop10;

NodoArray menorNodoArray(ArrayTop10 *top10, int *indice);

char *getNodoArrayArtistId(NodoArray *NodoArray);

int getArrayTop10Size(ArrayTop10 *h);

// Função para obter a duração de um nó da top10
int getNodoArrayDuration(NodoArray *NodoArray);

NodoArray *getArrayTop10NodoArray(ArrayTop10 *ArrayTop10, int i);

// Função para criar uma nova min-top10
ArrayTop10 *createArrayTop10();

// Função para inserir um elemento na min-top10
void insertArrayTop10(ArrayTop10 *top10, int totalDuration, int durationMinNode,
                      NodoArray *minNode, char *currentArtist,
                      int indiceMinNode);

// Função para liberar a memória da min-top10
void freeArrayTop10(ArrayTop10 *top10);

ArrayTop10 *cloneArrayTop10(ArrayTop10 *top10);

#endif // MIN_top10_H
