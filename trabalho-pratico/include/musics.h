/**
 * @file musics.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do musics
 */
#ifndef _MUSICS_H_
#define _MUSICS_H_

typedef struct musics Musics;

#include <glib.h>
#include <stdbool.h>


/**
 * @brief Define o ID de uma música.
 *
 * Esta função define o campo `id` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param id ID da música.
 */
void setMusicId(Musics *m, char *id);

/**
 * @brief Define o título de uma música.
 *
 * Esta função define o campo `title` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param title Título da música.
 */
void setMusicTitle(Musics *m, char *title);

/**
 * @brief Define o ID do artista de uma música.
 *
 * Esta função define o campo `artist_id` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param artist_id ID do artista.
 */
void setMusicArtistId(Musics *m, char *artist_id);

/**
 * @brief Define o ID do álbum de uma música.
 *
 * Esta função define o campo `album_id` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param album_id ID do álbum.
 */
void setMusicAlbumId(Musics *m, char *album_id);

/**
 * @brief Define a duração de uma música em segundos.
 *
 * Esta função define o campo `durationSeconds` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param durationSeconds Duração da música em segundos.
 */
void setMusicDurationSeconds(Musics *m, int durationSeconds);

/**
 * @brief Define o género de uma música.
 *
 * Esta função define o campo `genre` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param genre Género da música.
 */
void setMusicGenre(Musics *m, char *genre);

/**
 * @brief Define o ano de uma música.
 *
 * Esta função define o campo `year` de uma struct `Musics` com o valor fornecido.
 *
 * @param m Pointer para a struct `Musics` que representa a música.
 * @param year Ano de lançamento da música.
 */
void setMusicYear(Musics *m, int year);

/**
 * @brief Separa os dados de uma linha CSV em uma struct `Musics`.
 *
 * Esta função analisa uma linha CSV e preenche uma nova struct `Musics` com os valores extraídos.
 *
 * @param line Linha do CSV contendo os dados da música.
 * @return Uma nova struct `Musics` contendo os dados extraídos.
 */
Musics *separateMusics(char *line);

/**
 * @brief Valida os dados de uma música.
 *
 * Esta função valida os dados de uma música, verificando se a duração é válida e se o ano é válido.
 *
 * @param music Pointer para a struct `Musics` que representa a música.
 * @return `true` se a música for válida, caso contrário, `false`.
 */
bool validateMusic(Musics *music);

/**
 * @brief Obtém o ID de uma música.
 *
 * Esta função retorna uma cópia do campo `id` de uma struct `Musics`.
 *
 * @param music Pointer para a struct `Musics` que representa a música.
 * @return O ID da música.
 */
char *getMusicId(gpointer music);

/**
 * @brief Obtém o ID do artista de uma música.
 *
 * Esta função retorna uma cópia do campo `artist_id` de uma struct `Musics`.
 *
 * @param music Pointer para a struct `Musics` que representa a música.
 * @return O ID do artista.
 */
char *getMusicArtistId(gpointer music);

/**
 * @brief Obtém o ID do álbum de uma música.
 *
 * Esta função retorna uma cópia do campo `album_id` de uma struct `Musics`.
 *
 * @param music Pointer para a struct `Musics` que representa a música.
 * @return O ID do álbum.
 */
char *getMusicAlbumId(gpointer music);

/**
 * @brief Obtém a duração de uma música em segundos.
 *
 * Esta função retorna a duração de uma música, armazenada no campo `durationSeconds`.
 *
 * @param music Pointer para a struct `Musics` que representa a música.
 * @return A duração da música em segundos.
 */
int getMusicDuration(gpointer music);

/**
 * @brief Obtém o género de uma música.
 *
 * Esta função retorna uma cópia do campo `genre` de uma struct `Musics`.
 *
 * @param music Pointer para a struct `Musics` que representa a música.
 * @return O género da música.
 */
char *getMusicGenre(gpointer music);

/**
 * @brief Liberta a memória associada a uma struct `Musics`.
 *
 * Esta função liberta a memória de todos os campos de uma struct `Musics`, bem como da própria struct.
 *
 * @param music Pointer para a struct `Musics` a ser destruída.
 */
void destroyMusic(Musics *music);


#endif