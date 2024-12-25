#include "albuns.h"
#include "utils.h"
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
char *getAlbumId(Albuns *album) { return strdup(album->id); }

char *getAlbumTitle(Albuns *album) { return strdup(album->title); }

char *getAlbumArtistsId(Albuns *album) { return strdup(album->artists_id); }

char *getAlbumYear(Albuns *album) { return strdup(album->year); }

char *getAlbumProducers(Albuns *album) { return strdup(album->producers); }

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

int numeroArtistas(char *album_id) {
  int nvirgulas = 0;
  for (int i = 0; album_id[i] != '\0'; i++) {
    nvirgulas += (album_id[i] == ',');
  }
  return nvirgulas + 1;
}

// Função que separa dados de um álbum a partir de uma linha do CSV
Albuns *separateAlbuns(char *line, gestorArtists *gestorArtists) {
  Albuns *album = initAlbum();
  setAlbumId(album, strdup(strsep(&line, ";")));
  setAlbumTitle(album, strdup(strsep(&line, ";")));
  setAlbumArtistsId(album, strdup(strsep(&line, ";")));
  setAlbumYear(album, strdup(strsep(&line, ";")));
  setAlbumProducers(album, strdup(strsep(&line, ";")));
  char *artists = strdup(album->artists_id);
  remove_quotes(artists);
  removeFstLast(artists);
  int tamanho = strlen(artists);
  while (tamanho > 0) {
    if (tamanho == (int)strlen(artists)) {
      artists = artists + 1;
    } else
      artists = artists + 3;

    char *currentArtist =
        strdup(strsep(&artists, "'")); // Separa o ID do artista
    currentArtist[8] = '\0';           // Limita o ID a 8 caracteres
    incrementArtistsNumAlbuns(currentArtist, gestorArtists);

    tamanho -= 12;
  }

  return album;
}
