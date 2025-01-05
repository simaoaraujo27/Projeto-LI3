#ifndef _GESTOR_QUERIES_H_
#define _GESTOR_QUERIES_H_

#include "compare_files.h"
#include "gestor_albuns.h"
#include "gestor_artists.h"
#include "gestor_history.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "query3.h"
#include "query5.h"

void gestorQueries(char *line, Gestores *gestor, NodoMusica *lista, int i,
                   temposTestes *t);
#endif