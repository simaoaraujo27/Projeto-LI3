#ifndef _GESTOR_PRINTS_H_
#define _GESTOR_PRINTS_H_

#include <glib.h>
#include <stdio.h>

void printQuery2(GList *listaResposta, FILE *newFile, int numeroArtists,
                 int temS, char *country);

void printQuery4(FILE *newFile, int temS, char *name, char *type,
                 int countTop10);

#endif