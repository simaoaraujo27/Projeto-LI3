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

GHashTable *getMusicsTable(gestorMusics *gestorMusic);

GHashTableIter iterInitMusicsHashTable(gestorMusics *gestorMusics);

gboolean iter_HashTableMusics(gpointer *key1, gpointer *value1,
                              GHashTableIter iter);

gboolean lookUpMusicsHashTable(gestorMusics *gestormusic, char *line,
                               gpointer *value, gpointer *orig_key);

void processAllMusics(gestorMusics *gestorMusics, int numeroArtistas,
                      char *country, GList **listaResposta,
                      gestorArtists *gestorArtists);

void incrementMusicRep(char *musicId, gestorMusics *gestorMusics,
                       gestorArtists *gestorArtists);
                      
#endif