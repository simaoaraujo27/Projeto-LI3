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
bool validateUser(Users *user);
void destroyUser(gpointer user);

char *getUserUsername(gpointer user);
char *getUserEmail(gpointer user);
char *getUserFirstName(gpointer user);
char *getUserLastName(gpointer user);
char *getUserBirthDate(gpointer user);
char *getUserCountry(gpointer user);
char *getUserSubscriptionType(gpointer user);
char *getUserLikedMusicsId(gpointer user);

#endif
