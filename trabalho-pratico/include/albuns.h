/**
 * @file albuns.h
 * @author
 * Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do albuns
 */
#ifndef _ALBUNS_H_
#define _ALBUNS_H_

typedef struct albuns Albuns;

#include "gestor_artists.h"

/**
 * @brief Obtém o ID de um álbum.
 *
 * Esta função retorna uma cópia do campo `id` de uma struct `Albuns`.
 *
 * @param album Pointer para a struct `Albuns` que representa o álbum.
 * @return Uma string que contém o ID do álbum.
 */
char *getAlbumId(Albuns *album);

/**
 * @brief Define o ID de um álbum.
 *
 * Esta função atualiza o campo `id` de uma struct `Albuns` com o valor
 * fornecido.
 *
 * @param album Pointer para a struct `Albuns` que representa o álbum.
 * @param id String que contém o novo ID do álbum.
 */
void setAlbumId(Albuns *album, char *id);

/**
 * @brief Define o título de um álbum.
 *
 * Esta função atualiza o campo `title` de uma struct `Albuns` com o valor
 * fornecido.
 *
 * @param album Pointer para a struct `Albuns` que representa o álbum.
 * @param title String que contém o novo título do álbum.
 */
void setAlbumTitle(Albuns *album, char *title);

/**
 * @brief Define o ID dos artistas de um álbum.
 *
 * Esta função atualiza o campo `artists_id` de uma struct `Albuns` com o valor
 * fornecido.
 *
 * @param album Pointer para a struct `Albuns` que representa o álbum.
 * @param artists_id String que contém os IDs dos artistas do álbum.
 */
void setAlbumArtistsId(Albuns *album, char *artists_id);

/**
 * @brief Define o ano de lançamento de um álbum.
 *
 * Esta função atualiza o campo `year` de uma struct `Albuns` com o valor
 * fornecido.
 *
 * @param album Pointer para a struct `Albuns` que representa o álbum.
 * @param year String que contém o ano de lançamento do álbum.
 */
void setAlbumYear(Albuns *album, char *year);

/**
 * @brief Define os produtores de um álbum.
 *
 * Esta função atualiza o campo `producers` de uma struct `Albuns` com o valor
 * fornecido.
 *
 * @param album Pointer para a struct `Albuns` que representa o álbum.
 * @param producers String que contém os produtores do álbum.
 */
void setAlbumProducers(Albuns *album, char *producers);

/**
 * @brief Cria uma nova instância de um álbum.
 *
 * Esta função aloca memória e inicializa os campos de uma struct `Albuns` com
 * valores default (neste caso, todos os campos a NULL)
 *
 * @return Pointer para a struct `Albuns` inicializada ou NULL em caso de erro.
 */
Albuns *initAlbum();

/**
 * @brief Liberta a memória associada a um álbum.
 *
 * Esta função liberta toda a memória alocada para os campos e para a própria
 * struct `Albuns`.
 *
 * @param album Pointer para a struct `Albuns` a ser destruída.
 */
void destroyAlbum(Albuns *album);

/**
 * @brief Constrói um álbum a partir de uma linha de texto, proveniente de um ficheiro CSV.
 *
 * Esta função analisa uma linha de texto separada por delimitadores e preenche
 * cada um dos campos da struct `Albuns` correspondente.
 *
 * @param line Linha de texto que contém os dados do álbum, separados por
 * delimitadores.
 * @param gestorArtists Pointer para a estrutura de gestão de artistas.
 * @return Pointer para a struct `Albuns` preenchida com os dados da linha.
 */
Albuns *separateAlbuns(char *line, gestorArtists *gestorArtists);

#endif
