#ifndef _QUERY5_H_
#define _QUERY5_H_

typedef struct argumentosQuery5 argumentosQuery5;

#include "gestores.h"

argumentosQuery5 *initArgumentosQuery5();
void alocaMatriz(Gestores *gestor, argumentosQuery5 *a);
void constroiQuery5(Gestores *gestor, argumentosQuery5 *a);
void destroiArgumentosQuery5(argumentosQuery5 *a);

    void query5(Gestores *gestor, int numRecomendacoes, char *idUtilizadorAlvo,
                int i, argumentosQuery5 *a);

#endif