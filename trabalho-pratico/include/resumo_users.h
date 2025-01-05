/**
 * @file resumo_users.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do resumo_users.h
 */

#ifndef _RESUMO_USERS_H_
#define _RESUMO_USERS_H_

typedef struct artistaAudicoes ArtistaTempo;
typedef struct categoriaTempo AlbumTempo;
typedef struct categoriaTempo GeneroTempo;
typedef struct resumo Resumo;

#include <glib.h>

/**
 * @brief Inicializa a estrutura de resumo.
 *
 * Esta função aloca e inicializa uma nova estrutura de resumo para armazenar
 * informações de audição de um usuário.
 *
 * @return Ponteiro para a estrutura de resumo inicializada.
 */
Resumo *initResumo();

/**
 * @brief Verifica se uma música está no resumo do usuário.
 *
 * Esta função verifica se uma determinada música, identificada pelo seu ID,
 * está presente no resumo do usuário.
 *
 * @param res Ponteiro para a estrutura de resumo.
 * @param musicId ID da música a verificar.
 * @return retorna o indice onde esta, ou -1 se nao estiver
 */
int elemUserResumeIdsMusics(Resumo *res, char *musicId);

/**
 * @brief Atualiza o resumo do usuário com informações de artistas.
 *
 * Atualiza os dados de audição do usuário para um determinado artista,
 * considerando a duração da música e seu ID.
 *
 * @param res Ponteiro para a estrutura de resumo.
 * @param artistId ID do artista.
 * @param duracao Duração da música em segundos.
 * @param musicId ID da música associada.
 * @return Resultado da atualização (0 para sucesso ou outro valor para erro).
 */
int updateUserResumeArtists(Resumo *res, char *artistId, int duracao,
                            char *musicId);

/**
 * @brief Atualiza o resumo do usuário com informações de álbuns.
 *
 * Esta função atualiza o resumo com dados de um álbum específico,
 * considerando a duração total de audição.
 *
 * @param res Ponteiro para a estrutura de resumo.
 * @param albumId ID do álbum.
 * @param duracao Duração da música em segundos.
 */
void updateUserResumeAlbuns(Resumo *res, char *albumId, int duracao);

/**
 * @brief Atualiza o resumo do usuário com informações de gêneros musicais.
 *
 * Atualiza o resumo de audição com informações sobre um gênero musical
 * específico, considerando a duração total.
 *
 * @param res Ponteiro para a estrutura de resumo.
 * @param gen Nome do gênero musical.
 * @param duracao Duração da música em segundos.
 */
void updateUserResumeGeneros(Resumo *res, char *gen, int duracao);

/**
 * @brief Destrói a estrutura de resumos de usuários.
 *
 * Esta função libera a memória alocada para a estrutura de resumo de usuários.
 *
 * @param resumos Array contendo os resumos a serem destruídos.
 */
void destroyUserResumo(GArray *resumos);

#endif
