/**
 * @file argumentos_query5.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do argumentos_query5
 */

#ifndef _ARGUMENTOS_QUERY5_H_
#define _ARGUMENTOS_QUERY5_H_

typedef struct argumentosQuery5 argumentosQuery5;

#include "gestores.h"

/**
 * @brief Cria uma nova instância de `argumentosQuery5`.
 *
 * Esta função aloca memória e inicializa todos os campos de uma struct
 * `argumentosQuery5`.
 *
 *
 * @return Um pointer para a struct `argumentosQuery5` inicializada ou NULL em
 * caso de falha.
 */
argumentosQuery5 *initArgumentosQuery5();

/**
 * @brief Obtém o número de utilizadores.
 *
 * Esta função retorna o valor do campo `numUtilizadores` de uma struct
 * `argumentosQuery5`.
 *
 * @param a Pointer para a struct `argumentosQuery5`.
 * @return O número de utilizadores.
 */
int getArgumentosQuery5NumUtilizadores(argumentosQuery5 *a);

/**
 * @brief Obtém o número de géneros.
 *
 * Esta função retorna o valor do campo `numGeneros` de uma struct
 * `argumentosQuery5`.
 *
 * @param a Pointer para a struct `argumentosQuery5`.
 * @return O número de géneros.
 */
int getArgumentosQuery5NumGeneros(argumentosQuery5 *a);

/**
 * @brief Obtém a matriz de classificação das músicas.
 *
 * Esta função retorna o pointer para o campo `matrizClassificacaoMusicas` de
 * uma struct `argumentosQuery5`.
 *
 * @param a Pointer para a struct `argumentosQuery5`.
 * @return O pointer para a matriz de classificação.
 */
int **getArgumentosQuery5MatrizClassificacaoMusicas(argumentosQuery5 *a);

/**
 * @brief Obtém os nomes dos géneros.
 *
 * Esta função retorna o pointer para o campo `nomesGeneros` de uma struct
 * `argumentosQuery5`.
 *
 * @param a Pointer para a struct `argumentosQuery5`.
 * @return Um pointer para o array de strings com os nomes dos géneros.
 */
char **getArgumentosQuery5NomesGeneros(argumentosQuery5 *a);

/**
 * @brief Obtém os IDs dos utilizadores.
 *
 * Esta função retorna o pointer para o campo `idsUtilizadores` de uma struct
 * `argumentosQuery5`.
 *
 * @param a pointer para a struct `argumentosQuery5`.
 * @return Um pointer para o array de strings com os IDs dos utilizadores.
 */
char **getArgumentosQuery5IdsUtilizadores(argumentosQuery5 *a);

/**
 * @brief Aloca e inicializa a matriz e outros campos na struct `argumentosQuery5`.
 *
 * Esta função inicializa os campos `matrizClassificacaoMusicas`, `nomesGeneros`
 * e `idsUtilizadores` de uma struct `argumentosQuery5`, com base nos dados
 * fornecidos pelo gestor.
 *
 * @param gestor Pointer para a struct `Gestores` que contém os dados.
 * @param a Pointer para a struct `argumentosQuery5` a ser preenchida.
 */
void alocaMatriz(Gestores *gestor, argumentosQuery5 *a);

/**
 * @brief Constrói os dados necessários para a Query 5.
 *
 * Esta função preenche os campos da struct `argumentosQuery5`, incluindo a
 * matriz de classificação e ajusta os nomes dos géneros.
 *
 * @param gestor Pointer para a struct `Gestores` com os dados.
 * @param a Pointer para a struct `argumentosQuery5` a ser preenchida.
 */
void constroiQuery5(Gestores *gestor, argumentosQuery5 *a);

/**
 * @brief Liberta a memória associada a uma struct `argumentosQuery5`.
 *
 * Esta função liberta a memória alocada para todos os campos e para a própria
 * struct `argumentosQuery5`.
 *
 * @param a Pointer para a struct `argumentosQuery5` a ser destruída.
 */
void destroiArgumentosQuery5(argumentosQuery5 *a);

#endif
