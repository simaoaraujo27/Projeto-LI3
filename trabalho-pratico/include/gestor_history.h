#ifndef _GESTORHISTORY_H_
#define _GESTORHISTORY_H_

typedef struct gestorHistory gestorHistory;

#include "history.h"
#include <stdio.h>
#include <glib.h>
#include "utils.h"

gestorHistory *initGestorHistory(const char *errorsFilePath);
void freeGestorHistory(gestorHistory *gestor);

void parserHistory(GHashTable *historyTable, History *history, FILE *errorsFile,
                   char *line);
int GestorHistory(gestorHistory *gestor, char *historyPath);

#endif