#include "artists.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct artists {
  int id;                  // identificador único do artista
  char *nome;              // nome do artista
  char *descricao;         // descrição do artista
  int dinheiro_por_musica; // dinheiro auferido de cada vez que uma das músicas
                           // do artista é reproduzida
  int *listaIdArtistas;    // ista de identificadores únicos dos seus
                           // constituintes, no caso de se tratar de um artista
                           // coletivo. Este campo pode ser uma lista vazia.
  char *nacionalidade;     // nacionalidade do artista.
  bool artista_solo; // tipo de artista, i.e., individual ou grupo musical, caso
                     // individual = True, grupo = False
};

Artists *newArtist(int id, char *nome, char *descricao, int dinheiro_por_musica,
                   int *listaIdArtistas, char *nacionalidade,
                   bool artista_solo) {
  Artists *artista = malloc(sizeof(struct artists));
  if (!artista) {
    fprintf(stderr, "Malloc failed!");
    return -1;
  }
  artista->id = id;
  artista->nome = strdup(nome);
  artista->descricao = strdup(descricao);
  artista->dinheiro_por_musica = dinheiro_por_musica;
  artista->listaIdArtistas = listaIdArtistas;
  artista->nacionalidade = strdup(nacionalidade);
  artista->artista_solo = artista_solo;
  return artista;
}
