/**
 * @file gestores.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do gestores
 */
#ifndef _GESTORES_H_
#define _GESTORES_H_

typedef struct gestores Gestores;

#include "argumentos_query5.h"
#include "compare_files.h"
#include "erros.h"
#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestor_history.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Inicializa a estrutura principal Gestores.
 *
 * Esta função aloca memória para a estrutura `Gestores` e inicializa
 * todos os seus campos, incluindo gestores de artistas, músicas, utilizadores,
 * álbuns, ficheiros de erros, argumentos de queries e tempos de teste.
 * Caso ocorra algum erro durante a inicialização de um dos campos,
 * a função retorna `NULL` e ajusta o valor apontado por `flag` para indicar o erro.
 *
 * @param flag Pointer para uma flag que indica sucesso (0) ou falha (1).
 * @return Pointer para a estrutura `Gestores` inicializada ou `NULL` em caso de erro.
 */
Gestores *initgestor(int *flag);

/**
 * @brief Obtém o gestor de artistas associado à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para o gestor de artistas.
 */
gestorArtists *getGestorArtist(Gestores *gestor);

/**
 * @brief Obtém o gestor de músicas associado à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para o gestor de músicas.
 */
gestorMusics *getGestorMusic(Gestores *gestor);

/**
 * @brief Obtém o gestor de utilizadores associado à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para o gestor de utilizadores.
 */
gestorUsers *getGestorUser(Gestores *gestor);

/**
 * @brief Obtém o gestor de álbuns associado à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para o gestor de álbuns.
 */
gestorAlbuns *getGestorAlbum(Gestores *gestor);

/**
 * @brief Obtém o gestor de ficheiros de erros CSV associado à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para o gestor de ficheiros de erros CSV.
 */
FicheiroErrosCSV *getGestorFicheiroErrosCSV(Gestores *gestor);

/**
 * @brief Obtém os argumentos da query 5 associados à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para os argumentos da query 5.
 */
argumentosQuery5 *getGestorArgumentosQuery5(Gestores *gestor);

/**
 * @brief Obtém os tempos de testes associados à estrutura Gestores.
 *
 * @param gestor Pointer para a estrutura `Gestores`.
 * @return Pointer para os tempos de testes.
 */
temposTestes *getGestorTemposTestes(Gestores *gestor);

/**
 * @brief Liberta a memória associada à estrutura Gestores.
 *
 * Esta função liberta toda a memória alocada para os gestores e os seus
 * campos, garantindo que não haja memory leaks.
 *
 * @param gestor Pointer para a estrutura `Gestores` a ser destruída.
 */
void destroyGestor(Gestores *gestor);


#endif