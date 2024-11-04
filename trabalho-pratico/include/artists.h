#ifndef _ARTISTS_H_
#define _ARTISTS_H_

#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum tipoArtista;

typedef struct artists Artists;

Artists *separateArtists(char *line);
bool validateArtist(Artists *artist);

void setArtistId(Artists *a, char *id);
void setArtistName(Artists *a, char *name);
void setArtistDescription(Artists *a, char *description);
void setArtistRecipePerStream(Artists *a, int recipe_per_stream);
void setArtistIdConstituent(Artists *a, char *id_constituent);
void setArtistCountry(Artists *a, char *country);
void setArtistTipo(Artists *a, enum tipoArtista tipo);
void setArtistDiscografia(Artists *a, int discografia);

char *getArtistId(gpointer artist);
char *getArtistName(gpointer artist);
char *getArtistDescription(gpointer artist);
int getArtistRecipePerStream(gpointer artist);
char *getArtistIdConstituent(gpointer artist);
char *getArtistCountry(gpointer artist);
enum tipoArtista getArtistType(gpointer artist);
int getArtistDiscografia(gpointer artist);

void increment_artist_discografia(gpointer value, int duracao, GList **listaResposta, int numeroArtistas, char *country);
void procuraArt(Artists *artist, GList **listaResposta, int numeroArtistas);
void print(GList **listaResposta, int numeroArtistas, FILE *newFile);
void colocaZero(GHashTable *artistsTable);

void destroyArtist(gpointer artist);

#endif