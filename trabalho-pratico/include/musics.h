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


Musics *separateMusics(char *line);
bool validateMusic(Musics *music);


char *pegarMusicId(Musics *m);
char *pegarMusicTitle(Musics *m);
char *pegarMusicArtistId(Musics *m);
int pegarMusicDuration(Musics *m);
char *pegarMusicGenre(Musics *m);
int pegarMusicYear(Musics *m);
char *pegarMusicLyrics(Musics *m);

char *getMusicId(gpointer music);
char *getMusicTitle(gpointer music);
char *getMusicArtistId(gpointer music);
int getMusicDuration(gpointer music);
char *getMusicGenre(gpointer music);
int getMusicYear(gpointer music);
char *getMusicLyrics(gpointer music);

void destroyMusic(gpointer music);

#endif