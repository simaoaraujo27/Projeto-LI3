#ifndef _GESTOR_USERS_H_
#define _GESTOR_USERS_H_

#include "users.h"

typedef struct gestorUsers GestorUsers;

void parseUsers(FILE *fp, GHashTable *usersTable);



#endif