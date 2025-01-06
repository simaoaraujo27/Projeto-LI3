#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

/**
 * @file gestor_artists.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Gestor Artists`.
 */
typedef struct gestorArtists gestorArtists;

#include "artists.h"
#include "gestores.h"

/**
 * @brief Inicializa o gestor de artistas e todos os seus campos.
 *
 * Cria e inicializa a hash table para armazenar os artistas e outras
 * estruturas necessárias.
 *
 * @return gestorArtists* Pointer para o gestor de artistas recém-inicializado.
 */
gestorArtists *initGestorArtists();

/**
 * @brief Obtém a lista de Tops10 do gestor de artistas.
 *
 * Retorna o array contendo os 10 artistas mais populares.
 *
 * @param gestorArtists Pointer para o gestor de artistas.
 * @return GArray* Array contendo os 10 artistas mais populares.
 */
GArray *getGArrayTops10(gestorArtists *gestorArtists);

/**
 * @brief Liberta a memória alocada para o gestor de artistas.
 *
 * Liberta a memória da hash table e outras estruturas do gestor de artistas.
 *
 * @param gestor Pointer para o gestor de artistas a ser libertado.
 */
void freeGestorArtists(gestorArtists *gestor);

/**
 * @brief Processa o ficheiro de artistas e insere os dados na hash table.
 *
 * Lê o ficheiro de artistas e insere cada artista válido na hash table.
 *
 * @param gestor Pointer para o gestor utilizado para acederr ao gestor de
 * artistas.
 * @param artistsPath Caminho do ficheiro contendo os dados dos artistas.
 * @return int Retorna 1 se o processamento for bem-sucedido, 0 caso contrário.
 */
int GestorArtists(Gestores *gestor, char *artistsPath);

/**
 * @brief Procura um artista na hash table.
 *
 * Pesquisa um artista utilizando a chave fornecida (ID do artista).
 *
 * @param gestorArtist Pointer para o gestor de artistas.
 * @param key Chave (ID do artista) a ser pesquisada.
 * @param value Pointer para armazenar o valor (artista) encontrado na tabela
 * hash.
 * @param orig_key Pointer para armazenar a chave original.
 * @return gboolean TRUE se o artista for encontrado, FALSE caso contrário.
 */
gboolean lookUpArtistsHashTable(gestorArtists *gestorArtist, char *key,
                                gpointer *value, gpointer *orig_key);

/**
 * @brief Incrementa o número de álbuns de um artista.
 *
 * Atualiza o contador de álbuns de um artista.
 *
 * @param artistId ID do artista a ser atualizado.
 * @param gestorArtist Pointer para o gestor de artistas.
 */
void incrementArtistsNumAlbuns(char *artistId, gestorArtists *gestorArtist);

/**
 * @brief Coloca zero no campo "vezesTop10" de todos os artistas.
 *
 * Reseta a contagem de "vezesTop10" para todos os artistas.
 *
 * @param GestorArtists Pointer para o gestor de artistas.
 */
void colocaZeroVezesTop10(gestorArtists *GestorArtists);

/**
 * @brief Insere um artista na lista da query 2 de forma ordenada pela sua
 * discografia.
 *
 * A lista é ordenada de acordo com o número de álbuns do artista e seu ID.
 *
 * @param gestorArtists Pointer para o gestor de artistas.
 * @param artist Pointer para o artista a ser inserido.
 */
void insertListaQuery2(gestorArtists *gestorArtists, Artists *artist);

/**
 * @brief Cria as listas para a query 2.
 *
 * Insere todos os artistas na lista de forma ordenada.
 *
 * @param gestorArtists Pointer para o gestor de artistas.
 */
void CriaListasQuery2(gestorArtists *gestorArtists);

/**
 * @brief Obtém a lista da query 2 do gestor de artistas.
 *
 * Retorna a lista de artistas ordenada para a query 2.
 *
 * @param gestorArtists Pointer para o gestor de artistas.
 * @return GList* Lista contendo os artistas ordenados.
 */
GList *getGListQuery2GestorArtist(gestorArtists *gestorArtists);

#endif // _GESTORARTISTS_H_
