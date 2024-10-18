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
void parseArtists(FILE *fp, GHashTable *artistsTable);
void destroyArtist(gpointer artist);
char *getArtistName(Artists *artist);

#endif