#include "gestor_queries.h"
#include "query1.h"
#include "query2.h"
#include "query4.h"
#include "query5.h"
#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gestorQueries(char *line, Gestores *gestor, NodoMusica *lista, int i,
                   double *total_time_query1, double *total_time_query2,
                   double *total_time_query3) {
  clock_t start, end;
  double time_spent;
  int firstOcorr = 0, maxAge = 0, minAge = 0;
  int temS = 0;
  if (line[1] == 'S')
    temS = 1;

  if (line[0] == '1') {
    start = clock();
    if ((temS && (line[3] == 'U')) || (!temS && (line[2] == 'U'))) {
      query1User(pegarGestorUser(gestor), line, i, temS);
    } else
      query1Artist(pegarGestorArtist(gestor), line, i, temS);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    *total_time_query1 += time_spent; // Acumula o tempo para Query 1
  } else if (line[0] == '2') {
    start = clock();
    if (!temAspas(line)) {
      if (!temS) {
        query2(atoi(line + 2), NULL, gestor, i, temS);
      } else {
        query2(atoi(line + 3), NULL, gestor, i, temS);
      }
    } else {
      firstOcorr = primeiraOcorr(line, '"');
      if (!temS) {
        query2(atoi(line + 2), line + firstOcorr, gestor, i, temS);
      } else {
        query2(atoi(line + 3), line + firstOcorr, gestor, i, temS);
      }
    }
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    *total_time_query2 += time_spent; // Acumula o tempo para Query 2
  } else if (line[0] == '3') {
    start = clock();
    if (!temS) {
      minAge = atoi(line + 2);
      firstOcorr = primeiraOcorr(line + 2, ' ');
      maxAge = atoi(line + 2 + firstOcorr);
    } else {
      minAge = atoi(line + 3);
      firstOcorr = primeiraOcorr(line + 3, ' ');
      maxAge = atoi(line + 3 + firstOcorr);
    }
    query3(minAge, maxAge, lista, i, temS);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    *total_time_query3 += time_spent; // Acumula o tempo para Query 3
  } else if (line[0] == '4') {
    if ((temS && line[2] == ' ') || (!temS && line[1] == ' ')) {
      line += 2;
      if (temS)
        line++;
      char *fim = line + 11;
      fim[10] = '\0';
      line[10] = '\0';
      query4(pegarGestorArtist(gestor), line, fim, i, temS);
    } else
      query4(pegarGestorArtist(gestor), NULL, NULL, i, temS);
  } else if (line[0] == '5') {
    // query5(gestor);
  }
}
