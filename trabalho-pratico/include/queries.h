#ifndef _QUERIES_H
#define _QUERIES_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

char *calculate_age(char *birth_date);

/* Listar o resumo de um utilizador, consoante o identificador recebido por argumento. */
void query1(GHashTable *usersTable, char *line, int i);

/* top N artistas com maior discografia */
void query2();

/* géneros de música mais populares numa determinada faixa etária */
void query3();

#endif