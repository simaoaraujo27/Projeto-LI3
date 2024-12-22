#include "gestor_users.h"
#include "gestor_artists.h"
#include "inputResult.h"
#include "users.h"
#include "artists.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outputResult.h"

// Função para imprimir os dados de um user
void MakeQuery1User(gpointer orig_key, FILE *newFile, int temS) {
  // Obtém os dados do user usando os getters
  char *email = getUserEmail(orig_key);
  char *firstName = getUserFirstName(orig_key);
  char *lastName = getUserLastName(orig_key);
  char *birth_date = getUserBirthDate(orig_key);
  char *age = calculate_age_str(birth_date);
  char *country = getUserCountry(orig_key);
  // Calcula o tamanho total da string a ser concatenada, incluindo
  // delimitadores
  int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                  strlen(age) + strlen(country) + 5; // 5 para os ';' ou '=' e o '\0'
  char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'

  if (temS){
    // Formata a string concatenada com os dados do user, separando-os por '='
  snprintf(new_str, total_len + 1, "%s=%s=%s=%s=%s\n", email, firstName,
           lastName, age, country);
  }
  else{
  // Formata a string concatenada com os dados do user, separando-os por ';'
  snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
           lastName, age, country);
  }
  writeFile(newFile, new_str);

  // Liberta a memória alocada para as strings
  free(email);
  free(firstName);
  free(lastName);
  free(birth_date);
  free(age);
  free(country);
  free(new_str);
}

// Função que executa a consulta 1
void query1User(gestorUsers *gestorUser, char *line, int i, int temS) {
  // Remove os dois primeiros caracteres da linha
  line = line + 2;
  if (temS) line++;
  line[strlen(line) - 1] = '\0'; // Remove o caractere de nova linha no final
  FILE *newFile = createFile(i);

  gpointer value;
  gpointer orig_key;

  gboolean found = lookUpUsersHashTable(gestorUser, line, &value, &orig_key);
  // Se o user for encontrado, imprime os seus dados no arquivo
  if (found) {
    MakeQuery1User(orig_key, newFile, temS);
  } else {
    writeFile(newFile, "\n");
  }
}

// Função para imprimir os dados de um artist
void MakeQuery1Artist(gpointer orig_key, FILE *newFile, int temS) {
  // Obtém os dados do user usando os getters
  char *name = getArtistName(orig_key);
  //printf("a\n");
  char *type = getArtistTypeStr(orig_key);
  char *country = getArtistCountry(orig_key);
  int num_albuns_individual = getArtistNumAlbunsIndividual(orig_key);
  char *num_albuns_individual_str = intToString(num_albuns_individual);
  //char *total_recipe = "1000";
  // Calcula o tamanho total da string a ser concatenada, incluindo
  // delimitadores
  int total_len = strlen(name) + strlen(type) + strlen(country) + strlen(num_albuns_individual_str) +
                  4; // 5 para os ';' ou '=' e o '\0'
  char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'

  if (temS){
    // Formata a string concatenada com os dados do user, separando-os por '='
  snprintf(new_str, total_len + 1, "%s=%s=%s=%s\n", name, type, country, num_albuns_individual_str);
  }
  else{
  // Formata a string concatenada com os dados do user, separando-os por ';'
  snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type, country, num_albuns_individual_str);
  }
  writeFile(newFile, new_str);

  // Liberta a memória alocada para as strings
  free(name);
  //free(type);
  free(country);
  free(num_albuns_individual_str);
  free(new_str);
}

void query1Artist(gestorArtists *gestorArtist, char *line, int i, int temS) {
   line = line + 2;
   if (temS) line++;
  line[strlen(line) - 1] = '\0'; // Remove o caractere de nova linha no final
  FILE *newFile = createFile(i);
  gpointer value;
  gpointer orig_key;

  gboolean found = lookUpArtistsHashTable(gestorArtist, line, &value, &orig_key);

  // Se o user for encontrado, imprime os seus dados no arquivo
  if (found) {
    //MakeQuery1Artist(orig_key, newFile, temS);
  } else {
    writeFile(newFile, "\n");
  }
}

