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
 * @brief Inicializa a Struct de resumo.
 *
 * Esta função aloca e inicializa uma nova Struct de resumo para armazenar
 * informações de audição de um user.
 *
 * @return Pointer para a Struct de resumo inicializada.
 */
Resumo *initResumo();

/**
 * @brief Verifica se uma música está no resumo do user.
 *
 * Esta função verifica se uma determinada música, identificada pelo seu ID,
 * está presente no resumo do user.
 *
 * @param res Pointer para a Struct de resumo.
 * @param musicId ID da música a verificar.
 * @return retorna o indice onde esta, ou -1 se nao estiver
 */
int elemUserResumeIdsMusics(Resumo *res, char *musicId);

/**
 * @brief Atualiza o resumo do user com informações de artistas.
 *
 * Atualiza os dados de audição do user para um determinado artista,
 * considerando a duração da música e seu ID.
 *
 * @param res Pointer para a Struct de resumo.
 * @param artistId ID do artista.
 * @param duracao Duração da música em segundos.
 * @param musicId ID da música associada.
 * @return Resultado da atualização (0 para sucesso ou outro valor para erro).
 */
int updateUserResumeArtists(Resumo *res, char *artistId, int duracao,
                            char *musicId);

/**
 * @brief Atualiza o resumo do user com informações de álbuns.
 *
 * Esta função atualiza o resumo com dados de um álbum específico,
 * considerando a duração total de audição.
 *
 * @param res Pointer para a Struct de resumo.
 * @param albumId ID do álbum.
 * @param duracao Duração da música em segundos.
 */
void updateUserResumeAlbuns(Resumo *res, char *albumId, int duracao);

/**
 * @brief Atualiza o resumo do user com informações de gêneros musicais.
 *
 * Atualiza o resumo de audição com informações sobre um gênero musical
 * específico, considerando a duração total.
 *
 * @param res Pointer para a Struct de resumo.
 * @param gen Nome do gênero musical.
 * @param duracao Duração da música em segundos.
 */
void updateUserResumeGeneros(Resumo *res, char *gen, int duracao);

/**
 * @brief Destrói a Struct de resumos de users.
 *
 * Esta função liberta a memória alocada para a Struct de resumo de users.
 *
 * @param resumos Array contendo os resumos a serem destruídos.
 */
void destroyUserResumo(GArray *resumos);

/**
 * @brief Obtém o tempo total de audição do user em um determinado ano.
 *
 * Esta função retorna o tempo total (em segundos) que o user passou ouvindo
 * músicas em um ano específico.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual calcular o tempo de audição.
 * @return Tempo total de audição em segundos.
 */
int getUserResumoListeningTime(gpointer user, int year);

/**
 * @brief Obtém o número de músicas diferentes ouvidas pelo user em um ano.
 *
 * Esta função calcula quantas músicas únicas o user ouviu em um ano
 * específico.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual calcular o número de músicas diferentes.
 * @return Número de músicas únicas ouvidas pelo user.
 */
int getUserResumoNumMusicasDiferentes(gpointer user, int year);

/**
 * @brief Obtém os artistas mais ouvidos pelo user em um ano.
 *
 * Esta função retorna uma string contendo os IDs dos artistas mais ouvidos pelo
 * user em um ano, limitado pelo número especificado.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual obter os artistas mais ouvidos.
 * @param N Número máximo de artistas a serem retornados.
 * @param temS Indica se os artistas devem incluir uma pontuação (1 para sim, 0
 * para não).
 * @return String contendo os IDs dos artistas mais ouvidos.
 */
char *getUserResumoArtists(gpointer user, int year, int N, int temS);

/**
 * @brief Obtém o gênero musical mais ouvido pelo user em um ano.
 *
 * Esta função retorna uma string contendo o nome do gênero musical mais ouvido
 * pelo user em um ano específico.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual obter o gênero mais ouvido.
 * @return String com o nome do gênero mais ouvido.
 */
char *getUserResumoGenero(gpointer user, int year);

/**
 * @brief Obtém o álbum mais ouvido pelo user em um ano.
 *
 * Esta função retorna uma string contendo o ID do álbum mais ouvido pelo
 * user em um ano específico.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual obter o álbum mais ouvido.
 * @return String com o ID do álbum mais ouvido.
 */
char *getUserResumoAlbum(gpointer user, int year);

/**
 * @brief Obtém o dia do ano com mais audições do user.
 *
 * Esta função retorna o dia do ano em que o user teve o maior tempo
 * de audição em um ano específico.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual calcular o dia mais ativo.
 * @return Dia do ano com maior tempo de audição.
 */
int getUserResumoDay(gpointer user, int year);

/**
 * @brief Obtém a hora do dia com mais audições do user.
 *
 * Esta função retorna a hora do dia em que o user teve o maior tempo
 * de audição em um ano específico.
 *
 * @param user Pointer para o user.
 * @param year Ano para o qual calcular a hora mais ativa.
 * @return Hora do dia com maior tempo de audição.
 */
int getUserResumoHora(gpointer user, int year);

#endif
