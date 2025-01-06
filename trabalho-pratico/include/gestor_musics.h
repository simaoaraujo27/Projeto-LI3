#ifndef _GESTORMUSICS_H_
#define _GESTORMUSICS_H_

/**
 * @file gestor_musics.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Gestor Musics`.
 */

typedef struct gestorMusics gestorMusics;

#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "musics.h"
#include <glib.h>
#include <stdio.h>

/**
 * @brief Inicializa o gestor de músicas e todos os seus campos.
 *
 * Cria e inicializa a hash table para armazenar as músicas e os géneros,
 * além de inicializar o contador de géneros.
 *
 * @return gestorMusics* Pointer para o gestor de músicas recém-inicializado.
 */
gestorMusics *initGestorMusics();

/**
 * @brief Liberta a memória alocada para o gestor de músicas.
 *
 * Liberta a memória das hash tables e do contador de géneros do gestor de
 * músicas.
 *
 * @param gestor Pointer para o gestor de músicas a ser libertado.
 */
void freeGestorMusics(gestorMusics *gestor);

/**
 * @brief Obtém o número total de géneros distintos armazenados no gestor de
 * músicas.
 *
 * @param gestorMusic Pointer para o gestor de músicas.
 * @return int Número de géneros distintos.
 */
int getMusicsNGenres(gestorMusics *gestorMusic);

/**
 * @brief Insere os géneros presentes no gestor de músicas numa array.
 *
 * Cria uma array contendo todos os géneros distintos presentes na hash table de
 * géneros.
 *
 * @param gestorMusics Pointer para o gestor de músicas.
 * @param numGeneros Número de géneros presentes.
 * @return char** Array de strings contendo os géneros.
 */
char **insertGenreToArray(gestorMusics *gestorMusics, int numGeneros);

/**
 * @brief Procura uma música na hash table de músicas.
 *
 * Pesquisa uma música utilizando o seu ID.
 *
 * @param gestorMusic Pointer para o gestor de músicas.
 * @param line ID da música a ser procurado.
 * @param value Pointer para armazenar o valor (música) encontrado.
 * @param orig_key Pointer para armazenar a chave original da música.
 * @return gboolean TRUE se a música for encontrada, FALSE caso contrário.
 */
gboolean lookUpMusicsHashTable(gestorMusics *gestorMusic, char *line,
                               gpointer *value, gpointer *orig_key);

/**
 * @brief Incrementa o número de álbuns de um artista com base numa música.
 *
 * Atualiza o número de álbuns de um artista dado o ID da música.
 *
 * @param musicId ID da música que será usada para atualizar o número de álbuns.
 * @param gestorMusics Pointer para o gestor de músicas.
 * @param gestorArtists Pointer para o gestor de artistas.
 */
void incrementRecipeArtist(char *musicId, gestorMusics *gestorMusics,
                           gestorArtists *gestorArtists);

/**
 * @brief Processa um ficheiro de músicas e preenche as tabelas de músicas e
 * géneros.
 *
 * Lê o ficheiro de músicas linha por linha, processa cada linha e insere as
 * informações nas tabelas de músicas e géneros.
 *
 * @param gestor Pointer para a estrutura Gestores.
 * @param musicsPath Caminho do ficheiro contendo as músicas a ser processado.
 * @return int Retorna 1 se o processamento for bem-sucedido, 0 caso contrário.
 */
int GestorMusics(Gestores *gestor, char *musicsPath);

#endif // _GESTORMUSICS_H_
