#include "query4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura a ser armazenada na min-heap
typedef struct {
    char* artist_id;  // ID do artista
    int duration;     // Duração em segundos
} HeapNode;

// Estrutura da min-heap: a capacidade máxima é 10 uma vez que queremos o top10
typedef struct {
    HeapNode* data;   
    int size;         // Número atual de elementos na heap
} MinHeap;

MinHeap* create_min_heap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * 10);
    heap->size = 0;
    return heap;
}

void swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void insert_min_heap(MinHeap* heap, char* artist_id, int duration) {

    // Adicionar no final e ajustar
    int i = heap->size++;
    heap->data[i].artist_id = strdup(artist_id);
    heap->data[i].duration = duration;

    // Subir o elemento para a posição correta
    while (i > 0 && heap->data[i].duration < heap->data[(i - 1) / 2].duration) {
        swap_nodes(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left].duration < heap->data[smallest].duration)
        smallest = left;

    if (right < heap->size && heap->data[right].duration < heap->data[smallest].duration)
        smallest = right;

    if (smallest != i) {
        swap_nodes(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

HeapNode extract_min(MinHeap* heap) {

    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);

    return root;
}

void free_min_heap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        free(heap->data[i].artist_id); // Liberar a memória do ID do artista
    }
    free(heap->data);
    free(heap);
}


/*
enquanto é feito o parser de history:
  - ver o music_id
    - atraves do music_id sacar o artist_id da musica
  - ver a duration
  - ver o timestamp (data)

atraves do timestamp: 
distancia em dias entre a data limite (9 de setembro) e a data que queremos calcular
e depois dividir por 7 -> da o indice da semana a ver no array dinamico

array dinamico de minheaps de structs -> cada struct tem o artist_id e a duracao total nessa semana
cada posicao do array corresponde a uma semana; 
a minheap é atraves da duracão (o menor fica no inicio) e tem tamanho 10

*/