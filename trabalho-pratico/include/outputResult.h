#ifndef _OUTPUTRESULT_H_
#define _OUTPUTRESULT_H_

#include <glib.h>
#include <stdio.h>

void printQuery2(GList *listaResposta, FILE *newFile, int numeroArtists,
                 int temS, char *country);

void printQuery4(FILE *newFile, int temS, char *name, char *type,
                 int countTop10);

void writeFile(FILE *newFile, char *text);

#endif