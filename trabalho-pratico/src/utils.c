#include "utils.h"
#include "artists.h"
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_quotes(char *str) {
  int len = strlen(str);

  if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
    for (int i = 0; i < len - 1; i++) {
      str[i] = str[i + 1]; // Puxa para a esquerda
    }
    str[len - 2] = '\0';
  }
}

int primeiraOcorr(char *line, char carac) {
  int i;
  for (i = 0; line[i]; i++) {
    if (line[i] == carac)
      return i;
  }
  return -1;
}

int temAspas(char *line) {
  for (int i = 0; line[i]; i++) {
    if (line[i] == '"') {
      return 1;
    }
  }
  return 0;
}

void removeFstLast(char *str) {
  int len = strlen(str);

  for (int i = 0; i < len - 1; i++) {
    str[i] = str[i + 1];
  }
  str[len - 2] = '\0';
}

void removeForLikedMusics(char *str) {
  int len = strlen(str);

  for (int i = 0; i < len - 1; i++) {
    str[i] = str[i + 2];
  }
  str[len - 5] = '\0';
}

// util para remover o enter no fim
void removeLast(char *str) {
  int len = strlen(str);

  str[len - 1] = '\0';
}

char *calculate_age_str(char *birth_date) {
  // Formato esperado da data de nascimento: "YYYY-MM-DD"
  int birth_year, birth_month, birth_day;

  sscanf(birth_date, "%d/%d/%d", &birth_year, &birth_month, &birth_day);

  // Data fixa: 2024/09/09
  int current_year = 2024;
  int current_month = 9;
  int current_day = 9;

  int age = current_year - birth_year;

  // Ajustar a idade se o aniversário ainda não tiver ocorrido em 2024
  if (current_month < birth_month ||
      (current_month == birth_month && current_day < birth_day)) {
    age--;
  }

  char *age_str =
      malloc(12 * sizeof(char)); // Idades razoáveis cabem em 3 dígitos + '\0'

  if (age_str == NULL) {
    return NULL; // Se a alocação falhar
  }

  snprintf(age_str, 12, "%d", age);

  return age_str;
}

int calculateAge(char *birth_date) {
  int year = atoi(birth_date);
  int month = atoi(birth_date + 6);
  int day = atoi(birth_date + 9);

  // Data fixa: 2024/09/09
  int age = 2024 - year;
  if (9 < month || (month == 9 && 9 < day)) {
    age--;
  }
  return age;
}

int comparaStrings(char *str1, char *str2) {
  if (strlen(str1) == strlen(str2) - 1) { // -1 por causa do \n fantasma
    int len = strlen(str1);
    for (int i = 0; i < len; i++) {
      if (str1[i] != str2[i]) {
        return 1;
      }
    }
  } else
    return 1;
  return 0;
}