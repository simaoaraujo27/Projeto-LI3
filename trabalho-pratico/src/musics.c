#include "musics.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct musics {
  int id;         // identificador único da música
  char *title;    // nome da música
  char *artist_id; // lista de identificadores dos autores da música
  int duration;   // tempo de duração
  char *genre;    // género da música
  int year;       // ano de lançamento
  char *lyrics;   // letra da música
};

/* Musics *newMusic(int id, char *title, int *artist_id, int duration, char *genre,
                 int year, char *lyrics) {
  Musics *musica = malloc(sizeof(struct musics));
  if (!musica) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }
  musica->id = id;
  musica->title = strdup(title);
  musica->artist_id = artist_id;
  musica->duration = duration;
  musica->genre = strdup(genre);
  musica->year = year;
  musica->lyrics = strdup(lyrics);
  return musica;
} */