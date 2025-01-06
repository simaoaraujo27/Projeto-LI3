/**
 * @file outputResult.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do outputResult
 */
#ifndef _OUTPUT_RESULT_H_
#define _OUTPUT_RESULT_H_

#include <glib.h>
#include <stdio.h>

/**
 * @brief Escreve o resultado da Query 2 num ficheiro.
 *
 * Imprime uma lista de artistas, incluindo o nome, tipo, discografia em formato HH:MM:SS
 * e o país, filtrando por país se necessário.
 *
 * @param listaResposta Lista contendo os artistas a serem impressos.
 * @param newFile Pointer para o ficheiro onde os resultados serão escritos.
 * @param numeroArtists Número máximo de artistas a imprimir.
 * @param temS Flag que indica se o separador deve ser '=' (1) ou ';' (0).
 * @param country String do país a ser filtrado, ou NULL para incluir todos os países.
 */
void printQuery2(GList *listaResposta, FILE *newFile, int numeroArtists, int temS, char *country);

/**
 * @brief Escreve o resultado da Query 4 num ficheiro.
 *
 * Imprime informações sobre um nome, tipo e a contagem de aparições no Top 10.
 *
 * @param newFile Pointer para o ficheiro onde os resultados serão escritos.
 * @param temS Flag que indica se o separador deve ser '=' (1) ou ';' (0).
 * @param name String com o nome do artista.
 * @param type String com o tipo do artista.
 * @param countTop10 Número de vezes que o artista apareceu no Top 10.
 */
void printQuery4(FILE *newFile, int temS, char *name, char *type, int countTop10);

/**
 * @brief Escreve texto num ficheiro e fecha-o.
 *
 * @param newFile Pointer para o ficheiro onde o texto será escrito.
 * @param text Texto a ser escrito no ficheiro.
 */
void writeFile(FILE *newFile, char *text);

/**
 * @brief Escreve o resultado da Query 1 para um user num ficheiro.
 *
 * Inclui informações como email, nome, sobrenome, idade e país do user.
 *
 * @param orig_key Dados do user.
 * @param newFile Pointer para o ficheiro onde os resultados serão escritos.
 * @param temS Flag que indica se o separador deve ser '=' (1) ou ';' (0).
 */
void printQuery1User(gpointer orig_key, FILE *newFile, int temS);

/**
 * @brief Escreve o resultado da Query 1 para um artista num ficheiro.
 *
 * Inclui informações como nome, tipo, país, número de álbuns individuais e receita total.
 *
 * @param orig_key Dados do artista.
 * @param newFile Pointer para o ficheiro onde os resultados serão escritos.
 * @param temS Flag que indica se o separador deve ser '=' (1) ou ';' (0).
 */
void printQuery1Artist(gpointer orig_key, FILE *newFile, int temS);

#endif