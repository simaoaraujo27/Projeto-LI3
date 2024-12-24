#ifndef _GESTORHISTORY_H_
#define _GESTORHISTORY_H_

typedef struct gestorHistory gestorHistory;

#include "gestor_musics.h"
#include "history.h"
#include "utils.h"
#include <glib.h>
#include <stdio.h>

gestorHistory *initGestorHistory(const char *errorsFilePath);
void freeGestorHistory(gestorHistory *gestor);

void parserHistory(GHashTable *historyTable, History *history, FILE *errorsFile,
                   char *line, char *copia, gestorMusics *gestorMusics, gestorArtists *gestorArtists);
int GestorHistory(gestorHistory *gestor, gestorMusics *gestorMusic, gestorArtists *gestorArtists,
                  char *historyPath);

#endif