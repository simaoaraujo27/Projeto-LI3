#include "musics.h"

struct musics {
  char *id;            // identificador único da música
  char *title;         // nome da música
  char *artist_id;     // lista de identificadores dos autores da música
  int durationSeconds; // tempo de duração
  char *genre;         // género da música
  int year;            // ano de lançamento
};

void setMusicId(Musics *m, char *id) {
  remove_quotes(id);
  m->id = id;
}

void setMusicTitle(Musics *m, char *title) { m->title = title; }

void setMusicArtistId(Musics *m, char *artist_id) { m->artist_id = artist_id; }

void setMusicDurationSeconds(Musics *m, int durationSeconds) {
  m->durationSeconds = durationSeconds;
}

void setMusicGenre(Musics *m, char *genre) { m->genre = genre; }

void setMusicYear(Musics *m, int year) { m->year = year; }
/*
void setMusicLyrics(Musics *m, char *lyrics) { m->lyrics = lyrics; } */

Musics *separateMusics(char *line) {
  // Separa cada linha pelas suas respetivas variáveis

  Musics *music = malloc(sizeof(struct musics));
  if (!music) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  setMusicId(music, strdup(strsep(&line, ";")));
  setMusicTitle(music, strdup(strsep(&line, ";")));
  setMusicArtistId(music, strdup(strsep(&line, ";")));
  char *duration_str = strdup(strsep(&line, ";"));
  setMusicGenre(music, strdup(strsep(&line, ";")));
  setMusicYear(music, atoi(strdup(strsep(&line, ";"))));
  /* setMusicLyrics(music, strdup(strsep(&line, ";"))); */

  if (validateDuration(duration_str)) {
    setMusicDurationSeconds(music,
                            atoi(duration_str) /* horas */ * 3600 +
                                atoi(duration_str + 3) /* minutos */ * 60 +
                                atoi(duration_str + 6) /* segundos */);
  } else
    setMusicDurationSeconds(music, -1);

  return music;
}

bool validateMusic(Musics *music) {
  return (music->durationSeconds != -1 && music->year <= 2024);
}

char *pegarMusicId(Musics *m) { return strdup(m->id); }

char *pegarMusicTitle(Musics *m) { return strdup(m->title); }

char *pegarMusicArtistId(Musics *m) { return strdup(m->artist_id); }

int pegarMusicDuration(Musics *m) { return (m->durationSeconds); }

char *pegarMusicGenre(Musics *m) { return strdup(m->genre); }

int pegarMusicYear(Musics *m) { return (m->year); }

/* char *pegarMusicLyrics(Musics *m) { return strdup(m->lyrics); }
 */
char *getMusicId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->id);
}

char *getMusicTitle(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->title);
}

char *getMusicArtistId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->artist_id);
}

int getMusicDuration(gpointer music) {
  struct musics *m = (struct musics *)music;
  return (m->durationSeconds);
}

char *getMusicGenre(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->genre);
}

int getMusicYear(gpointer music) {
  struct musics *m = (struct musics *)music;
  return (m->year);
}

/* char *getMusicLyrics(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->lyrics);
} */

void destroyMusic(gpointer music) {
  Musics *m = (Musics *)music;

  free(m->title);
  free(m->artist_id);
  free(m->genre);
  /* free(m->lyrics); */

  free(m);
}