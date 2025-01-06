#include "albuns.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct albuns {
  char *id;
  char *title;
  char *artists_id;
  char *year;
  char *producers;
};

char *getAlbumId(Albuns *album) { return strdup(album->id); }

void setAlbumId(Albuns *album, char *id) {
  free(album->id);
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
  if (album) {
    free(album->id);
    free(album->title);
    free(album->artists_id);
    free(album->year);
    free(album->producers);
    free(album);
  }
}

// função que preenche todos os campos do album
Albuns *separateAlbuns(char *line, gestorArtists *gestorArtists) {
  Albuns *album = initAlbum();
  char *token = strdup(strsep(&line, ";"));
  setAlbumId(album, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setAlbumTitle(album, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setAlbumArtistsId(album, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setAlbumYear(album, token);
  free(token);
  token = strdup(strsep(&line, ";"));
  setAlbumProducers(album, token);
  free(token);
  char *artists = strdup(album->artists_id);
  char *originalArtists = artists;
  remove_quotes(artists);
  removeFstLast(artists);
  int tamanho = strlen(artists);
  // Itera por todos os artists do álbum e incrementa o número de álbuns de cada
  // artista
  while (tamanho > 0) {
    if (tamanho == (int)strlen(artists)) {
      artists = artists + 1;
    } else
      artists = artists + 3;

    char *currentArtist = strdup(strsep(&artists, "'"));
    currentArtist[8] = '\0';
    incrementArtistsNumAlbuns(currentArtist, gestorArtists);

    tamanho -= 12;
    free(currentArtist);
  }
  free(originalArtists);

  return album;
}
