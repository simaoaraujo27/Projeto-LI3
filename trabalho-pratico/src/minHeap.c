#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura a ser armazenada na min-heap
typedef struct {
  char *artist_id; // ID do artista
  int duration;    // Duração em segundos
} HeapNode;

// Estrutura da min-heap: a capacidade máxima é 10 uma vez que queremos o top10
typedef struct {
  HeapNode data[10];
  int size; // Número atual de elementos na heap
} MinHeap;

void setHeapNode(HeapNode *heapNode, char *artistId, int duration) {
  heapNode->artist_id = artistId;
  heapNode->duration = duration;
}

int getMinHeapSize(MinHeap *h) { return h->size; }

char *getHeapNodeArtistId(HeapNode *HeapNode) { return HeapNode->artist_id; }

// Função para obter a duração de um nó da heap
int getHeapNodeDuration(HeapNode *heapNode) { return heapNode->duration; }

// Função para obter o nó raiz da heap (menor elemento)
HeapNode *getMinHeapFstHeapNode(MinHeap *minHeap) { return &minHeap->data[0]; }

// Função para criar uma nova min-heap
MinHeap *createMinHeap() {
  MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
  heap->size = 0;
  return heap;
}

// Função para trocar dois nós na heap
void swapNodes(HeapNode *a, HeapNode *b) {
  HeapNode temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(MinHeap *heap, int i) {
  int smallest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  // Verificar o filho esquerdo
  if (left < heap->size) {
    if (heap->data[left].duration < heap->data[smallest].duration ||
        (heap->data[left].duration == heap->data[smallest].duration &&
         strcmp(heap->data[left].artist_id, heap->data[smallest].artist_id) <
             0)) {
      smallest = left;
    }
  }

  // Verificar o filho direito
  if (right < heap->size) {
    if (heap->data[right].duration < heap->data[smallest].duration ||
        (heap->data[right].duration == heap->data[smallest].duration &&
         strcmp(heap->data[right].artist_id, heap->data[smallest].artist_id) <
             0)) {
      smallest = right;
    }
  }

  // Trocar e continuar ajustando se necessário
  if (smallest != i) {
    swapNodes(&heap->data[i], &heap->data[smallest]);
    heapify(heap, smallest);
  }
}

// Função para inserir um elemento na min-heap
void insertMinHeap(MinHeap *heap, int totalDuration, int durationMinNode,
                   HeapNode *minNode, char *currentArtist) {
  // Verificar se a heap está cheia
  if (heap->size == 10) {
    // Substituir o maior elemento (raiz) se o novo for menor
    if ((durationMinNode < totalDuration) ||
        (durationMinNode == totalDuration &&
         strcmp(currentArtist, getHeapNodeArtistId(minNode)) < 0)) {
      free(heap->data[0].artist_id); // Liberar o ID do menor elemento
      heap->data[0].artist_id = strdup(currentArtist);
      heap->data[0].duration = totalDuration;
      heapify(heap, 0); // Reorganizar a heap

      return;
    }
  }

  // Adicionar no final e ajustar
  int i = heap->size++;
  heap->data[i].artist_id = strdup(currentArtist);
  heap->data[i].duration = totalDuration;

  // Subir o elemento para a posição correta
  while (i > 0 && heap->data[i].duration < heap->data[(i - 1) / 2].duration) {
    swapNodes(&heap->data[i], &heap->data[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

// Função para remover o menor elemento da heap (extração da raiz)
HeapNode extractMin(MinHeap *heap) {
  if (heap->size == 0) {
    fprintf(stderr, "Erro: a heap está vazia.\n");
    exit(EXIT_FAILURE);
  }

  HeapNode root = heap->data[0];
  heap->data[0] = heap->data[--heap->size];
  heapify(heap, 0);

  return root;
}

// Função para liberar a memória da min-heap
void freeMinHeap(MinHeap *heap) {
  for (int i = 0; i < heap->size; i++) {
    free(heap->data[i].artist_id); // Liberar a memória do ID do artista
  }
  free(heap);
}
