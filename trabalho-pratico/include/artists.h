#ifndef _ARTISTS_H_
#define _ARTISTS_H_

#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum tipoArtista;

typedef struct artists Artists;

Artists *separateArtists(char *line);
bool validateArtist(Artists *artist);
void parseArtists(FILE *fp, GHashTable *artistsTable);
void destroyArtist(gpointer artist);
void increment_artist_discografia(gpointer value, int duracao,
                                  Artists *arrayResposta[], int numeroArtistas);
char *getArtistId(gpointer artist);
char *getArtistName(gpointer artist);
char *getArtistDescription(gpointer artist);
int getArtistRecipePerStream(gpointer artist);
char *getArtistIdConstituent(gpointer artist);
char *getArtistCountry(gpointer artist);
enum tipoArtista getArtistType(gpointer artist);
int getArtistDiscografia(gpointer artist);
void PrintArt(Artists *arrayResposta[], int numeroArtistas);

#endif