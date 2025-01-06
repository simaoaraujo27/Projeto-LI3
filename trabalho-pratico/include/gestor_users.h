/**
 * @file gestor_users.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do gestor_users
 */
#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

typedef struct gestorUsers gestorUsers;

#include "gestor_musics.h"
#include "gestores.h"
#include "nodo_musica.h"
#include "users.h"

#include <glib.h>
#include <stdio.h>

/**
 * @brief Faz o parsing de todos os users.
 *
 * Esta função lê os dados dos users de um ficheiro especificado e
 * preenche os seus campos.
 *
 * @param gestor Pointer para a estrutura Gestores onde será inicializado o gestor de users.
 * @param usersPath Path para o ficheiro que contêm os dados dos users.
 * @return Um inteiro indicando o sucesso (0) ou falha (1) da operação.
 */
int GestorUsers(Gestores *gestor, char *usersPath);

/**
 * @brief Cria e inicializa uma nova estrutura gestorUsers.
 *
 * Esta função aloca memória e inicializa os campos necessários da estrutura gestorUsers 
 * (inicializa a hashtable, a query6table e o nUsers a 0).
 *
 * @return Um pointer para a estrutura inicializada gestorUsers, ou NULL se ocorrer um erro.
 */
gestorUsers *initGestorUsers();

/**
 * @brief Liberta a memória alocada pela estrutura gestorUsers.
 *
 * Esta função desaloca toda a memória associada à estrutura gestorUsers (incluindo as duas hashtables), evitando memory leaks.
 *
 * @param gestorUser Pointer para a estrutura gestorUsers a ser libertada.
 */
void freeGestorUsers(gestorUsers *gestorUser);

/**
 * @brief Verifica a existência de user na hashtable dos users.
 *
 * Esta função procura um user específico na hashtable associada ao gestor de utilizadores.
 * Se encontrada, retorna que encontrou e muda o value e a orig_key
 *
 * @param gestorUser Pointer para a estrutura gestorUsers.
 * @param line A chave a ser pesquisada.
 * @param value Pointer para armazenar o valor associado à chave (se encontrada).
 * @param orig_key Pointer para armazenar a chave original (se encontrada).
 * @return gboolean indicando TRUE (chave encontrada) ou FALSE (não encontrada).
 */
gboolean lookUpUsersHashTable(gestorUsers *gestorUser, char *line,
                              gpointer *value, gpointer *orig_key);

/**
 * @brief Processa todos os users que estão na hashtable.
 *
 * Esta função percorre todos os users na hashtable no gestor e vê a sua idade,
 * Vê também os generos das liked musics e adiciona um like neste género para a idade do user.
 *
 * @param gestor Pointer para a estrutura Gestores.
 * @param lista Pointer para uma lista com géneros e os likes de cada género.
 */
void processAllUsers(Gestores *gestor, NodoMusica **lista);

/**
 * @brief Obtém o número total de users.
 *
 * Esta função retorna o número de users atualmente armazenados na hashtable do gestorUsers.
 *
 * @param gestorUser Pointer para a estrutura gestorUsers.
 * @return O número total de users.
 */
int getNUsers(gestorUsers *gestorUser);

/**
 * @brief Preenche uma matriz de classificação de músicas com base nos dados dos users.
 *
 * Esta função percorre os dados armazenados na hashtable dos users para preencher uma matriz,
 * onde cada linha representa um user e cada coluna representa um género de música.
 * A matriz é preenchida com base na interação dos users com cada género.
 * Adicionalmente, os IDs dos users são armazenados em um array separado.
 *
 * @param matrizClassificaoMusicas Ponteiro para a matriz de classificação a ser preenchida. 
 *        Cada linha da matriz representa um utilizador, e cada coluna representa um género.
 * @param numGeneros Número total de géneros de música (número de colunas na matriz).
 * @param nomesGeneros Array de strings contendo os nomes dos géneros de música.
 * @param gestorUsers Pointer para a estrutura gestorUsers, que contém os dados dos users.
 * @param idsUtilizadores Array de strings onde serão armazenados os IDs dos users.
 *        Cada elemento do array corresponde a uma linha da matriz.
 */
void preencheMatriz(int **matrizClassificaoMusicas, int numGeneros,
                    char **nomesGeneros, gestorUsers *gestorUsers,
                    char **idsUtilizadores);

/**
 * @brief Verifica a existência de user na hashtable da query6.
 *
 * Esta função verifica se uma chave específica existe na hashtable da query6
 * Retorna os valores associados se encontrada.
 *
 * @param gestorUser Pointer para a estrutura gestorUsers.
 * @param line A chave a ser pesquisada.
 * @param value Pointer para armazenar o valor associado à chave (se encontrada).
 * @param orig_key Pointer para armazenar a chave original (se encontrada).
 * @return gboolean indicando TRUE (chave encontrada) ou FALSE (não encontrada).
 */
gboolean lookUpQuery6Table(gestorUsers *gestorUser, char *line, gpointer *value,
                           gpointer *orig_key);

/**
 * @brief Insere um user na hashtable usada na Query 6.
 *
 * Esta função adiciona um novo user à hashtable da query6
 * Se já la estiver acrescenta o novo ano
 *
 * @param line A chave a ser inserida.
 * @param gestorUsers Pointer para a estrutura gestorUsers.
 */
void setQuery6Table(char *line, gestorUsers *gestorUsers);


#endif