#ifndef _GESTOR_MUSICS_H_
#define _GESTOR_MUSICS_H_

#include "gestor_artists.h"
#include "musics.h"
#include <stdio.h>

typedef struct gestorMusics gestorMusics;

int GestorMusics(FILE *fp, gestorMusics *gestorMusic,
                  gestorArtists *gestorArtist, char *musicsPath);

gestorMusics *initGestorMusics(const char *errorsFilePath);

void freeGestorMusics(gestorMusics *gestor);

GHashTable *getMusicsTable(gestorMusics *gestorMusic);

#endif