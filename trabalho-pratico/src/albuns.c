#include "albuns.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que armazena informações sobre um álbum
struct albuns {
  char *id;         // Identificador único do álbum
  char *title;      // Título do álbum
  char *artists_id; // Lista de identificadores únicos dos artistas que lançaram
                    // o álbum;
  char *year;      // Ano de lançamento
  char *producers; // Lista de produtores
};

// Funções get
char *getAlbumId(Albuns *album) { return album->id; }

char *getAlbumTitle(Albuns *album) { return album->title; }

char *getAlbumArtistsId(Albuns *album) { return album->artists_id; }

char *getAlbumYear(Albuns *album) { return album->year; }

char *getAlbumProducers(Albuns *album) { return album->producers; }

// Funções set
void setAlbumId(Albuns *album, char *id) {
  free(album->id); // Libera a memória antiga, se necessário
  album->id = strdup(id);
}

void setAlbumTitle(Albuns *album, char *title) {
  free(album->title);
  album->title = strdup(title);
}

void setAlbumArtistsId(Albuns *album, char *artists_id) {
  free(album->artists_id);
  album->artists_id = strdup(artists_id);
}

void setAlbumYear(Albuns *album, char *year) {
  free(album->year);
  album->year = strdup(year);
}

void setAlbumProducers(Albuns *album, char *producers) {
  free(album->producers);
  album->producers = strdup(producers);
}

Albuns *initAlbum() {
  Albuns *album = malloc(sizeof(struct albuns));
  if (album == NULL) {
    printf("Malloc Failed!\n");
    return NULL;
  }
  album->id = NULL;
  album->title = NULL;
  album->artists_id = NULL;
  album->year = NULL;
  album->producers = NULL;

  return album;
}

void destroyAlbum(Albuns *album) {
  free(album->id);
  free(album->title);
  free(album->artists_id);
  free(album->year);
  free(album->producers);
}

// Função que separa dados de um álbum a partir de uma linha do CSV
Albuns *separateAlbuns(char *line) {
  Albuns *album = initAlbum();
  setAlbumId(album, strdup(strsep(&line, ";")));
  setAlbumTitle(album, strdup(strsep(&line, ";")));
  setAlbumArtistsId(album, strdup(strsep(&line, ";")));
  setAlbumYear(album, strdup(strsep(&line, ";")));
  setAlbumProducers(album, strdup(strsep(&line, ";")));

  return album;
}
