#include "argumentos_query5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct argumentosQuery5 {
  int numUtilizadores;
  int numGeneros;
  int **matrizClassificacaoMusicas;
  char **nomesGeneros;
  char **idsUtilizadores;
};

int getArgumentosQuery5NumUtilizadores(argumentosQuery5 *a) {
  return a->numUtilizadores;
}

int getArgumentosQuery5NumGeneros(argumentosQuery5 *a) { return a->numGeneros; }

int **getArgumentosQuery5MatrizClassificacaoMusicas(argumentosQuery5 *a) {
  return a->matrizClassificacaoMusicas;
}

char **getArgumentosQuery5NomesGeneros(argumentosQuery5 *a) {
  return a->nomesGeneros;
}

char **getArgumentosQuery5IdsUtilizadores(argumentosQuery5 *a) {
  return a->idsUtilizadores;
}

argumentosQuery5 *initArgumentosQuery5() {
  argumentosQuery5 *a = malloc(sizeof(struct argumentosQuery5));
  return a;
}

void alocaMatriz(Gestores *gestor, argumentosQuery5 *a) {
  a->numGeneros = getMusicsNGenres(getGestorMusic(gestor));
  a->numUtilizadores = getNUsers(getGestorUser(gestor));
  int **matrizClassificacaoMusicas;
  matrizClassificacaoMusicas = malloc(a->numUtilizadores * sizeof(int *));
  if (!matrizClassificacaoMusicas) {
    printf("Erro ao alocar memória para as linhas da matriz!\n");
    return;
  }

  for (int i = 0; i < a->numUtilizadores; i++) {
    matrizClassificacaoMusicas[i] = malloc(a->numGeneros * sizeof(int));
    if (!matrizClassificacaoMusicas[i]) {
      printf("Erro ao alocar memória para as colunas da matriz!\n");
      for (int k = 0; k < i; k++) {
        free(matrizClassificacaoMusicas[k]);
      }
      free(matrizClassificacaoMusicas);
      return;
    }
  }

  for (int i = 0; i < a->numUtilizadores; i++) {
    for (int j = 0; j < a->numGeneros; j++) {
      matrizClassificacaoMusicas[i][j] = 0;
    }
  }

  a->matrizClassificacaoMusicas = matrizClassificacaoMusicas;

  gestorMusics *gestorMusics = getGestorMusic(gestor);
  char **nomesGeneros = insertGenreToArray(gestorMusics, a->numGeneros);
  char **idsUtilizadores = malloc(sizeof(char *) * a->numUtilizadores);
  a->nomesGeneros = nomesGeneros;
  a->idsUtilizadores = idsUtilizadores;
}

void constroiQuery5(Gestores *gestor, argumentosQuery5 *a) {
  gestorUsers *gestorUsers = getGestorUser(gestor);

  preencheMatriz(a->matrizClassificacaoMusicas, a->numGeneros, a->nomesGeneros,
                 gestorUsers, a->idsUtilizadores);

  for (int i = 0; i < a->numGeneros; i++) {
    remove_quotes(a->nomesGeneros[i]);
  }
}

void destroiArgumentosQuery5(argumentosQuery5 *a) {
  for (int i = 0; i < a->numUtilizadores; i++) {
    free(a->matrizClassificacaoMusicas[i]);
    free(a->idsUtilizadores[i]);
  }
  for (int i = 0; i < a->numGeneros; i++) {
    free(a->nomesGeneros[i]);
  }
  free(a->matrizClassificacaoMusicas);
  free(a->idsUtilizadores);
  free(a->nomesGeneros);
  free(a);
}