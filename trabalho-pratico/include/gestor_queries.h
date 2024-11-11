#ifndef _GESTOR_QUERIES_H_
#define _GESTOR_QUERIES_H_

#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "query3.h"

void gestorQueries(char *line, Gestores *gestor, int firstOcorr, int maxAge,
                   int minAge, NodoMusica *lista, int i,
                   double *total_time_query1, double *total_time_query2,
                   double *total_time_query3);

#endif