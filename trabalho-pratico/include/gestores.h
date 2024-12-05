#ifndef _GESTORES_H_
#define _GESTORES_H_

typedef struct gestores Gestores;

#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Gestores *initgestor(int *flag);

gestorArtists *pegarGestorArtist(Gestores *gestor);

gestorMusics *pegarGestorMusic(Gestores *gestor);

gestorUsers *pegarGestorUser(Gestores *gestor);

void destroyGestor(Gestores *gestor);

#endif