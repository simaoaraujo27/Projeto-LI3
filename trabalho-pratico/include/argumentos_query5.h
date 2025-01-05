/**
 * @file argumentos_query5.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do argumentos_query5
 */

#ifndef _ARGUMENTOS_QUERY5_H_
#define _ARGUMENTOS_QUERY5_H_

typedef struct argumentosQuery5 argumentosQuery5;

#include "gestores.h"

argumentosQuery5 *initArgumentosQuery5();

int getArgumentosQuery5NumUtilizadores(argumentosQuery5 *a);

int getArgumentosQuery5NumGeneros(argumentosQuery5 *a);

int **getArgumentosQuery5MatrizClassificacaoMusicas(argumentosQuery5 *a);

char **getArgumentosQuery5NomesGeneros(argumentosQuery5 *a);

char **getArgumentosQuery5IdsUtilizadores(argumentosQuery5 *a);

void alocaMatriz(Gestores *gestor, argumentosQuery5 *a);
void constroiQuery5(Gestores *gestor, argumentosQuery5 *a);
void destroiArgumentosQuery5(argumentosQuery5 *a);

#endif