#ifndef _GESTORHISTORY_H_
#define _GESTORHISTORY_H_

typedef struct gestorHistory gestorHistory;

#include "gestor_musics.h"
#include "gestor_users.h"
#include "history.h"
#include "utils.h"
#include <glib.h>
#include <stdio.h>

gestorHistory *initGestorHistory(const char *errorsFilePath);
void freeGestorHistory(gestorHistory *gestor);

void parserHistory(History *history, char *line, char *copia, Gestores *gestor);

int GestorHistory(Gestores *gestor, char *historyPath);

#endif