#include "artists.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_prints.h"
#include "gestores.h"
#include "inputResult.h"
#include "musics.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que processa uma música
void processMusic(Musics *music, gestorArtists *gestorArtists,
                  int numeroArtistas, char *country, GList **listaResposta,
                  char *artistId) {
  remove_quotes(artistId); // Remove aspas do ID do artista
  removeFstLast(artistId); // Remove o primeiro e o último caractere do ID

  int duracao = getMusicDuration(music); // Obtém a duração da música
  gpointer value;
  gpointer orig_key;
  int l = strlen(artistId); // Tamanho do ID do artista

  // Percorre os ID's dos artistas
  for (int j = 0; j < l; j += 12) {
    char *key;
    if (j == 0)
      artistId = artistId + 1; // Ajusta o ponteiro
    else
      artistId =
          artistId + 3; // Ajusta o ponteiro para passar pelo espaço e ';'

    key =
        strdup(strsep(&artistId, "'")); // Extrai o ID do artista entre as aspas

    // Procura o artista na hashtable dos artistas
    gboolean found =
        lookUpArtistsHashTable(gestorArtists, key, &value, &orig_key);
    if (found) {
      // Incrementa a discografia do artista
      increment_artist_discografia(value, duracao, listaResposta,
                                   numeroArtistas, country);
    }

    free(key); // Liberta a key
  }
}

// Função principal que executa a query 2
void query2(int numeroArtistas, char *country, Gestores *gestor, int i,
            int temS) {
  FILE *newFile = createFile(i);
  gestorArtists *gestorArtists = pegarGestorArtist(gestor);

  if (numeroArtistas == 0) {
    fprintf(newFile, "\n");
    fclose(newFile);
    return;
  }
  GList *listaResposta = getGListQuery2GestorArtist(gestorArtists);
  if (country == NULL) {
    GList *listaResposta = getGListQuery2GestorArtist(gestorArtists);
    printQuery2(listaResposta, newFile, numeroArtistas, temS, NULL);
  } else {
    printQuery2(listaResposta, newFile, numeroArtistas, temS, country);
  }
}