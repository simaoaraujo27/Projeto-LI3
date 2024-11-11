#ifndef _GESTORARTISTS_H_
#define _GESTORARTISTS_H_

#include "artists.h"

typedef struct gestorArtists gestorArtists;

gestorArtists *initGestorArtists(const char *errorsFilePath,
                                 GHashTable *artistsTable);

GHashTable *getArtistTable(gestorArtists *gestorArtist);

void freeGestorArtists(gestorArtists *gestor);

void parseArtists(FILE *fp, gestorArtists *gestor);

#endif // _GESTORARTISTS_H_
