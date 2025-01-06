/**
 * @file top10query4.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file para manipulação da Struct Top 10 para Query 4
 */

#ifndef _TOP10QUERY4_H
#define _TOP10QUERY4_H

#include <stdlib.h>
#include <string.h>

/**
 * @brief Struct para os nós do Top 10.
 *
 * Esta Struct armazena o ID do artista e a duração em segundos.
 */
typedef struct NodoArray {
  char *artist_id;
  int duration;
} NodoArray;

/**
 * @brief Struct para o Top 10.
 *
 * Esta Struct armazena os 10 maiores elementos em um array fixo.
 */
typedef struct ArrayTop10 {
  NodoArray data[10];
  int size;
} ArrayTop10;

/**
 * @brief Obtém o nó com menor duração no Top 10.
 *
 * @param top10 Pointer para a Struct ArrayTop10.
 * @param indice Pointer para armazenar o índice do menor nó.
 * @return Struct NodoArray com o menor valor encontrado.
 */
NodoArray menorNodoArray(ArrayTop10 *top10, int *indice);

/**
 * @brief Obtém o ID do artista de um nó da Struct.
 *
 * @param NodoArray Pointer para a Struct NodoArray.
 * @return Pointer para a string contendo o ID do artista.
 */
char *getNodoArrayArtistId(NodoArray *NodoArray);

/**
 * @brief Obtém o tamanho atual do Top 10.
 *
 * @param h Pointer para a Struct ArrayTop10.
 * @return O tamanho atual do Top 10.
 */
int getArrayTop10Size(ArrayTop10 *h);

/**
 * @brief Obtém a duração de um nó da Struct.
 *
 * @param NodoArray Pointer para a Struct NodoArray.
 * @return Duração em segundos do nó especificado.
 */
int getNodoArrayDuration(NodoArray *NodoArray);

/**
 * @brief Obtém um nó específico do Top 10.
 *
 * @param ArrayTop10 Pointer para a Struct ArrayTop10.
 * @param i Índice do nó desejado.
 * @return Pointer para o nó solicitado.
 */
NodoArray *getArrayTop10NodoArray(ArrayTop10 *ArrayTop10, int i);

/**
 * @brief Cria e inicializa um novo Top 10.
 *
 * @return Pointer para a nova Struct ArrayTop10.
 */
ArrayTop10 *createArrayTop10();

/**
 * @brief Insere um novo elemento no Top 10.
 *
 * @param top10 Pointer para a Struct ArrayTop10.
 * @param totalDuration Duração total acumulada.
 * @param durationMinNode Duração do nó de menor valor.
 * @param minNode Pointer para o nó de menor valor.
 * @param currentArtist ID do artista atual.
 * @param indiceMinNode Índice do nó de menor valor.
 */
void insertArrayTop10(ArrayTop10 *top10, int totalDuration, int durationMinNode,
                      NodoArray *minNode, char *currentArtist,
                      int indiceMinNode);

/**
 * @brief Liberta a memória alocada para o Top 10.
 *
 * @param top10 Pointer para a Struct ArrayTop10 a ser libertada.
 */
void freeArrayTop10(ArrayTop10 *top10);

/**
 * @brief Clona uma Struct Top 10 existente.
 *
 * @param top10 Pointer para a Struct ArrayTop10 a ser clonada.
 * @return Pointer para a nova Struct clonada.
 */
ArrayTop10 *cloneArrayTop10(ArrayTop10 *top10);

#endif // _TOP10QUERY4_H
