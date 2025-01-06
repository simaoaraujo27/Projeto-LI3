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

/**
 * @brief Obtém a lista de resumos de audições de um usuário.
 *
 * Esta função retorna um array contendo os resumos de audições de um usuário.
 *
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para o array de resumos de audições.
 */
GArray *getUserResumo(gpointer user);

/**
 * @brief Obtém o primeiro nome do usuário.
 *
 * Esta função retorna o primeiro nome do usuário armazenado na estrutura.
 *
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string contendo o primeiro nome.
 */
char *getUserFirstName(gpointer user);

/**
 * @brief Obtém o último nome do usuário.
 *
 * Esta função retorna o último nome do usuário armazenado na estrutura.
 *
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string contendo o último nome.
 */
char *getUserLastName(gpointer user);

/**
 * @brief Obtém a data de nascimento do usuário.
 *
 * Esta função retorna a data de nascimento do usuário no formato de string.
 *
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string contendo a data de nascimento.
 */
char *getUserBirthDate(gpointer user);

/**
 * @brief Obtém o país do usuário.
 *
 * Esta função retorna o país associado ao usuário armazenado na estrutura.
 *
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string contendo o país do usuário.
 */
char *getUserCountry(gpointer user);

/**
 * @brief Obtém os IDs das músicas curtidas pelo usuário.
 *
 * Esta função retorna uma string contendo os IDs das músicas curtidas pelo
 * usuário.
 *
 * @param user Ponteiro para o usuário.
 * @return Ponteiro para a string com os IDs das músicas curtidas.
 */
char *getUserLikedMusicsId(gpointer user);

/**
 * @brief Preenche uma linha da matriz de classificação de músicas.
 *
 * Esta função atualiza uma linha específica da matriz de classificação de
 * músicas baseada nos dados de audições do usuário.
 *
 * @param matrizClassificaoMusicas Ponteiro para a matriz de classificação de
 * músicas.
 * @param linha Índice da linha a ser preenchida.
 * @param User Ponteiro para o usuário.
 * @param numGeneros Número total de gêneros na matriz.
 * @param nomesGeneros Array de strings contendo os nomes dos gêneros.
 */
void preencheLinhaMatriz(int **matrizClassificaoMusicas, int linha, Users *User,
                         int numGeneros, char **nomesGeneros);

#endif
