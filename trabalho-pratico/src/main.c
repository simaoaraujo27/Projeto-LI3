#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queires.h"
#include "gestor_users.h"
#include "gestores.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define o tamanho máximo para os caminhos dos arquivos
#define MAX_PATH_SIZE 1024

int main(int argc, char **argv) {
  FILE *fp = NULL;

  // Verifica se foram passados argumentos suficientes (caminho + nome do
  // arquivo de texto)
  if (argc < 3) {
    fp = stdin;
    fprintf(stderr, "Error: Missing filename\n");
    return EXIT_FAILURE;
  }

  // Armazena o caminho base passado como argumento
  char *path = argv[1];

  // Aloca memória para os caminhos completos dos arquivos
  char *artistsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *musicsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *usersPath = malloc(MAX_PATH_SIZE * sizeof(char));

  // Constroi os caminhos completos para os arquivos CSV
  snprintf(artistsPath, MAX_PATH_SIZE, "%s/%s", path, "artists.csv");
  snprintf(musicsPath, MAX_PATH_SIZE, "%s/%s", path, "musics.csv");
  snprintf(usersPath, MAX_PATH_SIZE, "%s/%s", path, "users.csv");

  // Inicializa a tabela de hash para os artistas
  GHashTable *artistsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyArtist);

  // Inicializa o gestor de artistas com o arquivo de erros
  gestorArtists *gestorArtists =
      initGestorArtists("./resultados/artists_errors.csv", artistsTable);

  // Verifica se o gestor de artistas foi inicializado corretamente
  if (!gestorArtists) {
    fprintf(stderr, "Failed to initialize gestorArtists\n");
    return EXIT_FAILURE;
  }

  // Abre o arquivo de artistas e carrega os dados
  fp = fopen(artistsPath, "r");
  if (fp) {
    parseArtists(fp, gestorArtists); // Faz o parsing dos dados dos artistas
    fclose(fp);
  } else {
    perror("Error opening artists file");
    freeGestorArtists(gestorArtists);
    return EXIT_FAILURE;
  }
  free(artistsPath); // Libera a memoria do caminho dos artistas

  // Inicializa a tabela de hash para musicas
  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);

  // Inicializa o gestor de músicas
  gestorMusics *gestorMusics =
      initGestorMusics("./resultados/musics_errors.csv", musicsTable);

  // Verifica se o gestor de musicas foi inicializado corretamente
  if (!gestorMusics) {
    fprintf(stderr, "Failed to initialize gestorMusics\n");
    return EXIT_FAILURE;
  }

  // Abre o arquivo de musicas e carrega os dados
  fp = fopen(musicsPath, "r");
  if (fp) {
    parseMusics(fp, gestorMusics, gestorArtists); // Faz o parsing das musicas
    fclose(fp);
  } else {
    perror("Error opening musics file");
    freeGestorMusics(gestorMusics);
    return EXIT_FAILURE;
  }
  free(musicsPath); // Libera a memória do caminho das musicas

  // Inicializa a tabela de hash para users
  GHashTable *usersTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyUser);

  // Inicializa o gestor de users
  gestorUsers *gestorUsers =
      initGestorUsers("./resultados/users_errors.csv", usersTable);

  // Verifica se o gestor de users foi inicializado corretamente
  if (!gestorUsers) {
    fprintf(stderr, "Failed to initialize gestorUsers\n");
    return EXIT_FAILURE;
  }

  // Abre o arquivo de users e carrega os dados
  fp = fopen(usersPath, "r");
  if (fp) {
    parseUsers(fp, gestorUsers, gestorMusics); // Faz o parsing dos users
    fclose(fp);
  } else {
    perror("Error opening users file");
    freeGestorUsers(gestorUsers);
    return EXIT_FAILURE;
  }
  free(usersPath); // Libera a memória do caminho dos users

  Gestores *gestor = initgestor(gestorArtists, gestorMusics, gestorUsers);

  // Abre o arquivo de texto passado como argumento para executar as queries
  char *txt = argv[2];
  fp = fopen(txt, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  size_t len = 0;
  int i = 1; // Contador para o número da query
  int firstOcorr = 0, minAge = 0, maxAge = 0;
  int IDADE_INICIAL = 120;
  NodoMusica *lista =
      NULL; // Lista de músicas baseadas nas preferências dos users
  guint idade_max = IDADE_INICIAL; // Inicializa a idade máxima

  lista = CriaListaRespostaQuery3(lista, idade_max, gestor);

  // Processa as queries lidas do arquivo
  while (getline(&line, &len, fp) != -1) {
    gestorQueries(line, gestor, firstOcorr,
                  maxAge, minAge, lista, i);
    i++;
  }
  fclose(fp);
  free(line);

  // Libera toda a memória alocada e destrói as tabelas de hash
  g_hash_table_destroy(musicsTable);
  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);
  liberar_lista(lista);
  freeGestorArtists(gestorArtists);
  freeGestorMusics(gestorMusics);
  freeGestorUsers(gestorUsers);
  destroyGestor(gestor);
  return 0;
}
