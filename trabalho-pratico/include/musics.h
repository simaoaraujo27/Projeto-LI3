#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct musics {
  int id;         // identificador único da música
  char *title;    // nome da música
  int *artist_id; // lista de identificadores dos autores da música
  int duration;   // tempo de duração
  char *genre;    // género da música
  int year;       // ano de lançamento
  char *lyrics;   // letra da música
} Musics;