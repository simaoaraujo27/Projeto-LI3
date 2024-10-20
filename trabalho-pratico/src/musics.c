#include "musics.h"
#include "validation.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musics {
  int id;              // identificador único da música
  char *title;         // nome da música
  char *artist_id;     // lista de identificadores dos autores da música
  int durationSeconds; // tempo de duração
  char *genre;         // género da música
  int year;            // ano de lançamento
  char *lyrics;        // letra da música
};

Musics *separateMusics(char *line) {
  // Separa cada linha pelas suas respetivas variáveis

  Musics *music = malloc(sizeof(struct musics));
  if (!music) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  music->id = atoi(strsep(&line, ";"));
  music->title = strdup(strsep(&line, ";"));
  music->artist_id = strdup(strsep(&line, ";"));
  char *duration_str = strdup(strsep(&line, ";"));
  music->genre = strdup(strsep(&line, ";"));
  music->year = atoi(strsep(&line, ";"));
  music->lyrics = strdup(strsep(&line, ";"));

  if (validateDuration(duration_str))
    music->durationSeconds = atoi(duration_str) /* horas */ * 3600 +
                             atoi(duration_str + 3) /* minutos */ * 60 +
                             atoi(duration_str + 6) /* segundos */;
  else
    music->durationSeconds = -1;

  return music;
}

bool validateMusic(Musics *music) {
  return (music->durationSeconds != -1 && music->year <= 2024);
}

void parseMusics(FILE *fp, GHashTable *musicsTable) {
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    Musics *music = separateMusics(line);
    // Insere na HashTable usando o music->artist_id como key
    g_hash_table_insert(musicsTable, g_strdup(music->artist_id), music);
  }

  free(line);
}

void destroyMusic(gpointer music) {
  Musics *m = (Musics *)music;

  free(m->title);
  free(m->artist_id);
  free(m->genre);
  free(m->lyrics);

  free(m);
}

int getMusicId(gpointer music) {
  struct musics *m = (struct musics *)music;
  return (m->id);
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

char *getMusicLyrics(gpointer music) {
  struct musics *m = (struct musics *)music;
  return strdup(m->lyrics);
}