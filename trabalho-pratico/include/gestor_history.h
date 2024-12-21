#ifndef _GESTORHISTORY_H_
#define _GESTORHISTORY_H_

typedef struct gestorHistory gestorHistory;

#include "history.h"
#include "utils.h"
#include <glib.h>
#include <stdio.h>

gestorHistory *initGestorHistory(const char *errorsFilePath);
void freeGestorHistory(gestorHistory *gestor);

void parserHistory(GHashTable *historyTable, History *history, FILE *errorsFile,
                   char *line, char *copia);
int GestorHistory(gestorHistory *gestor, char *historyPath);

#endif