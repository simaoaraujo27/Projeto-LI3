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

int getArtistId(gpointer artist);
char *getArtistName(gpointer artist);
char *getArtistDescription(gpointer artist);
int getArtistRecipePerStream(gpointer artist);
char *getArtistIdConstituent(gpointer artist);
char *getArtistCountry(gpointer artist);
enum tipoArtista getArtistType(gpointer artist);

#endif