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
 * @brief Executa a Query 5 para gerar recomendações baseadas no user alvo.
 *
 * Esta função realiza o processamento de dados e gera recomendações
 * personalizadas com base nas preferências do user alvo. As recomendações
 * são geradas com base nas informações armazenadas na Struct de gestão e
 * podem considerar argumentos adicionais para personalizar ainda mais os
 * resultados.
 *
 * @param gestor Pointer para a Struct de gestão utilizada para armazenar e
 * acessar os dados.
 * @param numRecomendacoes Número de recomendações a serem geradas.
 * @param idUtilizadorAlvo Pointer para o ID do utilizador alvo para as
 * recomendações.
 * @param i Índice do output gerado.
 * @param a Pointer para a Struct que contém argumentos adicionais
 * necessários para a execução da Query 5.
 */
void query5(Gestores *gestor, int numRecomendacoes, char *idUtilizadorAlvo,
            int i, argumentosQuery5 *a);

#endif
