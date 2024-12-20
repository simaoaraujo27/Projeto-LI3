#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

typedef struct gestorUsers gestorUsers;

#include "gestor_musics.h"
#include "gestores.h"
#include "nodo_musica.h"
#include "users.h"

#include <glib.h>
#include <stdio.h>

int GestorUsers(gestorUsers *gestorUser, gestorMusics *gestorMusic,
                char *usersPath);

gestorUsers *initGestorUsers(const char *errorsFilePath);

void freeGestorUsers(gestorUsers *gestorUser);

gboolean lookUpUsersHashTable(gestorUsers *gestorUser, char *line,
                              gpointer *value, gpointer *orig_key);

GHashTable *getUsersTable(gestorUsers *gestorUser);

void processAllUsers(Gestores *gestor, NodoMusica **lista);

#endif