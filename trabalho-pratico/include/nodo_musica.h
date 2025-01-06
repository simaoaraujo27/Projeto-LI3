/**
 * @file nodo_musica.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do nodo_musica
 */
#ifndef _NODO_MUSICA_H_
#define _NODO_MUSICA_H_

typedef struct nodoMusica NodoMusica;

#include <assert.h>
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Cria um novo nodo para um género.
 *
 * @param genero String que representa o nome do género.
 * @param idade_max Idade máxima inicial para criar o array de likes.
 * @return Pointer para o nodo criado, ou NULL caso a alocação de memória falhe.
 */
NodoMusica *criar_nodo(char *genero, guint idade_max);

/**
 * @brief Expande os arrays de likes em cada nodo para suportar uma nova idade máxima.
 *
 * @param lista Pointer para o início da lista ligada de nodos.
 * @param nova_idade_max Nova idade máxima a ser suportada pelos arrays de likes.
 */
void expandir_arrays(NodoMusica *lista, guint nova_idade_max);

/**
 * @brief Adiciona um like a um género para uma idade específica.
 *
 * Se o género ainda não existir na lista, um novo nodo será criado.
 * Caso a idade seja maior que a idade máxima atual, os arrays serão expandidos.
 *
 * @param lista Pointer para o início da lista ligada de nodos.
 * @param genero String que representa o nome do género musical.
 * @param idade Idade para a qual o like será adicionado.
 * @param idade_max Pointer para a idade máxima atual. Será atualizado se necessário.
 * @return Pointer para o início da lista (pode ser o mesmo ou um novo nodo, caso um novo género seja adicionado).
 */
NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade, guint *idade_max);

/**
 * @brief Liberta todos os recursos associados a uma lista de nodos.
 *
 * Esta função liberta todos os nodos da lista, incluindo os arrays de likes e os géneros.
 *
 * @param lista Pointer para o início da lista ligada de nodos.
 */
void libertar_lista(NodoMusica *lista);

/**
 * @brief Obtém o género associado a um nodo.
 *
 * @param l Pointer para o nodo.
 * @return String que representa o género do nodo.
 */
char *getGeneroNodoMusic(NodoMusica *l);

/**
 * @brief Obtém o array de likes associado a um nodo.
 *
 * @param l Pointer para o nodo.
 * @return Pointer para o array de likes do nodo.
 */
GArray *getLikesNodoMusic(NodoMusica *l);

/**
 * @brief Obtém o próximo nodo na lista ligada.
 *
 * @param l Pointer para o nodo atual.
 * @return Pointer para o próximo nodo na lista, ou NULL se for o último.
 */
NodoMusica *getProxNodoMusic(NodoMusica *l);

#endif