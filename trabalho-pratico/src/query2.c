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

// Função que executa a query 2
void query2(int numeroArtistas, char *country, Gestores *gestor, int i) {
  FILE *newFile = createFile(i);

  // Iterador para percorrer a hashtable das músicas
  GHashTableIter iter;
  iter = iterInitMusicsHashTable(pegarGestorMusic(gestor));
  gpointer key1, value1;
  GList *listaResposta = NULL; // Lista para armazenar a resposta
  char *artistId = NULL;
  int l = 0;
  int duracao = 0;

  // Percorre todas as músicas na hashtable das músicas
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Musics *music = (Musics *)value1;   // Obtém a música atual
    artistId = getMusicArtistId(music); // Obtém o identificador do artista da
                                        // música Armazena o ID do artista
    remove_quotes(artistId);            // Remove aspas do ID do artista
    removeFstLast(artistId); // Remove o primeiro e o último caractere do ID

    // Obtém a duração da música
    duracao = getMusicDuration(music);

    gpointer value;
    gpointer orig_key;
    l = strlen(artistId); // Tamanho do ID do artista

    // Percorre os ID's dos artistas
    for (int j = 0; j < l; j += 12) {
      char *key;
      if (j == 0)
        artistId = artistId + 1; // Ajusta o pointer
      else
        artistId =
            artistId +
            3; // Ajusta o ponteiro para também passar à frente o espaço e o ;
      key = strdup(
          strsep(&artistId, "'")); // Extrai o ID do artista entre as aspas

      // Procura o artista na hashtable dos artistas
      if (g_hash_table_lookup_extended(
              getArtistTable(pegarGestorArtist(gestor)), key, &orig_key,
              &value)) {
        // Se o artista for encontrado, incrementa a sua discografia
        increment_artist_discografia(value, duracao, &listaResposta,
                                     numeroArtistas, country);
      }
      free(key); // Liberta a key
    }
  }

  // Imprime a resposta da consulta no arquivo
  printQuery2(&listaResposta, newFile);

  // coloca a tabela de artistas a zero
  colocaZero(getArtistTable(pegarGestorArtist(gestor)));

  // Liberta a memória alocada para a lista de respostas
  g_list_free(listaResposta);
}
