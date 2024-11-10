#include "gestor_queries.h"
#include "gestor_users.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printQuery1(gpointer orig_key, FILE *newFile) {
  char *email = getUserEmail(orig_key);
  char *firstName = getUserFirstName(orig_key);
  char *lastName = getUserLastName(orig_key);
  char *birth_date = getUserBirthDate(orig_key);
  char *age = calculate_age_str(birth_date);
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
  free(birth_date);
  free(age);
  free(country);
  free(new_str);
}

void query1(gestorUsers *gestorUser, char *line, int i) {
  line = line + 2;
  line[strlen(line) - 1] = '\0';

  // Cria o ficheiro e guarda-o na pasta resultados
  FILE *newFile;
  char *path = "./resultados/commandx_output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt", i);
  newFile = fopen(new, "w");
  gpointer value;
  gpointer orig_key;

  gboolean found = g_hash_table_lookup_extended(getUsersTable(gestorUser), line,
                                                &value, &orig_key);

  if (found) {
    printQuery1(orig_key, newFile);
  } else {
    fprintf(newFile, "\n");
    fclose(newFile);
  }
  free(new);
}