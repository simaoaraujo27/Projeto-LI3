#include "gestor_queries.h"
#include "query1.h"
#include "query2.h"
#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gestorQueries(char *line, Gestores *gestor, int firstOcorr, int maxAge,
                   int minAge, NodoMusica *lista, int i) {
  if (line[0] == '1') {
    query1(pegarGestorUser(gestor), line, i);
  } else if (line[0] == '2') {
    if (!temAspas(line)) {
      query2(atoi(line + 2), NULL, gestor, i);

    } else {
      firstOcorr = primeiraOcorr(line, '"');
      query2(atoi(line + 2), line + firstOcorr, gestor, i);
    }
  } else if (line[0] == '3') {
    minAge = atoi(line + 2);
    firstOcorr = primeiraOcorr(line + 2, ' ');
    maxAge = atoi(line + 2 + firstOcorr);
    query3(minAge, maxAge, lista, i);
  }
}