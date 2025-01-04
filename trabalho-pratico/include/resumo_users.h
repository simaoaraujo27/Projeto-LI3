#ifndef _RESUMO_USERS_H_
#define _RESUMO_USERS_H_

typedef struct artistaAudicoes ArtistaTempo;
typedef struct categoriaTempo AlbumTempo;
typedef struct categoriaTempo GeneroTempo;
typedef struct resumo Resumo;

#include <glib.h>

Resumo *initResumo();

int elemUserResumeIdsMusics(Resumo *res, char *musicId);

int updateUserResumeArtists(Resumo *res, char *artistId, int duracao,
                            char *musicId);

void updateUserResumeAlbuns(Resumo *res, char *albumId, int duracao);

void updateUserResumeGeneros(Resumo *res, char *gen, int duracao);

void updateUserResume(gpointer u, int year, int duracao, char *musicId,
                      char *artistId, char *albumId, char *genero, int dia,
                      int hora);

int getUserResumoListeningTime(gpointer user, int year);

int getUserResumoNumMusicasDiferentes(gpointer user, int year);

gint comparar_likes_Q6(gconstpointer a, gconstpointer b);

char *getUserResumoArtists(gpointer user, int year, int N, int temS);

char *getUserResumoGenero(gpointer user, int year);

char *getUserResumoAlbum(gpointer user, int year);

int getUserResumoDay(gpointer user, int year);

int getUserResumoHora(gpointer user, int year);

void destroyUserResumo(GArray *resumos);

#endif