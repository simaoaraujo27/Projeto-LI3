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
 * @brief Armazena valores de uma música em Structs de gestão.
 *
 * Esta função armazena informações sobre uma música, incluindo sua duração e
 * timestamp, em Structs de gestão de músicas e artistas, além de atualizar
 * um array com os dados do Top 10.
 *
 * @param musicId Pointer para o ID da música (string).
 * @param duration Duração da música em segundos.
 * @param timeStamp Tempo em dias desde o dia 9/9/2024.
 * @param gestorMusics Pointer para a Struct de gestão de músicas.
 * @param gestorArtists Pointer para a Struct de gestão de artistas.
 * @param Tops10 Pointer para um array que contém os dados do Top 10.
 */
void armazenarValores(char *musicId, int duration, int timeStamp,
                      gestorMusics *gestorMusics, gestorArtists *gestorArtists,
                      GArray *Tops10);

/**
 * @brief Executa a Query 4 para processar dados entre intervalos de datas.
 *
 * Esta função realiza o processamento de dados de artistas dentro de um
 * intervalo de datas especificado. O processamento considera as informações
 * armazenadas na Struct de gestão de artistas e retorna os resultados de
 * acordo com o formato de resposta indicado.
 *
 * @param gestorArtists Pointer para a Struct de gestão de artistas.
 * @param DataFim Pointer para a data final do intervalo (string).
 * @param DataInicio Pointer para a data inicial do intervalo (string).
 * @param contadorOutputs Contador para os outputs gerados.
 * @param temS Indicador do tipo de resposta (1 para '=' e 0 para ';').
 */
void query4(gestorArtists *gestorArtists, char *DataFim, char *DataInicio,
            int contadorOutputs, int temS);

#endif