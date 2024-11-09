#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

#include "gestor_musics.h"
#include "users.h"
#include <stdio.h>

typedef struct gestorUsers gestorUsers;

void parseUsers(FILE *fp, gestorUsers *gestorUser, gestorMusics *gestorMusic);

gestorUsers *initGestorUsers(const char *errorsFilePath,
                             GHashTable *usersTable);

void freeGestorUsers(gestorUsers *gestorUser);

GHashTable *getUsersTable(gestorUsers *gestorUser);

#endif