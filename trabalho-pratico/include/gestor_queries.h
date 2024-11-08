#ifndef _GESTOR_QUERIES_H
#define _GESTOR_QUERIES_H

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum codigoMusica;

// char *calculate_age(char *birth_date);

/* Listar o resumo de um utilizador, consoante o identificador recebido por
 * argumento. */
void query1(GHashTable *usersTable, char *line, int i);

int temAspas(char *line);

/* top N artistas com maior discografia */
void query2(int numeroArtistas, char *country, GHashTable *artistsTable,
            GHashTable *musicsTable, char *line, int i);


// Serve para o QuickSort
int compare(const void *a, const void *b);

/* géneros de música mais populares numa determinada faixa etária */
// void query3(int minAge, int maxAge, int array[121][10], GHashTable *musicsTable, int i);

#endif
