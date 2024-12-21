#ifndef _GESTORALBUNS_H_
#define _GESTORALBUNS_H_

typedef struct gestorAlbuns gestorAlbuns;

#include "albuns.h"
#include "gestor_artists.h"
#include <glib.h>
#include <stdio.h>

gestorAlbuns *initGestorAlbuns(char *errorsFilePath);
void freeGestorAlbuns(gestorAlbuns *gestor);
void parserAlbum(GHashTable *albunsTable, Albuns *album, FILE *errorsFile,
                 char *line, char *copia, gestorArtists *gestorArtists);
int GestorAlbuns(gestorAlbuns *gestor, char *albunsPath,
                 gestorArtists *gestorArtists);
gboolean lookUpAlbunsHashTable(gestorAlbuns *gestorAlbuns, char *key,
                               gpointer *value, gpointer *orig_key);

#endif