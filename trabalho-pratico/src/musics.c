#include "musics.h"
#include "utils.h"
#include "validation.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musics {
  char *id;
  char *title;
  char *artist_id;
  char *album_id;
  int durationSeconds;
  char *genre;
  int year;
  int reproducoes;
};

// setters

void setMusicId(Musics *m, char *id) {
  remove_quotes(id);
  m->id = id;
}

void setMusicTitle(Musics *m, char *title) { m->title = title; }

void setMusicArtistId(Musics *m, char *artist_id) { m->artist_id = artist_id; }

void setMusicAlbumId(Musics *m, char *album_id) { m->album_id = album_id; }

void setMusicDurationSeconds(Musics *m, int durationSeconds) {
  m->durationSeconds = durationSeconds;
}

void setMusicGenre(Musics *m, char *genre) { m->genre = genre; }

void setMusicYear(Musics *m, int year) { m->year = year; }

// preenche todos os campos de uma música
Musics *separateMusics(char *line) {
  Musics *music = malloc(sizeof(struct musics));
  if (!music) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  setMusicId(music, strdup(strsep(&line, ";")));
  setMusicTitle(music, strdup(strsep(&line, ";")));
  setMusicArtistId(music, strdup(strsep(&line, ";")));
  setMusicAlbumId(music, strdup(strsep(&line, ";")));

  char *duration_str = strdup(strsep(&line, ";"));
  setMusicGenre(music, strdup(strsep(&line, ";")));

  char *year_str = strdup(strsep(&line, ";"));
  setMusicYear(music, atoi(year_str));
  free(year_str);

  if (validateDuration(duration_str)) {
    setMusicDurationSeconds(music, atoi(duration_str) * 3600 +
                                       atoi(duration_str + 3) * 60 +
                                       atoi(duration_str + 6));
  } else {
    setMusicDurationSeconds(music, -1);
  }
  music->reproducoes = 0;
  free(duration_str);
  return music;
}

bool validateMusic(Musics *music) {
  return (music->durationSeconds != -1 && music->year <= 2024);
}

// getters

char *getMusicId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->id);
}

char *getMusicArtistId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->artist_id);
}

char *getMusicAlbumId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->album_id);
}

int getMusicDuration(gpointer music) {
  struct musics *m = (struct musics *)music;
  return (m->durationSeconds);
}

char *getMusicGenre(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->genre);
}

void destroyMusic(Musics *music) {
  if (music) {
    free(music->id);
    free(music->title);
    free(music->artist_id);
    free(music->album_id);
    free(music->genre);
    free(music);
  }
}
