#ifndef _GESTOR_QUERIES_H_
#define _GESTOR_QUERIES_H_

#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "query3.h"


void gestorQueries(char *line, gestorArtists *gestorArtists,
                   gestorMusics *gestorMusics, gestorUsers *gestorUsers,
                   int firstOcorr, int maxAge, int minAge, NodoMusica *lista,
                   int i);

#endif