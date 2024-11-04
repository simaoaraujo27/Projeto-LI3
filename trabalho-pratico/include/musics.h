#ifndef _MUSICS_H_
#define _MUSICS_H_

#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct musics Musics;

void setMusicId (Musics *m, char *id);
void setMusicTitle (Musics *m, char *title);
void setMusicArtistId (Musics *m, char *artist_id);
void setMusicDurationSeconds (Musics *m, int durationSeconds);
void setMusicGenre (Musics *m, char *genre);
void setMusicYear (Musics *m, int year);
void setMusicLyrics (Musics *m, char *lyrics);

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
//typedef struct genreLikes GenreLikes;

//GenreLikes *createGenre(char *genero);

#endif