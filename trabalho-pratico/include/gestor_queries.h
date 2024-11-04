#ifndef _GESTOR_QUERIES_H
#define _GESTOR_QUERIES_H

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *calculate_age(char *birth_date);

/* Listar o resumo de um utilizador, consoante o identificador recebido por
 * argumento. */
void query1(GHashTable *usersTable, char *line, int i);

int temAspas(char *line);

/* top N artistas com maior discografia */
void query2(int numeroArtistas, char *country, GHashTable *artistsTable,
            GList *listMusics, char *line, int i);

/* géneros de música mais populares numa determinada faixa etária */
void query3(int minAge, int maxAge, GList *listUsers, GHashTable *musicsTable,
            int i);

#endif