#include "artists.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artists {
  int id;                  // identificador único do artista
  char *nome;              // nome do artista
  char *descricao;         // descrição do artista
  int dinheiro_por_musica; // dinheiro auferido de cada vez que uma das músicas
                           // do artista é reproduzida
  char *listaIdArtistas;    // lista de identificadores únicos dos seus
                           // constituintes, no caso de se tratar de um artista
                           // coletivo. Este campo pode ser uma lista vazia.
  char *nacionalidade;     // nacionalidade do artista.
  bool artista_solo; // tipo de artista, i.e., individual ou grupo musical, caso
                     // individual = True, grupo = False
};
