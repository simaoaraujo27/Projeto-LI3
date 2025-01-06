/**
 * @file query6.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do query6.h
 */

#ifndef _QUERY6_H_
#define _QUERY6_H_

#include "gestor_users.h"

/**
 * @brief Executa a Query 6 para processar dados de um user específico
 * baseado no ano e em critérios adicionais.
 *
 * Esta função realiza a análise de dados de um user específico, considerando
 * o ano informado e critérios adicionais para gerar uma lista dos artistas mais
 * ouvidos pelo user.
 *
 * @param user_id Pointer para o ID do user alvo.
 * @param year Ano a ser considerado para a análise.
 * @param N Número de artistas mais ouvidos a serem listados.
 * @param gestorUsers Pointer para a Struct de gestão de users que contém
 * os dados.
 * @param i Índice do output gerado.
 * @param temS Indicador do tipo de resposta (1 para '=' e 0 para ';').
 */
void query6(char *user_id, int year, int N, gestorUsers *gestorUsers, int i,
            int temS);

#endif
