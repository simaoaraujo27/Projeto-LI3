#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

#include "gestor_musics.h"
#include "users.h"
#include <stdio.h>

typedef struct gestorUsers gestorUsers;

int GestorUsers( gestorUsers *gestorUser, gestorMusics *gestorMusic,
                char *usersPath);

gestorUsers *initGestorUsers(const char *errorsFilePath);

void freeGestorUsers(gestorUsers *gestorUser);

GHashTable *getUsersTable(gestorUsers *gestorUser);

#endif