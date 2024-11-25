#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

#include "artists.h"

typedef struct gestorArtists gestorArtists;

gestorArtists *initGestorArtists(const char *errorsFilePath);

GHashTable *getArtistTable(gestorArtists *gestorArtist);

void freeGestorArtists(gestorArtists *gestor);

int GestorArtists( gestorArtists *gestor, char *artistsPath);

#endif // _GESTORARTISTS_H_
