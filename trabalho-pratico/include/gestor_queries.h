#ifndef _GESTOR_QUERIES_H_
#define _GESTOR_QUERIES_H_

#include "compare_files.h"
#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestor_history.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "query3.h"
#include "query5.h"

/**
 * @file gestor_queries.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Gestor Queries`.
 */

/**
 * @brief Executa as queries com base na linha de entrada.
 *
 * Esta função analisa o comando fornecido em `line` e chama a função
 * correspondente à query indicada. Ela também calcula o tempo de execução
 * e armazena os resultados no objeto `temposTestes`.
 *
 * @param line Linha de comando que contém a identificação da query e seus
 * parâmetros.
 * @param gestor Pointer para a estrutura de gestores.
 * @param lista Lista de músicas (usada por algumas queries).
 * @param i Índice do gestor (usado em algumas queries).
 * @param t Pointer para a estrutura de tempos de execução.
 */
void gestorQueries(char *line, Gestores *gestor, NodoMusica *lista, int i,
                   temposTestes *t);

#endif // _GESTOR_QUERIES_H_
