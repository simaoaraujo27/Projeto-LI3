#include "utils.h"
#include "artists.h"
#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float arredondarParaSeisCasas(float numero) {
  return roundf(numero * 1000000) / 1000000;
}

void colocaTudoMinusculo(char *word) {
  for (int i = 0; i < (int)strlen(word); i++) {
    word[i] = tolower(word[i]);
  }
}

// Função para remover aspas (") no início e no final de uma string
void remove_quotes(char *str) {
  int len = strlen(str);

  // Verifica se a string tem pelo menos dois caracteres e começa e termina com
  // aspas
  if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
    // Desloca os caracteres da string para a esquerda
    for (int i = 0; i < len - 1; i++) {
      str[i] = str[i + 1];
    }
    str[len - 2] = '\0'; // Adiciona o \0 no final da string
  }
}

// Função para encontrar a primeira ocorrência de um caractere em uma string
int primeiraOcorr(char *line, char carac) {
  int i;
  // Percorre a string até encontrar o caractere ou chegar ao final
  for (i = 0; line[i]; i++) {
    if (line[i] == carac)
      return i; // Retorna o índice da primeira ocorrência
  }
  return -1; // Retorna -1 se o caractere não for encontrado
}

// Função para verificar se uma string contém aspas (")
int temAspas(char *line) {
  for (int i = 0; line[i]; i++) {
    if (line[i] == '"') {
      return 1; // Retorna 1 se houver aspas
    }
  }
  return 0; // Retorna 0 se não houver aspas
}

// Função para remover o primeiro e o último caractere de uma string
void removeFstLast(char *str) {
  int len = strlen(str);

  // Desloca os caracteres da string para a esquerda, removendo o primeiro
  for (int i = 0; i < len - 1; i++) {
    str[i] = str[i + 1];
  }
  str[len - 2] = '\0'; // Adiciona o \0, removendo o último caractere
}

// Função para remover o espaço e as aspas da string de "liked musics"
void removeForLikedMusics(char *str) {
  int len = strlen(str);

  // Desloca a string para a esquerda, removendo as aspas e o espaço
  for (int i = 0; i < len - 1; i++) {
    str[i] = str[i + 2];
  }
  str[len - 5] = '\0'; // Adiciona o \0 no final
}

// Função para remover o ultimo caractere de uma string
void removeLast(char *str) {
  int len = strlen(str);
  str[len - 1] = '\0';
}

// Função para calcular a idade de uma pessoa com base na data de nascimento
char *calculate_age_str(char *birth_date) {
  // Formato esperado da data de nascimento: "YYYY-MM-DD"
  int birth_year, birth_month, birth_day;

  // Faz o parsing da data de nascimento
  sscanf(birth_date, "%d/%d/%d", &birth_year, &birth_month, &birth_day);

  // Data atual fixa: 2024/09/09
  int current_year = 2024;
  int current_month = 9;
  int current_day = 9;

  int age = current_year - birth_year;

  // Ajusta a idade se o aniversário ainda não tiver ocorrido em 2024
  if (current_month < birth_month ||
      (current_month == birth_month && current_day < birth_day)) {
    age--; // Subtrai um ano caso ainda não tenha feito anos
  }

  // Aloca memória para armazenar a idade em string
  char *age_str =
      malloc(12 * sizeof(char)); // Capacidade suficiente para idades razoáveis

  if (age_str == NULL) {
    return NULL; // Se a alocação falhar, retorna NULL
  }

  // Converte a idade para string
  snprintf(age_str, 12, "%d", age);

  return age_str; // Retorna a idade como uma string
}

// Função para calcular a idade a partir da data de nascimento, retornando um
// inteiro
int calculateAge(char *birth_date) {
  int year = atoi(birth_date);      // Ano de nascimento
  int month = atoi(birth_date + 6); // Mês de nascimento
  int day = atoi(birth_date + 9);   // Dia de nascimento

  // Data atual fixa: 2024/09/09
  int age = 2024 - year; // Calcula a idade

  // Ajusta a idade se o aniversário ainda não tiver ocorrido em 2024
  if (9 < month || (month == 9 && 9 < day)) {
    age--; // Subtrai um ano caso ainda não tenha feito anos
  }

  return age; // Retorna a idade calculada
}

// Função para comparar duas strings, considerando que a segunda string pode ter
// um caractere '\n' no final
int comparaStrings(char *str1, char *str2) {
  if (strlen(str1) == strlen(str2) - 1) { // Considera o '\n' adicional
    int len = strlen(str1);
    for (int i = 0; i < len; i++) {
      if (str1[i] != str2[i]) {
        return 1; // Retorna 1 se as strings forem diferentes
      }
    }
  } else
    return 1; // Retorna 1 se as strings tiverem tamanhos diferentes
  return 0;   // Retorna 0 se as strings forem iguais
}

char *intToString(int number) {
  // Aloca memória suficiente para armazenar a string (máximo 12 caracteres para
  // int)
  char *result = (char *)malloc(12 * sizeof(char));
  if (result == NULL) {
    return NULL; // Retorna NULL se não conseguiu alocar memória
  }
  // Converte o número inteiro em string
  sprintf(result, "%d", number);
  return result;
}
