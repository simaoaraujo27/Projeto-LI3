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

HeapNode menorHeapNode(MinHeap *heap, int *indice) {
  HeapNode menor = heap->data[0];
  for (int i = 0; i < heap->size; i++) {
    if (heap->data[i].duration < menor.duration) {
      menor = heap->data[i];
      *indice = i;
    } else if (heap->data[i].duration == menor.duration &&
               strcmp(menor.artist_id, heap->data[i].artist_id) < 0) {
      menor = heap->data[i];
      *indice = i;
    }
  }
  return menor;
}

void setHeapNode(HeapNode *heapNode, char *artistId, int duration) {
  heapNode->artist_id = artistId;
  heapNode->duration = duration;
}

void removeMinHeap(MinHeap *minheap, int indice) {
  minheap = NULL;
  if (indice && minheap) {
  }
}

int getMinHeapSize(MinHeap *h) { return h->size; }

char *getHeapNodeArtistId(HeapNode *HeapNode) {
  return strdup(HeapNode->artist_id);
}

// Função para obter a duração de um nó da heap
int getHeapNodeDuration(HeapNode *heapNode) { return heapNode->duration; }

// Função para obter o nó raiz da heap (menor elemento)
HeapNode *getMinHeapFstHeapNode(MinHeap *minHeap) { return &minHeap->data[0]; }

HeapNode *getMinHeapHeapNode(MinHeap *minHeap, int i) {
  return &minHeap->data[i];
}

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

int elemMinHeap(char *currentArtist, HeapNode data[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (strcmp(data[i].artist_id, currentArtist) == 0) {
      return i;
    }
  }
  return -1;
}

// Função para inserir um elemento na min-heap
void insertMinHeap(MinHeap *heap, int totalDuration, int durationMinNode,
                   HeapNode *minNode, char *currentArtist, int indiceMinNode) {
  if (!heap || !currentArtist)
    return; // Validações básicas

  int indice = elemMinHeap(currentArtist, heap->data, heap->size);

  // Verificar se a heap está cheia
  if (indice != -1) {
    heap->data[indice].duration = totalDuration;
    return;
  }

  if (heap->size == 10) {
    char *heapNodeArtistId = getHeapNodeArtistId(minNode);
    if (!heapNodeArtistId)
      return;

    // Substituir o maior elemento (raiz) se o novo for menor
    if ((durationMinNode < totalDuration) ||
        (durationMinNode == totalDuration &&
         strcmp(currentArtist, heapNodeArtistId) < 0)) {
      if (heap->data[indiceMinNode].artist_id != NULL) {
        free(heap->data[indiceMinNode].artist_id);
      }

      heap->data[indiceMinNode].artist_id = strdup(currentArtist);
      if (!heap->data[indiceMinNode].artist_id) {
        free(heapNodeArtistId);
        return;
      }
      heap->data[indiceMinNode].duration = totalDuration;
    }
    free(heapNodeArtistId);
    return;
  }

  // Adicionar no final e ajustar
  int i = heap->size++;
  heap->data[i].artist_id = strdup(currentArtist);

  // Verificar falha em strdup
  if (!heap->data[i].artist_id) {
    heap->size--; // Reverter incremento se falhar
    return;
  }
  heap->data[i].duration = totalDuration;
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

void freeMinHeap(MinHeap *heap) {
  if (heap != NULL) { // Verifica se a heap não é NULL
    for (int i = 0; i < heap->size; i++) {
      if (heap->data[i].artist_id != NULL) { // Libera cada artist_id se alocado
        free(heap->data[i].artist_id);
        heap->data[i].artist_id = NULL; // Prevenção de uso de ponteiro inválido
      }
    }
    free(heap);  // Libera a estrutura da heap
    heap = NULL; // Prevenção de uso de ponteiro inválido
  }
}

MinHeap *cloneMinHeap(MinHeap *heap) {
  if (!heap) {
    return NULL; // Retorna NULL se a heap original for NULL
  }

  // Aloca memória para a nova heap
  MinHeap *newHeap = createMinHeap();
  if (!newHeap) {
    fprintf(stderr, "Erro ao alocar memória para a nova heap.\n");
    return NULL;
  }

  // Copia o tamanho da heap
  newHeap->size = heap->size;

  // Copia cada nó da heap original para a nova
  for (int i = 0; i < heap->size; i++) {
    newHeap->data[i].artist_id = strdup(heap->data[i].artist_id);
    if (!newHeap->data[i].artist_id) {
      fprintf(stderr, "Erro ao alocar memória para o artist_id.\n");

      // Libera os nós já alocados em caso de erro
      for (int j = 0; j < i; j++) {
        free(newHeap->data[j].artist_id);
      }
      free(newHeap);
      return NULL;
    }

    // Copia a duração
    newHeap->data[i].duration = heap->data[i].duration;
  }

  return newHeap; // Retorna a nova heap clonada
}
