#include "gestor_artists.h"
#include "musics.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeFile(FILE *newFile, char *text) {
  fprintf(newFile, "%s", text);

  fclose(newFile);
}

char *SegundosParaHoras(int segundos) {
  int horas = segundos / 3600;
  int minutos = (segundos % 3600) / 60;
  int segundosRestantes = segundos % 60;
  char *hora = malloc(20 * sizeof(char));
  snprintf(hora, 20, "%02d:%02d:%02d", horas, minutos, segundosRestantes);
  return hora;
}

void printQuery2(GList *listaResposta, FILE *newFile, int numeroArtists,
                 int temS, char *country1) {
  GList *node = listaResposta;
  int contadorDeNodes = 0;
  if (country1 == NULL) {
    while (node != NULL && contadorDeNodes < numeroArtists) {
      char *name;
      char *type;
      char *discografia;
      char *country;
      char *new_str;

      Artists *currentArtist = (Artists *)node->data;

      name = getArtistName(currentArtist);
      type = getArtistTypeStr(currentArtist);
      discografia = SegundosParaHoras(getArtistDiscografia(currentArtist));
      country = getArtistCountry(currentArtist);
      int total_len = strlen(name) + strlen(type) + 4 + strlen(country) + 4;
      new_str = malloc((total_len + 1) * sizeof(char));

      remove_quotes(name);
      remove_quotes(country);
      if (temS) {
        snprintf(new_str, total_len + 1, "%s=%s=%s=%s\n", name, type,
                 discografia, country);
      } else {
        snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type,
                 discografia, country);
      }
      fprintf(newFile, "%s", new_str);
      node = node->next;
      contadorDeNodes++;
      free(name);
      free(type);
      free(discografia);
      free(country);
      free(new_str);
    }
  } else {
    removeLast(country1);
    while (node != NULL && contadorDeNodes < numeroArtists) {
      char *name;
      char *type;
      char *discografia;
      char *country;
      char *new_str;

      Artists *currentArtist = (Artists *)node->data;
      country = getArtistCountry(currentArtist);
      if (strcmp(country1, country) != 0) {
        node = node->next;
        free(country);
      } else {
        name = getArtistName(currentArtist);
        type = getArtistTypeStr(currentArtist);
        discografia = SegundosParaHoras(getArtistDiscografia(currentArtist));

        int total_len = strlen(name) + strlen(type) + 4 + strlen(country) + 4;

        new_str = malloc((total_len + 1) * sizeof(char));

        remove_quotes(name);
        remove_quotes(country);
        if (temS) {
          snprintf(new_str, total_len + 1, "%s=%s=%s=%s\n", name, type,
                   discografia, country);
        } else {
          snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type,
                   discografia, country);
        }
        fprintf(newFile, "%s", new_str);
        node = node->next;

        contadorDeNodes++;
        free(name);
        free(type);
        free(discografia);
        free(country);
        free(new_str);
      }
    }
  }
  if (contadorDeNodes == 0) {
    fprintf(newFile, "\n");
  }
  fclose(newFile);
}

void printQuery4(FILE *newFile, int temS, char *name, char *type,
                 int countTop10) {
  char *contarTop10 = intToString(countTop10);
  int total_len = strlen(name) + strlen(type) + 6;
  char *new_str = malloc((total_len + 1) * sizeof(char));
  if (temS) {
    snprintf(new_str, total_len + 1, "%s=%s=%s\n", name, type, contarTop10);
  } else {
    snprintf(new_str, total_len + 1, "%s;%s;%s\n", name, type, contarTop10);
  }
  fprintf(newFile, "%s", new_str);

  free(contarTop10);
  free(new_str);

  fclose(newFile);
}

void printQuery5(FILE *newFile, char **recomendacao, int numRecomendacoes) {
  for (int i = 0; i < numRecomendacoes; i++) {
    fprintf(newFile, "%s\n", recomendacao[i]);
  }

  fclose(newFile);
}

void MakeQuery1User(gpointer orig_key, FILE *newFile, int temS) {
  char *email = getUserEmail(orig_key);
  char *firstName = getUserFirstName(orig_key);
  char *lastName = getUserLastName(orig_key);
  char *birth_date = getUserBirthDate(orig_key);
  char *age = calculate_age_str(birth_date);
  char *country = getUserCountry(orig_key);

  int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                  strlen(age) + strlen(country) + 5;
  char *new_str = malloc((total_len + 1) * sizeof(char));

  if (temS) {
    snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s\n", email, firstName,
             lastName, age, country);
  } else {
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
             lastName, age, country);
  }
  writeFile(newFile, new_str);

  free(email);
  free(firstName);
  free(lastName);
  free(birth_date);
  free(age);
  free(country);
  free(new_str);
}

void floatParaString(float numero, char **buffer) {
  *buffer = (char *)malloc(20 * sizeof(char));
  if (*buffer == NULL) {
    printf("Erro ao alocar memória!\n");
    return;
  }
  snprintf(*buffer, 20, "%.2f", numero);
}

void MakeQuery1Artist(gpointer orig_key, FILE *newFile, int temS) {
  char *name = getArtistName(orig_key);
  remove_quotes(name);
  char *type = getArtistTypeStr(orig_key);
  char *country = getArtistCountry(orig_key);
  remove_quotes(country);
  int num_albuns_individual = getArtistNumAlbunsIndividual(orig_key);
  char *num_albuns_individual_str = intToString(num_albuns_individual);

  float receitaTotal = getArtistReceitaTotal(orig_key);

  char *receitaTotalStr;
  floatParaString(receitaTotal, &receitaTotalStr);

  int total_len = strlen(name) + strlen(type) + strlen(country) +
                  strlen(num_albuns_individual_str) + strlen(receitaTotalStr) +
                  5;
  char *new_str = malloc((total_len + 1) * sizeof(char));

  if (temS) {
    snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s\n", name, type, country,
             num_albuns_individual_str, receitaTotalStr);
  } else {
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", name, type, country,
             num_albuns_individual_str, receitaTotalStr);
  }
  writeFile(newFile, new_str);

  free(name);
  free(country);
  free(num_albuns_individual_str);
  free(new_str);
  free(receitaTotalStr);
}
