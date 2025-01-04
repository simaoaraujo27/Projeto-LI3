#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

typedef struct gestorUsers gestorUsers;

#include "gestor_musics.h"
#include "gestores.h"
#include "nodo_musica.h"
#include "users.h"

#include <glib.h>
#include <stdio.h>

int GestorUsers(Gestores *gestor, char *usersPath);

gestorUsers *initGestorUsers();

void freeGestorUsers(gestorUsers *gestorUser);

gboolean lookUpUsersHashTable(gestorUsers *gestorUser, char *line,
                              gpointer *value, gpointer *orig_key);

void processAllUsers(Gestores *gestor, NodoMusica **lista);

int getNUsers(gestorUsers *gestorUser);

void preencheMatriz(int **matrizClassificaoMusicas, int numGeneros,
                    char **nomesGeneros, gestorUsers *gestorUsers,
                    char **idsUtilizadores);

gboolean lookUpQuery6Table(gestorUsers *gestorUser, char *line, gpointer *value,
                           gpointer *orig_key);

void setQuery6Table(char *line, gestorUsers *gestorUsers);

#endif