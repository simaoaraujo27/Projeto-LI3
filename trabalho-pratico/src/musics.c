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

void parseMusics(FILE *fp) {
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    Musics *music = separateMusics(line);
  }

  free(line);
}

void destroyMusic(gpointer user) {
    return;
}