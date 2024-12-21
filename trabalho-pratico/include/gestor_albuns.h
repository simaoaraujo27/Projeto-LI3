#ifndef _GESTORALBUNS_H_
#define _GESTORALBUNS_H_

typedef struct gestorAlbuns gestorAlbuns;

#include "albuns.h"
#include <glib.h>
#include <stdio.h>

gestorAlbuns *initGestorAlbuns(const char *errorsFilePath);
void freeGestorAlbuns(gestorAlbuns *gestor);
void parserAlbum(GHashTable *albunsTable, Albuns *album, FILE *errorsFile,
                 char *line);
int GestorAlbuns(gestorAlbuns *gestor, char *albunsPath);
gboolean lookUpAlbunsHashTable(gestorAlbuns *gestorAlbuns, char *key,
                               gpointer *value, gpointer *orig_key);

#endif