#include "musics.h"
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
