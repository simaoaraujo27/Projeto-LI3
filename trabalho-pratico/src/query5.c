#include "gestor_history.h"
#include "gestores.h"
#include "inputResult.h"
#include "recomendador.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void query5(Gestores *gestor, int numRecomendacoes, char *idUtilizadorAlvo, int i) {
  FILE *newFile = createFile(i);
  
  gpointer value;
  gpointer orig_key;
  // Caso não esteja na HT dos users, é inválido e por isso não faz nada
  if (!lookUpUsersHashTable(pegarGestorUser(gestor), idUtilizadorAlvo,
                            &orig_key, &value)) {
    fprintf(newFile, "\n");
    fclose(newFile);
    return;
  }

  gestorUsers *gestorUsers = pegarGestorUser(gestor);
  gestorMusics *gestorMusics = pegarGestorMusic(gestor);
  int numUtilizadores = getNUsers(gestorUsers);

  int numGeneros = getMusicsNGenres(gestorMusics);

  int **matrizClassificacaoMusicas;
  matrizClassificacaoMusicas = malloc(numUtilizadores * sizeof(int *));
  if (!matrizClassificacaoMusicas) {
    printf("Erro ao alocar memória para as linhas da matriz!\n");
    return;
  }

  // Alocar memória para as colunas de cada linha
  for (int i = 0; i < numUtilizadores; i++) {
    matrizClassificacaoMusicas[i] = malloc(numGeneros * sizeof(int));
    if (!matrizClassificacaoMusicas[i]) {
      printf("Erro ao alocar memória para as colunas da matriz!\n");
      for (int k = 0; k < i; k++) {
        free(matrizClassificacaoMusicas[k]);
      }
      free(matrizClassificacaoMusicas);
      return;
    }
  }

  for (int i = 0; i < numUtilizadores; i++) {
    for (int j = 0; j < numGeneros; j++) {
      matrizClassificacaoMusicas[i][j] = 0;
    }
  }

  char **nomesGeneros = insertGenreToArray(gestorMusics, numGeneros);
  char **idsUtilizadores = malloc(sizeof(char *) * numUtilizadores);

  preencheMatriz(matrizClassificacaoMusicas, numGeneros, nomesGeneros,
                 gestorUsers, idsUtilizadores);

  for (int i = 0; i < numGeneros; i++) {
    remove_quotes(nomesGeneros[i]);
  }

  char **recomendacao = recomendaUtilizadores(
      idUtilizadorAlvo, matrizClassificacaoMusicas, idsUtilizadores,
      nomesGeneros, numUtilizadores, numGeneros, numRecomendacoes);
  for (int i = 0; i < numRecomendacoes; i++) {
    fprintf(newFile, "%s\n", recomendacao[i]);
  }
  fclose(newFile);
}
