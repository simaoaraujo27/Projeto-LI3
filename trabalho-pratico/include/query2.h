/**
 * @file query2.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do query2
 */
#ifndef _QUERY2_H_
#define _QUERY2_H_

#include "gestores.h"

/**
 * @brief Processa a Query 2 para listar artistas.
 *
 * A função recebe o número de artistas a listar, um filtro opcional por país,
 * e o gestor de dados. Em seguida, gera um ficheiro contendo os 
 * resultados com base nos parâmetros fornecidos. Caso o número de artistas 
 * seja 0, o ficheiro será uma linha vazia.
 *
 * @param numeroArtistas Número máximo de artistas a incluir na saída. Se for 0, 
 *                       nenhum artista será listado.
 * @param country Filtro opcional por país. Se NULL, todos os países são considerados.
 * @param gestor Gestor que contêm as informações necessárias para a query.
 * @param i Índice usado para nomear o ficheiro.
 * @param temS Flag indicando o formato de escrita (1 para separador '=', 0 para separador ';').
 */
void query2(int numeroArtistas, char *country, Gestores *gestor, int i,
            int temS);

#endif