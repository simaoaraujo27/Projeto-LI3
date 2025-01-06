/**
 * @file query1.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do query1
 */
#ifndef _QUERIE1_H_
#define _QUERIE1_H_

/**
 * @brief Processa a Query 1 para users.
 *
 * A função recebe uma linha de entrada contendo um id de um user, 
 * procura por este identificador na hashtable de users e gera um ficheiro 
 * com os detalhes do user ou uma linha vazia caso o user não seja encontrado.
 *
 * @param gestorUser Gestor que contém a hash table dos users.
 * @param line Linha de entrada com o identificador do user.
 * @param i Índice usado para nomear o ficheiro.
 * @param temS Flag que indica o formato da escrita (1 para separador '=', 0 para separador ';').
 */
void query1User(gestorUsers *gestorUser, char *line, int i, int temS);

/**
 * @brief Processa a Query 1 para artistas.
 *
 * A função recebe uma linha de entrada contendo um id de um artista, 
 * procura por este id na hashtable de artistas e gera um ficheiro 
 * com os detalhes do artista ou uma linha vazia caso o artista não seja encontrado.
 *
 * @param gestorArtist Gestor que contém a hash table de artistas.
 * @param line Linha de entrada com o identificador do artista.
 * @param i Índice usado para nomear o ficheiro.
 * @param temS Flag que indica o formato de escrita (1 para separador '=', 0 para separador ';').
 */
void query1Artist(gestorArtists *gestorArtist, char *line, int i, int temS);


#endif