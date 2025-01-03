#include "query5.h"
#include "gestor_history.h"
#include "gestores.h"
#include "inputResult.h"
#include "recomendador.h"
#include "utils.h"
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

argumentosQuery5 *initArgumentosQuery5() {
  argumentosQuery5 *a = malloc(sizeof(struct argumentosQuery5));

  return a;
}

void alocaMatriz(Gestores *gestor, argumentosQuery5 *a) {
  a->numGeneros = getMusicsNGenres(pegarGestorMusic(gestor));
  a->numUtilizadores = getNUsers(pegarGestorUser(gestor));
  int **matrizClassificacaoMusicas;
  matrizClassificacaoMusicas = malloc(a->numUtilizadores * sizeof(int *));
  if (!matrizClassificacaoMusicas) {
    printf("Erro ao alocar memória para as linhas da matriz!\n");
    return;
  }

  // Alocar memória para as colunas de cada linha
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

  gestorMusics *gestorMusics = pegarGestorMusic(gestor);
  char **nomesGeneros = insertGenreToArray(gestorMusics, a->numGeneros);
  char **idsUtilizadores = malloc(sizeof(char *) * a->numUtilizadores);
  a->nomesGeneros = nomesGeneros;
  a->idsUtilizadores = idsUtilizadores;
}

void constroiQuery5(Gestores *gestor, argumentosQuery5 *a) {
  gestorUsers *gestorUsers = pegarGestorUser(gestor);

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

void query5(Gestores *gestor, int numRecomendacoes, char *idUtilizadorAlvo,
            int i, argumentosQuery5 *a) {
  FILE *newFile = createFile(i);

  gpointer value;
  gpointer orig_key;
  // Caso não esteja na HT dos users, é inválido e por isso não faz nada
  if (!lookUpUsersHashTable(pegarGestorUser(gestor), idUtilizadorAlvo,
                            &orig_key, &value) ||
      numRecomendacoes == 0) {
    fprintf(newFile, "\n");
    fclose(newFile);
    return;
  }

  char **recomendacao = recomendaUtilizadores(
      idUtilizadorAlvo, a->matrizClassificacaoMusicas, a->idsUtilizadores,
      a->nomesGeneros, a->numUtilizadores, a->numGeneros, numRecomendacoes);
  for (int i = 0; i < numRecomendacoes; i++) {
    fprintf(newFile, "%s\n", recomendacao[i]);
  }
  fclose(newFile);
  free(recomendacao);
}
