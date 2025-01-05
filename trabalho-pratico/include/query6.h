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
 * @brief Executa a Query 6 para processar dados de um usuário específico
 * baseado no ano e em critérios adicionais.
 *
 * Esta função realiza a análise de dados de um usuário específico, considerando
 * o ano informado e critérios adicionais para gerar uma lista dos artistas mais
 * ouvidos pelo usuário.
 *
 * @param user_id Ponteiro para o ID do usuário alvo.
 * @param year Ano a ser considerado para a análise.
 * @param N Número de artistas mais ouvidos a serem listados.
 * @param gestorUsers Ponteiro para a estrutura de gestão de usuários que contém
 * os dados.
 * @param i Índice do output gerado.
 * @param temS Indicador do tipo de resposta (1 para '=' e 0 para ';').
 * @return Não há valor de retorno.
 */
void query6(char *user_id, int year, int N, gestorUsers *gestorUsers, int i,
            int temS);

#endif
