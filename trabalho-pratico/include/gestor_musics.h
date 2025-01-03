#ifndef _GESTOR_MUSICS_H_
#define _GESTOR_MUSICS_H_

#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "musics.h"
#include <glib.h>
#include <stdio.h>

typedef struct gestorMusics gestorMusics;

int GestorMusics(gestorMusics *gestorMusic, gestorArtists *gestorArtist,
                 gestorAlbuns *gestorAlbuns, char *musicsPath);

gestorMusics *initGestorMusics(const char *errorsFilePath);

void freeGestorMusics(gestorMusics *gestor);

int getMusicsNGenres(gestorMusics *gestorMusic);

char **insertGenreToArray(gestorMusics *gestorMusics, int numGeneros);

gboolean lookUpMusicsHashTable(gestorMusics *gestormusic, char *line,
                               gpointer *value, gpointer *orig_key);

void incrementRecipeArtist(char *musicId, gestorMusics *gestorMusics,
                           gestorArtists *gestorArtists);

#endif