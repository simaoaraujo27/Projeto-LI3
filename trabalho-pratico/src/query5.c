#include "gestor_history.h"
#include "gestores.h"
#include "recomendador.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void query5(Gestores *gestor) {
  gestorUsers *gestorUsers = pegarGestorUser(gestor);
  gestorMusics *gestorMusics = pegarGestorMusic(gestor);
  gestorHistory *gestorHistory = pegarGestorHistory(gestor);
  if (gestorHistory != NULL) {
  }

  char *idUtilizadorAlvo = "U0164904";
  if (idUtilizadorAlvo) {
  }

  int numUtilizadores = getNUsers(gestorUsers);
  if (numUtilizadores) {
  }
  int numGeneros = getMusicsNGenres(gestorMusics);
  if (numGeneros) {
  }

  char **nomesGeneros = insertGenreToArray(gestorMusics, numGeneros);
  if (nomesGeneros) {
  }

  char **idsUtilizadores = insertIdsToArray(gestorUsers, numUtilizadores);
  if (idsUtilizadores) {
  }

  // for (int i = 0; i < numUtilizadores; i++) {
  //   printf("%s\n", idsUtilizadores[i]);
  // }

  int numRecomendacoes = 7;
  if (numRecomendacoes) {
  }
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

  /*   printf("numUtilizadores: %d\n", numUtilizadores);
    printf("numGeneros: %d\n", numGeneros);
    for (int i = 0; i < numUtilizadores; i++) {
      printf("%s\n", idsUtilizadores[i]);
    }
    for (int i = 0; i < numGeneros; i++) {
      printf("%s\n", nomesGeneros[i]);
    } */

  for (int i = 0; i < numUtilizadores; i++) {
    for (int j = 0; j < numGeneros; j++) {
      matrizClassificacaoMusicas[i][j] = 0;
    }
  }
  printf("faz isto!\n");
  // printf("Num utilizadores: %d\n", numUtilizadores);
  preencheMatriz(matrizClassificacaoMusicas, numUtilizadores, numGeneros,
                 idsUtilizadores, nomesGeneros, gestorMusics, gestorHistory,
                 gestorUsers);

  /*   for (int i = 0; i < numUtilizadores; i++) {
      for (int j = 0; j < numGeneros; j++) {
        printf("%d\n", matrizClassificacaoMusicas[i][i]);
      }
    } */
  /*  */

  char **recomendacao = recomendaUtilizadores(
      idUtilizadorAlvo, matrizClassificacaoMusicas, idsUtilizadores,
      nomesGeneros, numUtilizadores, numGeneros, numRecomendacoes);
  if (recomendacao != NULL) {
  }
  for (int i = 0; i < numRecomendacoes; i++) {
    printf("REC: %s\n", recomendacao[i]);
  }

  // numRecomendacoes e idUtilizadorAlvo vêm do txt!
}

/*
OUTPUT ESPERADO:
U0080869
U0104287
U0145818
U0046251
U0050690
U0059152
U0075286

*/

/*
O parseUsers tem de vir antes do parseHistory

À medida que fazemos o parseUsers colocamos o seguinte na struct:
  um counter (nUsers) que nos vai indicar quantos users existem;

À medida que fazemos o parseMusics colocamos o seguinte na struct:
  uma HashTable ht que vai ter os nomes do género de música

Criamos a matriz (chamemos de mat): mat[nUsers][length(ht)]
E colocamos todas as posições a 0

Depois à medida que fazemos o parseHistory:
  Vemos qual é o género da música através do getMusicGenre;
  Vemos em que índice esse género está no arr (index);
  Fazemos mat[removeZerosAEsqerda(user_id)][index];
*/