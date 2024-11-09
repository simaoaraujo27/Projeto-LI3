#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

#include <stdio.h>
#include "users.h"

void parseUsers(FILE *fp, GHashTable *usersTable,
                GHashTable *musicsTable);

#endif