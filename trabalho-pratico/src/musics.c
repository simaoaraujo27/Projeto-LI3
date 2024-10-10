#include "musics.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Musics *newMusic(int id, char *title, int *artist_id, int duration, char *genre,
                 int year, char *lyrics) {
  Musics *musica;
  musica = malloc(sizeof(Musics));
  if (!musica) {
    fprintf(stderr, "Malloc failed!");
    return -1;
  }
  musica->id = id;
  musica->title = strdup(title);
  musica->artist_id = artist_id;
  musica->duration = duration;
  musica->genre = strdup(genre);
  musica->year = year;
  musica->lyrics = strdup(lyrics);
  return musica;
}