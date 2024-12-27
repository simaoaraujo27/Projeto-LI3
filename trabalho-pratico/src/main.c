#include "gestorParsers.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
#include "gestor_users.h"
#include "gestores.h"
#include "nodo_musica.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
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
  double total_time_query1 = 0, total_time_query2 = 0, total_time_query3 = 0;

  clock_t start, end;

  // Verifica se foram passados argumentos suficientes (path + nome do
  // arquivo de texto)
  if (argc < 3) {
    fprintf(stderr, "Error: Missing filename\n");
    return EXIT_FAILURE;
  }

  // Armazena o path base passado como argumento
  char *path = argv[1];
  int flag = 0;

  Gestores *gestor = initgestor(&flag);

  if (flag == 1 || !GestorParsers(gestor, path)) {
    fprintf(stderr, "Failed to initialize Gestor\n");
    destroyGestor(gestor);
    return EXIT_FAILURE;
  }


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
  NodoMusica *lista =
      NULL; // Lista de músicas baseadas nas preferências dos users

  start = clock();
  lista = CriaListaRespostaQuery3(lista, gestor);
  end = clock();

  total_time_query3 += (double)(end - start) / CLOCKS_PER_SEC;

  // Processa as queries lidas do arquivo
  while (getline(&line, &len, fp) != -1) {
    gestorQueries(line, gestor, lista, i, &total_time_query1,
                  &total_time_query2, &total_time_query3);
    i++;
  }
  fclose(fp);
  free(line);

  // Liberta toda a memória alocada e destrói as hashtables
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
