/**
 * @file query3.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do query3.h
 */

#ifndef _QUERY3_H_
#define _QUERY3_H_

typedef struct generoLikes GeneroLikes;

#include "gestor_musics.h"
#include "gestor_users.h"
#include "gestores.h"
#include "nodo_musica.h"
#include <glib.h>

/**
 * @brief Compara dois valores de likes.
 *
 * Esta função é usada para ordenar elementos com base na quantidade
 * de likes atribuídos. É utilizada em operações de ordenação.
 *
 * @param a Primeiro elemento a ser comparado.
 * @param b Segundo elemento a ser comparado.
 * @return Um valor inteiro negativo, zero ou positivo, dependendo do resultado
 * da comparação: negativo se "a < b", positivo se "a > b" e zero se forem
 * iguais.
 */
gint comparar_likes(gconstpointer a, gconstpointer b);

/**
 * @brief Executa a Query 3 para filtrar músicas com base em idade e critérios
 * adicionais.
 *
 * Esta função realiza um filtro nas músicas disponíveis, considerando
 * a faixa etária fornecida e critérios especificados pelos parâmetros.
 *
 * @param minAge Idade mínima dos users.
 * @param maxAge Idade máxima dos users.
 * @param lista Lista de músicas a ser filtrada.
 * @param i Índice do output gerado pela função.
 * @param temS Indicador do tipo de resposta (= ou ;).
 */
void query3(int minAge, int maxAge, NodoMusica *lista, int i, int temS);

/**
 * @brief Cria uma lista de resposta para a Query 3.
 *
 * Esta função filtra e processa uma lista de músicas, criando uma nova
 * lista com base nos critérios especificados. O processamento é feito
 * usando os dados geridos pela Struct de gestão.
 *
 * @param lista Lista inicial de músicas a ser processada.
 * @param gestor Struct de gestão usada para armazenar e recuperar dados
 * relevantes.
 * @return Ponteiro para a lista de resposta criada após o processamento.
 */
NodoMusica *CriaListaRespostaQuery3(NodoMusica *lista, Gestores *gestor);

#endif