#ifndef _USERS_H_
#define _USERS_H_

#include "validation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

typedef struct users Users;

Users *separateUsers(char *line);
void parseUsers(FILE *fp, GHashTable *usersTable);
void destroyUser(gpointer user);

#endif
