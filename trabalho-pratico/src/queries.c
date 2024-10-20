#include "queries.h"
#include "users.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *calculate_age(char *birth_date) {
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
      malloc(4 * sizeof(char)); // Idades razoáveis cabem em 3 dígitos + '\0'

  if (age_str == NULL) {
    return NULL; // Se a alocação falhar
  }

  snprintf(age_str, 4, "%d", age);

  return age_str;
}

void query1(GHashTable *usersTable, char *line, int i) {
  line = line + 2;
  line[strlen(line) - 1] = '\0';

  // Cria o ficheiro e guarda-o na pasta resultados
  FILE *newFile;
  char *path = "./resultados/commandx-output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d-output.txt", i);
  newFile = fopen(new, "w");
  gpointer value;
  gpointer orig_key;

  gboolean found =
      g_hash_table_lookup_extended(usersTable, line, &value, &orig_key);

  if (found) {
    char *email = getUserEmail(orig_key);
    char *firstName = getUserFirstName(orig_key);
    char *lastName = getUserLastName(orig_key);
    char *age = calculate_age(getUserBirthDate(orig_key));
    char *country = getUserCountry(orig_key);

    int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                    strlen(age) + strlen(country) + 5; // 5 para os ';' e o '\0'
    char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    // Concatenar as strings, separando-as por ;
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
             lastName, age, country);

    fprintf(newFile, "%s", new_str);
    fclose(newFile);

    free(email);
    free(firstName);
    free(lastName);
    free(age);
    free(country);
  }
}

void query2() { return; }

void query3() { return; }