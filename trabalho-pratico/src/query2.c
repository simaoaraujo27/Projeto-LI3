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
void processMusic(Musics *music, Gestores *gestor, int numeroArtistas,
                  char *country, GList **listaResposta) {
  char *orig =
      getMusicArtistId(music);   // Obtém o identificador do artista da música
  char *artistId = strdup(orig); // Faz uma cópia do ID do artista
  remove_quotes(artistId);       // Remove aspas do ID do artista
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
    gboolean found = lookUpArtistsHashTable(pegarGestorArtist(gestor), key,
                                            &value, &orig_key);
    if (found) {
      // Incrementa a discografia do artista
      increment_artist_discografia(value, duracao, listaResposta,
                                   numeroArtistas, country);
    }

    free(key); // Liberta a key
  }

  free(orig); // Liberta a string original
}

// Função principal que executa a query 2
void query2(int numeroArtistas, char *country, Gestores *gestor, int i) {
  FILE *newFile = createFile(i);

  // Iterador para percorrer a hashtable das músicas
  GHashTableIter iter;
  iter = iterInitMusicsHashTable(pegarGestorMusic(gestor));
  gpointer key1, value1;
  GList *listaResposta = NULL; // Lista para armazenar a resposta

  // Percorre todas as músicas na hashtable das músicas
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Musics *music = (Musics *)value1; // Obtém a música atual
    processMusic(music, gestor, numeroArtistas, country, &listaResposta);
  }

  // Imprime a resposta da consulta no arquivo
  printQuery2(&listaResposta, newFile);

  // Reseta os valores na tabela de artistas
  colocaZero(pegarGestorArtist(gestor));

  // Liberta a memória alocada para a lista de respostas
  g_list_free(listaResposta);
}