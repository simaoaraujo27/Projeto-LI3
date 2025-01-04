#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

typedef struct gestorArtists gestorArtists;

#include "artists.h"
#include "gestores.h"

gestorArtists *initGestorArtists();

GArray *getGArrayTops10(gestorArtists *gestorArtists);

void freeGestorArtists(gestorArtists *gestor);

int GestorArtists(Gestores *gestor, char *artistsPath);

gboolean lookUpArtistsHashTable(gestorArtists *gestorArtist, char *line,
                                gpointer *value, gpointer *orig_key);

void incrementArtistsNumAlbuns(char *artistId, gestorArtists *gestorArtist);

void colocaZeroVezesTop10(gestorArtists *GestorArtists);

void insertListaQuery2(gestorArtists *gestorArtists, Artists *artist);

void CriaListasQuery2(gestorArtists *gestorArtists);

GList *getGListQuery2GestorArtist(gestorArtists *gestorArtists);

#endif // _GESTORARTISTS_H_
