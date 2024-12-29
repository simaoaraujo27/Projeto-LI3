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

int getNUsers(gestorUsers *gestorUser);

char **insertIdsToArray(gestorUsers *gestorUsers, int numUtilizadores);

int procuraIndexHashTable(char *user, gestorUsers *gestorUsers);

gboolean pertenceAosUsernames(char *username, gestorUsers *gestorUsers);

void preencheMatriz(int **matrizClassificaoMusicas, int numGeneros,
                    char **nomesGeneros, gestorUsers *gestorUsers,
                    char **idsUtilizadores);

#endif