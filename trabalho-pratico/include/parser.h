/**
 * @file parser.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do parser
 */
#ifndef _PARSER_H_
#define _PARSER_H_

#include "gestores.h"
#include <stdio.h>

/**
 * @brief Realiza o parsing dos arquivos CSV e processa os dados.
 *
 * A função aloca memória para os paths completos dos arquivos CSV, constrói os paths
 * para os arquivos de artistas, músicas, usuários, álbuns e histórico. Em seguida, 
 * chama funções para processar os dados dos arquivos e preencher as respectivas estruturas.
 * No final, a função liberta a memória alocada para os paths e retorna um valor indicando
 * o sucesso ou falha no processamento.
 *
 * @param gestor Gestor contendo as estruturas necessárias para o parsing.
 * @param path Caminho base para onde os arquivos CSV estão localizados.
 * @param fp Ponteiro para o arquivo de entrada (historico.csv) que será processado.
 * 
 * @return 1 se o parsing foi bem-sucedido, 0 se ocorreu alguma falha.
 */
int GestorParsers(Gestores *gestor, char *path, FILE *fp);

#endif