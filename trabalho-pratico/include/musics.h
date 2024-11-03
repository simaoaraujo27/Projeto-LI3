#ifndef _MUSICS_H_
#define _MUSICS_H_

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct musics Musics;

Musics *separateMusics(char *line);
bool validateMusic(Musics *music);
void parseMusics(FILE *fp, GHashTable *musicsTable);
void destroyMusic(gpointer music);

char *getMusicId(gpointer music);
char *getMusicTitle(gpointer music);
char *getMusicArtistId(gpointer music);
int getMusicDuration(gpointer music);
char *getMusicGenre(gpointer music);
int getMusicYear(gpointer music);
char *getMusicLyrics(gpointer music);
typedef struct genreLikes GenreLikes;

#endif