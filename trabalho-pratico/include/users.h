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
 * @brief Struct de dados para armazenar informações de um user.
 */
typedef struct users Users;

/**
 * @brief Define o nome de user.
 * @param u Pointer para a Struct do user.
 * @param username Nome de user a ser definido.
 */
void setUserUsername(Users *u, char *username);

/**
 * @brief Define o e-mail do user.
 * @param u Pointer para a Struct do user.
 * @param email E-mail a ser definido.
 */
void setUserEmail(Users *u, char *email);

/**
 * @brief Define o primeiro nome do user.
 * @param u Pointer para a Struct do user.
 * @param first_name Primeiro nome a ser definido.
 */
void setUserFirstName(Users *u, char *first_name);

/**
 * @brief Define o último nome do user.
 * @param u Pointer para a Struct do user.
 * @param last_name Último nome a ser definido.
 */
void setUserLastName(Users *u, char *last_name);

/**
 * @brief Define a data de nascimento do user.
 * @param u Pointer para a Struct do user.
 * @param birth_date Data de nascimento a ser definida.
 */
void setUserBirthDate(Users *u, char *birth_date);

/**
 * @brief Define o país do user.
 * @param u Pointer para a Struct do user.
 * @param country País a ser definido.
 */
void setUserCountry(Users *u, char *country);

/**
 * @brief Define o tipo de assinatura do user.
 * @param u Pointer para a Struct do user.
 * @param subscription_type Tipo de assinatura a ser definida.
 */
void setUserSubscriptionType(Users *u, char *subscription_type);

/**
 * @brief Define as músicas curtidas pelo user.
 * @param u Pointer para a Struct do user.
 * @param liked_musics_id ID das músicas curtidas.
 */
void setUserLikedMusicsId(Users *u, char *liked_musics_id);

/**
 * @brief Atualiza o resumo de audições do user.
 * @param u Pointer para o user.
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
 * @brief Separa e processa os dados de um user a partir de uma linha de
 * texto.
 * @param line Linha de texto contendo os dados do user.
 * @return Pointer para a Struct Users processada.
 */
Users *separateUsers(char *line);

/**
 * @brief Incrementa a contagem de audições de um gênero musical.
 * @param user Pointer para o user.
 * @param genre Gênero a ser incrementado.
 */
void incrementMusicsListening(gpointer user, char *genre);

/**
 * @brief Verifica se um resumo de audições existe.
 * @param user Pointer para o user.
 * @param indice Índice de verificação.
 * @return 1 se existir, 0 caso contrário.
 */
int existUserResume(gpointer user, int indice);

/**
 * @brief Obtém o nome de user.
 * @param user Pointer para o user.
 * @return Pointer para a string com o nome de user.
 */
char *getUserUsername(gpointer user);

/**
 * @brief Obtém o e-mail do user.
 * @param user Pointer para o user.
 * @return Pointer para a string com o e-mail.
 */
char *getUserEmail(gpointer user);

/**
 * @brief Liberta a memória alocada para a Struct do user.
 * @param u Pointer para a Struct Users.
 */
void destroyUser(Users *u);

/**
 * @brief Obtém a lista de resumos de audições de um user.
 *
 * Esta função retorna um array contendo os resumos de audições de um user.
 *
 * @param user Pointer para o user.
 * @return Pointer para o array de resumos de audições.
 */
GArray *getUserResumo(gpointer user);

/**
 * @brief Obtém o primeiro nome do user.
 *
 * Esta função retorna o primeiro nome do user armazenado na Struct.
 *
 * @param user Pointer para o user.
 * @return Pointer para a string contendo o primeiro nome.
 */
char *getUserFirstName(gpointer user);

/**
 * @brief Obtém o último nome do user.
 *
 * Esta função retorna o último nome do user armazenado na Struct.
 *
 * @param user Pointer para o user.
 * @return Pointer para a string contendo o último nome.
 */
char *getUserLastName(gpointer user);

/**
 * @brief Obtém a data de nascimento do user.
 *
 * Esta função retorna a data de nascimento do user no formato de string.
 *
 * @param user Pointer para o user.
 * @return Pointer para a string contendo a data de nascimento.
 */
char *getUserBirthDate(gpointer user);

/**
 * @brief Obtém o país do user.
 *
 * Esta função retorna o país associado ao user armazenado na Struct.
 *
 * @param user Pointer para o user.
 * @return Pointer para a string contendo o país do user.
 */
char *getUserCountry(gpointer user);

/**
 * @brief Obtém os IDs das músicas curtidas pelo user.
 *
 * Esta função retorna uma string contendo os IDs das músicas curtidas pelo
 * user.
 *
 * @param user Pointer para o user.
 * @return Pointer para a string com os IDs das músicas curtidas.
 */
char *getUserLikedMusicsId(gpointer user);

/**
 * @brief Preenche uma linha da matriz de classificação de músicas.
 *
 * Esta função atualiza uma linha específica da matriz de classificação de
 * músicas baseada nos dados de audições do user.
 *
 * @param matrizClassificaoMusicas Pointer para a matriz de classificação de
 * músicas.
 * @param linha Índice da linha a ser preenchida.
 * @param User Pointer para o user.
 * @param numGeneros Número total de gêneros na matriz.
 * @param nomesGeneros Array de strings contendo os nomes dos gêneros.
 */
void preencheLinhaMatriz(int **matrizClassificaoMusicas, int linha, Users *User,
                         int numGeneros, char **nomesGeneros);

#endif
