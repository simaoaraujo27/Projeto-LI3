#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

#include "artists.h"

typedef struct gestorArtists gestorArtists;

gestorArtists *initGestorArtists(const char *errorsFilePath);

GHashTable *getArtistTable(gestorArtists *gestorArtist);

GArray *getGArrayTops10(gestorArtists *gestorArtists);

void freeGestorArtists(gestorArtists *gestor);

int GestorArtists(gestorArtists *gestor, char *artistsPath);

gboolean lookUpArtistsHashTable(gestorArtists *gestorArtist, char *line,
                                gpointer *value, gpointer *orig_key);

void incrementArtistsNumAlbuns(char *artistId, gestorArtists *gestorArtist);

void colocaZero(gestorArtists *GestorArtists);

#endif // _GESTORARTISTS_H_
