#ifndef _GESTORPARSERS_H_
#define _GESTORPARSERS_H_

#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include <stdio.h>

int GestorParsers(FILE *fp, gestorArtists *gestorArtists,
                  gestorMusics *gestorMusics, gestorUsers *gestorUsers,
                  char *artistsPath, char *musicsPath, char *usersPath);

#endif