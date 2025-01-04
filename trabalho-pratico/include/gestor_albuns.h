#ifndef _GESTORALBUNS_H_
#define _GESTORALBUNS_H_

typedef struct gestorAlbuns gestorAlbuns;

#include "albuns.h"
#include "gestor_artists.h"
#include "gestores.h"
#include <glib.h>
#include <stdio.h>

gestorAlbuns *initGestorAlbuns();
void freeGestorAlbuns(gestorAlbuns *gestor);
void parserAlbum(GHashTable *albunsTable, Albuns *album, Gestores *gestor,
                 char *line, char *copia, gestorArtists *gestorArtists);
int GestorAlbuns(Gestores *gestor, char *albunsPath);
gboolean lookUpAlbunsHashTable(gestorAlbuns *gestorAlbuns, char *key,
                               gpointer *value, gpointer *orig_key);

#endif