#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

#include "users.h"

void parseUsers(FILE *fp, GHashTable *usersTable, GHashTable *usersQ3Table,
                GHashTable *musicsTable);

#endif