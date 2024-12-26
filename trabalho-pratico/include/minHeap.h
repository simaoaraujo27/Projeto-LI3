#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdlib.h>
#include <string.h>

// Estrutura para os nós da heap
typedef struct heapNode {
  char *artist_id; // ID do artista
  int duration;    // Duração em segundos
} HeapNode;

// Estrutura para a min-heap
typedef struct minHeap {
  HeapNode data[10]; // Array fixo para os 10 maiores elementos
  int size;          // Número atual de elementos na heap
} MinHeap;

void setHeapNode(HeapNode *heapNode, char *artistId, int duration);

char *getHeapNodeArtistId(HeapNode *HeapNode);

int getMinHeapSize(MinHeap *h);

// Função para obter a duração de um nó da heap
int getHeapNodeDuration(HeapNode *heapNode);

HeapNode *getMinHeapFstHeapNode(MinHeap *minHeap);

// Função para criar uma nova min-heap
MinHeap *createMinHeap();

// Função para trocar dois nós na heap
void swapNodes(HeapNode *a, HeapNode *b);

// Função para inserir um elemento na min-heap
void insertMinHeap(MinHeap *heap, int totalDuration, int durationMinNode,
                   HeapNode *minNode, char *currentArtist);

// Função para reorganizar a heap a partir de um índice
void heapify(MinHeap *heap, int i);

// Função para remover o menor elemento da heap (extração da raiz)
HeapNode *extractMin(MinHeap *heap);

// Função para liberar a memória da min-heap
void freeMinHeap(MinHeap *heap);

#endif // MIN_HEAP_H
