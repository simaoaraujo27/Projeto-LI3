#include "queries.h"
#include "users.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *adicionarAspas(const char *str) {
  // Calcula o tamanho da nova string
  size_t tamanhoOriginal = strlen(str);
  size_t tamanhoNovo =
      tamanhoOriginal + 3; // 2 para as aspas e 1 para o terminador nulo

  char *novaStr = (char *)malloc(tamanhoNovo * sizeof(char));
  if (novaStr == NULL) {
    fprintf(stderr, "Erro ao alocar memória\n");
    return NULL;
  }

  sprintf(novaStr, "\"%s\"", str);

  return novaStr;
}

void query1(GHashTable *usersTable, char *line) {
  line = line + 2;
  line[strlen(line) - 1] = '\0';
//   line = adicionarAspas(line);

  gpointer value;
  gpointer orig_key;

  gboolean found =
      g_hash_table_lookup_extended(usersTable, line, &value, &orig_key);

  if (found) {

    char *email = getUserEmail(orig_key);
    char *firstName = getUserFirstName(orig_key);
    char *lastName = getUserLastName(orig_key);
    char *age = getUserBirthDate(orig_key);
    char *country = getUserCountry(orig_key);

    int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                    strlen(age) + strlen(country) + 5; // 5 para os ';' e o '\0'
    char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    // Concatenar as strings, separando-as por ;
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
             lastName, age, country);

    printf("%s", new_str);

    free(email);
    free(firstName);
    free(lastName);
    free(age);
    free(country);
  } else {
    printf("NOT FOUND!\n");
  }

}

void query2() { return; }

void query3() { return; }
