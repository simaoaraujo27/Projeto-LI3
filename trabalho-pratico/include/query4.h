/**
 * @file query4.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do query4.h
 */

#ifndef _QUERY4_H_
#define _QUERY4_H_

#include "gestor_musics.h"

/**
 * @brief Armazena valores de uma música em estruturas de gestão.
 *
 * Esta função armazena informações sobre uma música, incluindo sua duração e
 * timestamp, em estruturas de gestão de músicas e artistas, além de atualizar
 * um array com os dados do Top 10.
 *
 * @param musicId Ponteiro para o ID da música (string).
 * @param duration Duração da música em segundos.
 * @param timeStamp Tempo em dias desde o dia 9/9/2024.
 * @param gestorMusics Ponteiro para a estrutura de gestão de músicas.
 * @param gestorArtists Ponteiro para a estrutura de gestão de artistas.
 * @param Tops10 Ponteiro para um array que contém os dados do Top 10.
 * @return Não há valor de retorno.
 */
void armazenarValores(char *musicId, int duration, int timeStamp,
                      gestorMusics *gestorMusics, gestorArtists *gestorArtists,
                      GArray *Tops10);

/**
 * @brief Executa a Query 4 para processar dados entre intervalos de datas.
 *
 * Esta função realiza o processamento de dados de artistas dentro de um
 * intervalo de datas especificado. O processamento considera as informações
 * armazenadas na estrutura de gestão de artistas e retorna os resultados de
 * acordo com o formato de resposta indicado.
 *
 * @param gestorArtists Ponteiro para a estrutura de gestão de artistas.
 * @param DataFim Ponteiro para a data final do intervalo (string).
 * @param DataInicio Ponteiro para a data inicial do intervalo (string).
 * @param contadorOutputs Contador para os outputs gerados.
 * @param temS Indicador do tipo de resposta (1 para '=' e 0 para ';').
 * @return Não há valor de retorno.
 */
void query4(gestorArtists *gestorArtists, char *DataFim, char *DataInicio,
            int contadorOutputs, int temS);

#endif