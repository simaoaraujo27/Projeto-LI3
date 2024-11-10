#include "artists.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_prints.h"
#include "gestores.h"
#include "musics.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que executa a consulta 2
void query2(int numeroArtistas, char *country, Gestores *gestor, int i) {
  // Criação do arquivo para salvar os resultados
  FILE *newFile;
  char *path = "./resultados/commandx_output.txt"; // Caminho base para o
                                                   // arquivo de resultados
  char *new =
      malloc(sizeof(char) *
             (strlen(path) + 10)); // Aloca memória para o caminho completo
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt",
           i);               // Formata o nome do arquivo
  newFile = fopen(new, "w"); // Abre o arquivo para escrita

  // Iterador para percorrer a tabela de músicas
  GHashTableIter iter;
  g_hash_table_iter_init(
      &iter, getMusicsTable(pegarGestorMusic(
                 gestor))); // Inicializa o iterador da tabela de músicas
  gpointer key1, value1;
  GList *listaResposta = NULL; // Lista para armazenar a resposta
  char *artistId = NULL;
  int l = 0;
  int duracao = 0;

  // Percorre todas as músicas na tabela de músicas
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Musics *music = (Musics *)value1; // Obtém a música atual
    char *orig =
        getMusicArtistId(music); // Obtém o identificador do artista da música
    artistId = orig;             // Armazena o ID do artista
    remove_quotes(artistId);     // Remove aspas do ID do artista
    removeFstLast(artistId); // Remove o primeiro e o último caractere do ID
                             // (provavelmente para formatação)

    // Obtém a duração da música
    duracao = getMusicDuration(music);

    gpointer value;
    gpointer orig_key;
    l = strlen(artistId); // Tamanho do ID do artista

    // Percorre o ID do artista, dividindo-o em partes menores
    for (int j = 0; j < l;
         j += 12) { // O ID do artista parece estar em blocos de 12 caracteres
      char *key;
      if (j == 0)
        artistId =
            artistId + 1; // Ajusta o ponteiro para pular o primeiro caractere
      else
        artistId = artistId +
                   3; // Ajusta o ponteiro para pular os caracteres de separação
      key = strdup(
          strsep(&artistId, "'")); // Extrai o ID do artista entre as aspas

      // Procura o artista na tabela de artistas
      if (g_hash_table_lookup_extended(
              getArtistTable(pegarGestorArtist(gestor)), key, &orig_key,
              &value)) {
        // Se o artista for encontrado, incrementa a discografia do artista
        increment_artist_discografia(value, duracao, &listaResposta,
                                     numeroArtistas, country);
      }
      free(key); // Libera a memória alocada para o ID do artista
    }

    free(orig); // Libera a memória alocada para o ID original do artista
  }

  // Imprime a resposta da consulta no arquivo
  printQuery2(&listaResposta, newFile);

  // coloca a tabela de artistas a zero
  colocaZero(getArtistTable(pegarGestorArtist(gestor)));

  // Libera a memória alocada para a lista de respostas
  g_list_free(listaResposta);

  // Libera a memória alocada para o caminho do arquivo
  free(new);
}
