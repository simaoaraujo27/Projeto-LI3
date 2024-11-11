#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
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
#include <sys/resource.h>

// Define o tamanho máximo para os paths dos arquivos
#define MAX_PATH_SIZE 1024

int main(int argc, char **argv) {
  FILE *fp = NULL;

  // Variáveis para calcular o tempo total de duração de cada query
  double total_time_query1 = 0;
  double total_time_query2 = 0;
  double total_time_query3 = 0;

  clock_t start, end;

  // Verifica se foram passados argumentos suficientes (path + nome do
  // arquivo de texto)
  if (argc < 3) {
    fp = stdin;
    fprintf(stderr, "Error: Missing filename\n");
    return EXIT_FAILURE;
  }

  // Armazena o path base passado como argumento
  char *path = argv[1];

  // Aloca memória para os paths completos dos arquivos
  char *artistsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *musicsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *usersPath = malloc(MAX_PATH_SIZE * sizeof(char));

  // Constroi os paths completos para os arquivos CSV
  snprintf(artistsPath, MAX_PATH_SIZE, "%s/%s", path, "artists.csv");
  snprintf(musicsPath, MAX_PATH_SIZE, "%s/%s", path, "musics.csv");
  snprintf(usersPath, MAX_PATH_SIZE, "%s/%s", path, "users.csv");

  // Inicializa a hashtable para os artistas
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
  free(artistsPath); // Liberta a memoria do path dos artistas

  // Inicializa a hashtable para musicas
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
  free(musicsPath); // Liberta a memória do path das musicas

  // Inicializa a hashtable para users
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
  free(usersPath); // Liberta a memória do path dos users

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

  start = clock();
  lista = CriaListaRespostaQuery3(lista, idade_max, gestor);
  end = clock();

  total_time_query3 += (double)(end - start) / CLOCKS_PER_SEC;

  // Processa as queries lidas do arquivo
  while (getline(&line, &len, fp) != -1) {
    gestorQueries(line, gestor, firstOcorr, maxAge, minAge, lista, i,
                  &total_time_query1, &total_time_query2, &total_time_query3);
    i++;
  }
  fclose(fp);
  free(line);

  // Liberta toda a memória alocada e destrói as hashtables
  g_hash_table_destroy(musicsTable);
  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);
  liberar_lista(lista);
  destroyGestor(gestor);

  // Medir o uso de memória no final da execução
  // Verifica se o programa foi chamado com RAM_MONITOR
  if (getenv("RAM_MONITOR") != NULL) {
    // Medir o uso de memória no final da execução
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória utilizada: %ld KB\n", r_usage.ru_maxrss);

    printf("Tempos de execução: \n");
    printf("Q1: %fs\n", total_time_query1);
    printf("Q2: %fs\n", total_time_query2);
    printf("Q3: %fs\n", total_time_query3);
  }
  return 0;
}
