#ifndef _GESTOR_MUSICS_H_
#define _GESTOR_MUSICS_H_

typedef struct gestorMusics gestorMusics;

#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "musics.h"
#include <glib.h>
#include <stdio.h>

int GestorMusics(Gestores *gestor, char *musicsPath);

gestorMusics *initGestorMusics();

void freeGestorMusics(gestorMusics *gestor);

int getMusicsNGenres(gestorMusics *gestorMusic);

char **insertGenreToArray(gestorMusics *gestorMusics, int numGeneros);

gboolean lookUpMusicsHashTable(gestorMusics *gestormusic, char *line,
                               gpointer *value, gpointer *orig_key);

void incrementRecipeArtist(char *musicId, gestorMusics *gestorMusics,
                           gestorArtists *gestorArtists);

#endif