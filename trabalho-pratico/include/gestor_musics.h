#ifndef _GESTOR_MUSICS_H_
#define _GESTOR_MUSICS_H_

#include "gestor_artists.h"
#include "musics.h"
#include <stdio.h>

typedef struct gestorMusics gestorMusics;

void parseMusics(FILE *fp, gestorMusics *gestorMusic,
                 gestorArtists *gestorArtist);

gestorMusics *initGestorMusics(const char *errorsFilePath,
                               GHashTable *musicsTable);

void freeGestorMusics(gestorMusics *gestor);

GHashTable *getMusicsTable(gestorMusics *gestorMusic);

#endif