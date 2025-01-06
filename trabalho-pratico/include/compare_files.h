#ifndef _COMPARE_FILES_H_
#define _COMPARE_FILES_H_

/**
 * @file compare_files.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Compare Files`.
 */

typedef struct temposTestes temposTestes;

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

#define MAX_PATH_SIZE 1024

/**
 * @brief Inicializa uma nova instância da struct `temposTestes`.
 *
 * Esta função aloca memória para uma nova struct `temposTestes` e inicializa
 * os tempos acumulados das queries com 0.
 *
 * @return Um pointer para a struct `temposTestes` inicializada, ou `NULL`
 * em caso de falha na alocação de memória.
 */
temposTestes *initTemposTestes();

/**
 * @brief Liberta a memória associada a uma struct `temposTestes`.
 *
 * Esta função desaloca a memória alocada para uma struct `temposTestes`.
 *
 * @param t Pointer para a struct `temposTestes` a ser destruída.
 */
void destroyTemposTestes(temposTestes *t);

/**
 * @brief Obtém o tempo acumulado de uma query específica.
 *
 * Esta função retorna o tempo total acumulado de uma query (1 a 6) da struct
 * `temposTestes`.
 *
 * @param t Pointer para a struct `temposTestes`.
 * @param i O número da query (de 1 a 6) da qual o tempo será recuperado.
 *
 * @return O tempo acumulado da query específica, ou -1 se o índice for
 * inválido.
 */
double getTemposTestes(temposTestes *t, int i);

/**
 * @brief Define o tempo acumulado de uma query específica.
 *
 * Esta função acumula um valor de tempo específico para uma query (1 a 6) na
 * struct `temposTestes`.
 *
 * @param t Pointer para a struct `temposTestes`.
 * @param i O número da query (de 1 a 6) da qual o tempo será alterado.
 * @param val O valor do tempo a ser adicionado à query.
 */
void setTemposTestes(temposTestes *t, int i, double val);

/**
 * @brief Compara dois ficheiros linha por linha.
 *
 * Esta função compara dois ficheiros linha por linha e verifica se são iguais.
 * Retorna `true` se os ficheiros forem idênticos e `false` caso contrário.
 *
 * @param fp1 Pointer para o primeiro ficheiro a ser comparado.
 * @param fp2 Pointer para o segundo ficheiro a ser comparado.
 * @param nQuery Número da query que está a ser comparada.
 * @param i Índice do ficheiro a ser comparado.
 *
 * @return `true` se os ficheiros forem iguais, `false` caso contrário.
 */
bool compareFiles(FILE *fp1, FILE *fp2, int nQuery, int i);

#endif
