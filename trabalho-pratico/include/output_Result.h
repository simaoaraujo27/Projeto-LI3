#ifndef _OUTPUT_RESULT_H_
#define _OUTPUT_RESULT_H_

#include <glib.h>
#include <stdio.h>

void printQuery2(GList *listaResposta, FILE *newFile, int numeroArtists,
                 int temS, char *country);

void printQuery4(FILE *newFile, int temS, char *name, char *type,
                 int countTop10);

void writeFile(FILE *newFile, char *text);

void MakeQuery1User(gpointer orig_key, FILE *newFile, int temS);

void MakeQuery1Artist(gpointer orig_key, FILE *newFile, int temS);

#endif