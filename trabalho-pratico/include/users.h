/**
 * @file users.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file para o ficheiro users.h
 */

#ifndef _USERS_H_
#define _USERS_H_

#include <glib.h>

/**
 * @brief Estrutura de dados para armazenar informações de um usuário.
 */
typedef struct users Users;

/**
 * @brief Define o nome de usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param username Nome de usuário a ser definido.
 */
void setUserUsername(Users *u, char *username);

/**
 * @brief Define o e-mail do usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param email E-mail a ser definido.
 */
void setUserEmail(Users *u, char *email);

/**
 * @brief Define o primeiro nome do usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param first_name Primeiro nome a ser definido.
 */
void setUserFirstName(Users *u, char *first_name);

/**
 * @brief Define o último nome do usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param last_name Último nome a ser definido.
 */
void setUserLastName(Users *u, char *last_name);

/**
 * @brief Define a data de nascimento do usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param birth_date Data de nascimento a ser definida.
 */
void setUserBirthDate(Users *u, char *birth_date);

/**
 * @brief Define o país do usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param country País a ser definido.
 */
void setUserCountry(Users *u, char *country);

/**
 * @brief Define o tipo de assinatura do usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param subscription_type Tipo de assinatura a ser definida.
 */
void setUserSubscriptionType(Users *u, char *subscription_type);

/**
 * @brief Define as músicas curtidas pelo usuário.
 * @param u Ponteiro para a estrutura do usuário.
 * @param liked_musics_id ID das músicas curtidas.
 */
void setUserLikedMusicsId(Users *u, char *liked_musics_id);

/**
 * @brief Atualiza o resumo de audições do usuário.
 * @param u Ponteiro para o usuário.
 * @param year Ano da audição.
 * @param duracao Duração da música.
 * @param musicId ID da música.
 * @param artistId ID do artista.
 * @param albumId ID do álbum.
 * @param genero Gênero musical.
 * @param dia Dia da audição.
 * @param hora Hora da audição.
 */
void updateUserResume(gpointer u, int year, int duracao, char *musicId,
                      char *artistId, char *albumId, char *genero, int dia,
                      int hora);

/**
 * @brief Separa e processa os dados de um usuário a partir de uma linha de
 * texto.
 * @param line Linha de texto contendo os dados do usuário.
 * @return Ponteiro para a estrutura Users processada.
 */
Users *separateUsers(char *line);

/**
 * @brief Incrementa a contagem de audições de um gênero musical.
 * @param user Ponteiro para o usuário.
 * @param genre Gênero a ser incrementado.
 */
void incrementMusicsListening(gpointer user, char *genre);

/**
 * @brief Verifica se um resumo de audições existe.
 * @param user Ponteiro para o usuário.
 * @param indice Índice de verificação.
 * @return 1 se existir, 0 caso contrário.
 */
int existUserResume(gpointer user, int indice);

/**
 * @brief Obtém o nome de usuário.
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string com o nome de usuário.
 */
char *getUserUsername(gpointer user);

/**
 * @brief Obtém o e-mail do usuário.
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string com o e-mail.
 */
char *getUserEmail(gpointer user);

/**
 * @brief Libera a memória alocada para a estrutura do usuário.
 * @param u Ponteiro para a estrutura Users.
 */
void destroyUser(Users *u);

GArray *getUserResumo(gpointer user);

char *getUserFirstName(gpointer user);

char *getUserLastName(gpointer user);

char *getUserBirthDate(gpointer user);

char *getUserCountry(gpointer user);

char *getUserLikedMusicsId(gpointer user);

void preencheLinhaMatriz(int **matrizClassificaoMusicas, int linha, Users *User,
                         int numGeneros, char **nomesGeneros);

#endif
