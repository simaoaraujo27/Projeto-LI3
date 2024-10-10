#include "artists.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Artists *newArtist(int id, char *nome, char *descricao, int dinheiro_por_musica,
                   int *listaIdArtistas, char *nacionalidade,
                   bool artista_solo) {
  Artists *artista;
  artista = malloc(sizeof(Artists));
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
