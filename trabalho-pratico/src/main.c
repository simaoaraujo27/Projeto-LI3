#include "compare_files.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
#include "gestor_users.h"
#include "gestores.h"
#include "nodo_musica.h"
#include "parser.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "top10Query4.h"
#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#define MAX_PATH_SIZE 1024

int main(int argc, char **argv) {
  temposTestes *t = initTemposTestes();
  argumentosQuery5 *a = initArgumentosQuery5();
  FILE *fp = NULL;

  if (argc < 3) {
    fprintf(stderr, "Error: Missing filename\n");
    return EXIT_FAILURE;
  }

  char *path = argv[1];
  int flag = 0;

  char *txt = argv[2];
  fp = fopen(txt, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  }

  Gestores *gestor = initgestor(&flag);

  if (flag == 1 || !GestorParsers(gestor, path, fp)) {
    fprintf(stderr, "Failed to initialize Gestor\n");
    destroyGestor(gestor);
    return EXIT_FAILURE;
  }
  fclose(fp);

  char *line = NULL;
  size_t len = 0;
  int i = 1;
  NodoMusica *lista = NULL;

  lista = CriaListaRespostaQuery3(lista, gestor);
  alocaMatriz(gestor, a);
  constroiQuery5(gestor, a);

  fp = fopen(txt, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  }

  while (getline(&line, &len, fp) != -1) {
    gestorQueries(line, gestor, lista, a, i, t);
    i++;
  }
  fclose(fp);
  free(line);

  if (getenv("RAM_MONITOR") != NULL) {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memória utilizada: %ld KB\n", r_usage.ru_maxrss);

    printf("Tempos de execução: \n");
    printf("Q1: %fs\n", getTemposTestes(t, 1));
    printf("Q2: %fs\n", getTemposTestes(t, 2));
    printf("Q3: %fs\n", getTemposTestes(t, 3));
    printf("Q4: %fs\n", getTemposTestes(t, 4));
    printf("Q5: %fs\n", getTemposTestes(t, 5));
    printf("Q6: %fs\n", getTemposTestes(t, 6));
  }

  liberar_lista(lista);
  destroiArgumentosQuery5(a);
  destroyGestor(gestor);
  destroyTemposTestes(t);
  return 0;
}
