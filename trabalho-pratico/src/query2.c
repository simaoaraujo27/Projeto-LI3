#include "artists.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_prints.h"
#include "gestor_queries.h"
#include "musics.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void query2(int numeroArtistas, char *country, gestorArtists *gestorArtist,
            gestorMusics *gestorMusic, char *line, int i) {
  FILE *newFile;
  char *path = "./resultados/commandx_output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt", i);
  newFile = fopen(new, "w");

  GHashTableIter iter;
  g_hash_table_iter_init(&iter, getMusicsTable(gestorMusic));
  gpointer key1, value1;
  GList *listaResposta = NULL;
  char *artistId;
  char *key;
  int l = 0;
  int duracao = 0;
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Musics *music = (Musics *)value1;
    artistId = getMusicArtistId(music);
    remove_quotes(artistId);
    removeFstLast(artistId);
    duracao = getMusicDuration(music);
    gpointer value;
    gpointer orig_key;
    l = strlen(artistId);
    for (int j = 0; j < l; j += 12) {
      if (j == 0)
        artistId = artistId + 1;
      else
        artistId = artistId + 3;
      key = strdup(strsep(&artistId, "'"));
      if (g_hash_table_lookup_extended(getArtistTable(gestorArtist), key,
                                       &orig_key, &value)) {
        increment_artist_discografia(value, duracao, &listaResposta,
                                     numeroArtistas, country);
      }
    }
  }
  printQuery2(&listaResposta, numeroArtistas, newFile);
  colocaZero(getArtistTable(gestorArtist));
  g_list_free(listaResposta);
  free(new);
}