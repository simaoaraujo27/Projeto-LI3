#include "artists.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artists {
  int id;                // identificador único do artista
  char *name;            // nome do artista
  char *description;     // descrição do artista
  int recipe_per_stream; // dinheiro auferido de cada vez que uma das músicas
                         // do artista é reproduzida
  char *id_constituent;  // lista de identificadores únicos dos seus
                         // constituintes, no caso de se tratar de um artista
                         // coletivo. Este campo pode ser uma lista vazia.
  char *country;         // nacionalidade do artista.
  bool type; // tipo de artista, i.e., individual ou grupo musical, caso
             // individual = True, grupo = False
};
