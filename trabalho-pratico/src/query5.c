#include "query5.h"
#include "argumentos_query5.h"
#include "gestor_history.h"
#include "gestores.h"
#include "inputResult.h"
#include "recomendador.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void query5(Gestores *gestor, int numRecomendacoes, char *idUtilizadorAlvo,
            int i, argumentosQuery5 *a) {
  FILE *newFile = createFile(i);

  gpointer value;
  gpointer orig_key;

  if (!lookUpUsersHashTable(getGestorUser(gestor), idUtilizadorAlvo, &orig_key,
                            &value) ||
      numRecomendacoes == 0) {
    fprintf(newFile, "\n");
    fclose(newFile);
    return;
  }

  char **recomendacao = recomendaUtilizadores(
      idUtilizadorAlvo, getArgumentosQuery5MatrizClassificacaoMusicas(a),
      getArgumentosQuery5IdsUtilizadores(a), getArgumentosQuery5NomesGeneros(a),
      getArgumentosQuery5NumUtilizadores(a), getArgumentosQuery5NumGeneros(a),
      numRecomendacoes);
  for (int i = 0; i < numRecomendacoes; i++) {
    fprintf(newFile, "%s\n", recomendacao[i]);
  }
  fclose(newFile);
  free(recomendacao);
}
