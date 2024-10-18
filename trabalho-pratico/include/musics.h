#ifndef _MUSICS_H_
#define _MUSICS_H_

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct musics Musics;

Musics *separateMusics(char *line);
void parseMusics(FILE *fp, GHashTable *musicsTable);
void destroyMusic(gpointer music);

#endif