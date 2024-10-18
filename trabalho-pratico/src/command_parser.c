#include "command_parser.h"
#include "validation.c"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Artists *separateArtists(char *line) {
  // Separa a linha e guarda os respetivos dados na struct artistas

  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  artist->id = atoi(strsep(&line, ";"));
  artist->name = strdup(strsep(&line, ";"));
  artist->description = strdup(strsep(&line, ";"));
  artist->recipe_per_stream = atoi(strsep(&line, ";"));
  artist->id_constituent = strdup(strsep(&line, ";"));
  artist->country = strdup(strsep(&line, ";"));
  if (!strcmp(strsep(&line, "\n"), "individual"))
    artist->tipo = Individual;
  else
    artist->tipo = Grupo;

  return artist;
}

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

Users *separateUsers(char *line) {
  // separa cada linha pelas suas respetivas variáveis
  Users *user = malloc(sizeof(struct users));
  if (!user) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  user->username = strdup(strsep(&line, ";"));
  user->email = strdup(strsep(&line, ";"));
  user->first_name = strdup(strsep(&line, ";"));
  user->last_name = strdup(strsep(&line, ";"));
  user->birth_date = strdup(strsep(&line, ";"));
  user->country = strdup(strsep(&line, ";"));
  user->subscription_type = strdup(strsep(&line, ";"));
  user->liked_musics_id = strdup(strsep(&line, ";"));

  return user;
}
