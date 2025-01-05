/**
 * @file top10query4.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file para manipulação da estrutura Top 10 para Query 4
 */

#ifndef _TOP10QUERY4_H
#define _TOP10QUERY4_H

#include <stdlib.h>
#include <string.h>

/**
 * @brief Estrutura para os nós do Top 10.
 *
 * Esta estrutura armazena o ID do artista e a duração em segundos.
 */
typedef struct NodoArray {
  char *artist_id; /**< ID do artista. */
  int duration;    /**< Duração em segundos. */
} NodoArray;

/**
 * @brief Estrutura para o Top 10.
 *
 * Esta estrutura armazena os 10 maiores elementos em um array fixo.
 */
typedef struct ArrayTop10 {
  NodoArray data[10]; /**< Array fixo para os 10 maiores elementos. */
  int size;           /**< Número atual de elementos na top10. */
} ArrayTop10;

/**
 * @brief Obtém o nó com menor duração no Top 10.
 *
 * @param top10 Ponteiro para a estrutura ArrayTop10.
 * @param indice Ponteiro para armazenar o índice do menor nó.
 * @return Estrutura NodoArray com o menor valor encontrado.
 */
NodoArray menorNodoArray(ArrayTop10 *top10, int *indice);

/**
 * @brief Obtém o ID do artista de um nó da estrutura.
 *
 * @param NodoArray Ponteiro para a estrutura NodoArray.
 * @return Ponteiro para a string contendo o ID do artista.
 */
char *getNodoArrayArtistId(NodoArray *NodoArray);

/**
 * @brief Obtém o tamanho atual do Top 10.
 *
 * @param h Ponteiro para a estrutura ArrayTop10.
 * @return O tamanho atual do Top 10.
 */
int getArrayTop10Size(ArrayTop10 *h);

/**
 * @brief Obtém a duração de um nó da estrutura.
 *
 * @param NodoArray Ponteiro para a estrutura NodoArray.
 * @return Duração em segundos do nó especificado.
 */
int getNodoArrayDuration(NodoArray *NodoArray);

/**
 * @brief Obtém um nó específico do Top 10.
 *
 * @param ArrayTop10 Ponteiro para a estrutura ArrayTop10.
 * @param i Índice do nó desejado.
 * @return Ponteiro para o nó solicitado.
 */
NodoArray *getArrayTop10NodoArray(ArrayTop10 *ArrayTop10, int i);

/**
 * @brief Cria e inicializa um novo Top 10.
 *
 * @return Ponteiro para a nova estrutura ArrayTop10.
 */
ArrayTop10 *createArrayTop10();

/**
 * @brief Insere um novo elemento no Top 10.
 *
 * @param top10 Ponteiro para a estrutura ArrayTop10.
 * @param totalDuration Duração total acumulada.
 * @param durationMinNode Duração do nó de menor valor.
 * @param minNode Ponteiro para o nó de menor valor.
 * @param currentArtist ID do artista atual.
 * @param indiceMinNode Índice do nó de menor valor.
 */
void insertArrayTop10(ArrayTop10 *top10, int totalDuration, int durationMinNode,
                      NodoArray *minNode, char *currentArtist,
                      int indiceMinNode);

/**
 * @brief Libera a memória alocada para o Top 10.
 *
 * @param top10 Ponteiro para a estrutura ArrayTop10 a ser liberada.
 */
void freeArrayTop10(ArrayTop10 *top10);

/**
 * @brief Clona uma estrutura Top 10 existente.
 *
 * @param top10 Ponteiro para a estrutura ArrayTop10 a ser clonada.
 * @return Ponteiro para a nova estrutura clonada.
 */
ArrayTop10 *cloneArrayTop10(ArrayTop10 *top10);

#endif // _TOP10QUERY4_H
