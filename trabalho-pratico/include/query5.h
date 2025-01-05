/**
 * @file query5.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do query5.h
 */

#ifndef _QUERY5_H_
#define _QUERY5_H_

#include "argumentos_query5.h"
#include "gestores.h"

/**
 * @brief Executa a Query 5 para gerar recomendações baseadas no usuário alvo.
 *
 * Esta função realiza o processamento de dados e gera recomendações
 * personalizadas com base nas preferências do usuário alvo. As recomendações
 * são geradas com base nas informações armazenadas na estrutura de gestão e
 * podem considerar argumentos adicionais para personalizar ainda mais os
 * resultados.
 *
 * @param gestor Ponteiro para a estrutura de gestão utilizada para armazenar e
 * acessar os dados.
 * @param numRecomendacoes Número de recomendações a serem geradas.
 * @param idUtilizadorAlvo Ponteiro para o ID do utilizador alvo para as
 * recomendações.
 * @param i Índice do output gerado.
 * @param a Ponteiro para a estrutura que contém argumentos adicionais
 * necessários para a execução da Query 5.
 * @return Não há valor de retorno.
 */
void query5(Gestores *gestor, int numRecomendacoes, char *idUtilizadorAlvo,
            int i, argumentosQuery5 *a);

#endif
