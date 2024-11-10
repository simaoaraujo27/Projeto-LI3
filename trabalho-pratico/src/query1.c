#include "gestor_users.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para imprimir os dados de um user na consulta 1
void printQuery1(gpointer orig_key, FILE *newFile) {
  // Obtém os dados do user usando as funções de acesso
  char *email = getUserEmail(orig_key);
  char *firstName = getUserFirstName(orig_key);
  char *lastName = getUserLastName(orig_key);
  char *birth_date = getUserBirthDate(orig_key);
  char *age = calculate_age_str(birth_date);
  char *country = getUserCountry(orig_key);

  // Calcula o tamanho total da string a ser concatenada, incluindo
  // delimitadores
  int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                  strlen(age) + strlen(country) + 5; // 5 para os ';' e o '\0'
  char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'

  // Formata a string concatenada com os dados do user, separando-os por ';'
  snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
           lastName, age, country);

  // Escreve a string formatada no arquivo de saída
  fprintf(newFile, "%s", new_str);

  // Fecha o arquivo de saída
  fclose(newFile);

  // Libera a memória alocada para as strings
  free(email);
  free(firstName);
  free(lastName);
  free(birth_date);
  free(age);
  free(country);
  free(new_str);
}

// Função que executa a consulta 1
void query1(gestorUsers *gestorUser, char *line, int i) {
  // Remove os dois primeiros caracteres da linha
  line = line + 2;
  line[strlen(line) - 1] = '\0'; // Remove o caractere de nova linha no final

  // Cria o caminho para o arquivo de resultados na pasta "resultados"
  FILE *newFile;
  char *path = "./resultados/commandx_output.txt";
  char *new =
      malloc(sizeof(char) *
             (strlen(path) + 10)); // Aloca memória para o caminho do arquivo
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt",
           i);               // Formata o nome do arquivo
  newFile = fopen(new, "w"); // Abre o arquivo para escrita

  gpointer value;
  gpointer orig_key;

  // Tenta buscar o user na tabela hash usando a chave fornecida (line)
  gboolean found = g_hash_table_lookup_extended(getUsersTable(gestorUser), line,
                                                &value, &orig_key);

  // Se o user for encontrado, imprime seus dados no arquivo
  if (found) {
    printQuery1(orig_key, newFile);
  } else {
    // Se o user não for encontrado, escreve uma linha em branco
    fprintf(newFile, "\n");
    fclose(newFile); // Fecha o arquivo
  }

  // Libera a memória alocada para o caminho do arquivo
  free(new);
}
