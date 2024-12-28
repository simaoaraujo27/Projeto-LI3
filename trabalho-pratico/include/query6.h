#ifndef _QUERY6_H_
#define _QUERY6_H_

typedef struct categoriaTempo artistaTempo;
typedef struct categoriaTempo albumTempo;
typedef struct categoriaTempo generoTempo;

#include "gestor_users.h"

void query6(char *user_id, int year, int N, gestorHistory *gestorHistory);

#endif