/**
 * @file artists.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do módulo `Artists`.
 */

#ifndef _ARTISTS_H_
#define _ARTISTS_H_

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>

enum tipoArtista;

/**
 * Struct que representa um artista.
 */
typedef struct artists Artists;

/**
 * @brief Cria um artista a partir de uma linha de texto.
 *
 * Esta função processa uma linha de texto formatada e cria uma instância
 * da struct `Artists` com os valores extraídos.
 *
 * @param line Linha de texto formatada com dados do artista.
 * @return Um pointer para a struct `Artists` criada.
 */
Artists *separateArtists(char *line);

/**
 * @brief Valida os dados de um artista.
 *
 * Esta função verifica se os atributos de um artista são consistentes com
 * o seu tipo (Individual ou Grupo).
 *
 * @param artist Pointer para a struct `Artists` a ser validada.
 * @return `true` se os dados forem válidos; caso contrário, retorna `false`.
 */
bool validateArtist(Artists *artist);

/**
 * @brief Incrementa a duração de reprodução semanal de um artista.
 *
 * Esta função incrementa a duração semanal acumulada para uma determinada
 * semana, expandindo o array caso necessário.
 *
 * @param a Pointer para a struct `Artists`.
 * @param duration Duração a ser incrementada.
 * @param semana Semana em que a duração será adicionada.
 * @return O valor atualizado da duração semanal para a semana especificada.
 */
int incrementArtistDurationPerWeek(gpointer a, int duration, int semana);

/**
 * @brief Incrementa o contador de vezes que o artista esteve no Top 10.
 *
 * Esta função atualiza o campo `vezesNoTop10` de uma struct `Artists`,
 * incrementando-o em 1.
 *
 * @param a Pointer para a struct `Artists`.
 * @return O valor atualizado do contador de vezes no Top 10.
 */
int incrementArtistVezesNoTop10(gpointer a);

/**
 * @brief Define todas as vezes que um artista esteve no Top 10 para 0.
 *
 * Esta função reinicia o contador `vezesNoTop10` de uma struct `Artists` para
 * 0.
 *
 * @param artist Pointer para a struct `Artists`.
 */
void putArtistsVezesTop10Zero(Artists *artist);

/**
 * @brief Define o ID de um artista.
 *
 * Esta função atualiza o campo `id` de uma struct `Artists` com o valor
 * fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param id String que contém o ID do artista.
 */
void setArtistId(Artists *a, char *id);

/**
 * @brief Define o nome de um artista.
 *
 * Esta função atualiza o campo `name` de uma struct `Artists` com o valor
 * fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param name String que contém o nome do artista.
 */
void setArtistName(Artists *a, char *name);

/**
 * @brief Define o valor de receita por reprodução de um artista.
 *
 * Esta função atualiza o campo `recipePerStream` de uma struct `Artists` com
 * o valor fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param recipe_per_stream Valor da receita por reprodução.
 */
void setArtistRecipePerStream(Artists *a, float recipe_per_stream);

/**
 * @brief Define o ID de um constituinte de um artista.
 *
 * Esta função atualiza o campo `id_constituent` de uma struct `Artists` com
 * o valor fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param id_constituent String que contém o ID_constituent.
 */
void setArtistIdConstituent(Artists *a, char *id_constituent);

/**
 * @brief Define o país de um artista.
 *
 * Esta função atualiza o campo `country` de uma struct `Artists` com o valor
 * fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param country String que contém o país do artista.
 */
void setArtistCountry(Artists *a, char *country);

/**
 * @brief Define o tipo de um artista.
 *
 * Esta função atualiza o campo `tipo` de uma struct `Artists` com o valor
 * fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param tipo Valor do enum `tipoArtista` que define o tipo de artista.
 */
void setArtistTipo(Artists *a, enum tipoArtista tipo);

/**
 * @brief Define a discografia de um artista.
 *
 * Esta função atualiza o campo `discografia` de uma struct `Artists` com o
 * valor fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param discografia Valor que indica o tamanho da discografia do artista.
 */
void setArtistDiscografia(gpointer a, int discografia);

/**
 * @brief Atualiza o número de álbuns individuais de um artista.
 *
 * Esta função modifica o campo `num_albuns_individual` de uma struct `Artists`
 * com o valor fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param num_albuns_individual Valor que representa o número de álbuns
 * individuais.
 */
void alterarArtistNumAlbunsIndividual(gpointer a, int num_albuns_individual);

/**
 * @brief Define a receita total de um artista.
 *
 * Esta função atualiza o campo `receitaTotal` de uma struct `Artists` com o
 * valor fornecido.
 *
 * @param artist Pointer para a struct `Artists`.
 * @param receitaTotal Valor que representa a receita total do artista.
 */
void setArtistReceitaTotal(gpointer artist, float receitaTotal);

/**
 * @brief Define o tamanho do grupo de um artista.
 *
 * Esta função atualiza o campo `tamanhoGrupo` de uma struct `Artists` com o
 * valor fornecido.
 *
 * @param a Pointer para a struct `Artists`.
 * @param tamanho Valor que indica o tamanho do grupo do artista.
 */
void setArtistTamanhoGrupo(Artists *a, int tamanho);

/**
 * @brief Obtém o ID de um artista.
 *
 * Esta função retorna uma cópia do campo `id` de uma struct `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return String com o valor do campo `id`.
 */
char *getArtistId(gpointer artist);

/**
 * @brief Obtém o nome de um artista.
 *
 * Esta função retorna uma cópia do campo `name` de uma struct `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return String com o valor do campo `name`.
 */
char *getArtistName(gpointer artist);

/**
 * @brief Obtém o ID de um constituinte do artista.
 *
 * Esta função retorna uma cópia do campo `id_constituent` de uma struct
 * `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return String com o valor do campo `id_constituent`.
 */
char *getArtistIdConstituent(gpointer artist);

/**
 * @brief Obtém o país de um artista.
 *
 * Esta função retorna uma cópia do campo `country` de uma struct `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return String com o valor do campo `country`.
 */
char *getArtistCountry(gpointer artist);

/**
 * @brief Obtém o tipo de um artista.
 *
 * Esta função retorna o valor da enumeração `tipoArtista` correspondente ao
 * tipo do artista.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return Valor da enumeração `tipoArtista`.
 */
enum tipoArtista getArtistType(gpointer artist);

/**
 * @brief Obtém o tipo de um artista como string.
 *
 * Esta função retorna uma string que descreve o tipo do artista, seja
 * "individual" ou "group".
 *
 * @param artist Pointer para a struct `Artists`.
 * @return String com o tipo do artista.
 */
char *getArtistTypeStr(gpointer artist);

/**
 * @brief Obtém o tamanho da discografia de um artista.
 *
 * Esta função retorna o valor do campo `discografia` de uma struct `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return Valor do campo `discografia`.
 */
int getArtistDiscografia(gpointer artist);

/**
 * @brief Obtém o número de álbuns individuais de um artista.
 *
 * Esta função retorna o valor do campo `num_albuns_individual` de uma struct
 * `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return Número de álbuns individuais.
 */
int getArtistNumAlbunsIndividual(gpointer artist);

/**
 * @brief Obtém a receita por reprodução de um artista.
 *
 * Esta função retorna o valor do campo `recipePerStream` de uma struct
 * `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return Valor da receita por reprodução.
 */
float getArtistRecipePerStream(gpointer artist);

/**
 * @brief Obtém a receita total de um artista.
 *
 * Esta função retorna o valor do campo `receitaTotal` de uma struct `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return Valor da receita total.
 */
float getArtistReceitaTotal(gpointer artist);

/**
 * @brief Obtém o tamanho do grupo de um artista.
 *
 * Esta função retorna o valor do campo `tamanhoGrupo` de uma struct `Artists`.
 *
 * @param artist Pointer para a struct `Artists`.
 * @return Tamanho do grupo do artista.
 */
int getArtistTamanhoGrupo(gpointer artist);

/**
 * @brief Liberta a memória associada a uma struct `Artists`.
 *
 * Esta função desaloca todos os campos de uma struct `Artists` e liberta a
 * memória associada.
 *
 * @param a Pointer para a struct `Artists` a ser destruída.
 */
void destroyArtist(Artists *a);

#endif
