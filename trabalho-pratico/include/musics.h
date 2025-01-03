#ifndef _MUSICS_H_
#define _MUSICS_H_

#include <glib.h>
#include <stdbool.h>

typedef struct musics Musics;

void setMusicId(Musics *m, char *id);
void setMusicTitle(Musics *m, char *title);
void setMusicArtistId(Musics *m, char *artist_id);
void setMusicDurationSeconds(Musics *m, int durationSeconds);
void setMusicGenre(Musics *m, char *genre);
void setMusicYear(Musics *m, int year);

Musics *separateMusics(char *line);
bool validateMusic(Musics *music);

char *getMusicId(gpointer music);
char *getMusicArtistId(gpointer music);
char *getMusicAlbumId(gpointer music);
int getMusicDuration(gpointer music);
char *getMusicGenre(gpointer music);

void destroyMusic(Musics *music);

#endif