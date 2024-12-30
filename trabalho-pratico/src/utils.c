#include "utils.h"
#include "artists.h"
#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int somaHoras(char *hora1, char *hora2, int *dif) {
  int h1, m1, s1, h2, m2, s2;

  // Converter as strings para horas, minutos e segundos
  sscanf(hora1, "%d:%d:%d", &h1, &m1, &s1);
  sscanf(hora2, "%d:%d:%d", &h2, &m2, &s2);

  // Somar as horas, minutos e segundos
  int totalSegundos = (h1 * 3600 + m1 * 60 + s1) + (h2 * 3600 + m2 * 60 + s2);

  // Verificar se passou de 24 horas (86400 segundos)
  if (totalSegundos >= 86400) {
    *dif = 86000 - totalSegundos;
    return 1;
  } else {
    return 0;
  }
}

// Função para converter "HH:MM:SS" em segundos
int converterParaSegundos(char *tempo) {
  int horas, minutos, segundos;

  // Dividir a string em horas, minutos e segundos
  if (sscanf(tempo, "%d:%d:%d", &horas, &minutos, &segundos) != 3) {
    fprintf(stderr, "Erro: Formato de tempo inválido.\n");
    return -1;
  }

  // Calcular o total de segundos
  return horas * 3600 + minutos * 60 + segundos;
}

// Função para calcular se um ano é bissexto
int isLeapYear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Função para calcular o número de dias em um mês
int daysInMonth(int year, int month) {
  int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  return daysPerMonth[month - 1];
}

// Função para calcular a diferença de dias entre duas datas
int calcularDiferencaDias(char *data1, char *data2) {
  int year1, month1, day1;
  int year2, month2, day2;

  // Parse as duas datas
  if (sscanf(data1, "%d/%d/%d", &year1, &month1, &day1) != 3 ||
      sscanf(data2, "%d/%d/%d", &year2, &month2, &day2) != 3) {
    fprintf(stderr, "Erro ao analisar as datas.\n");
    return -1;
  }

  // Converter ambas as datas para o formato "dias desde o início do calendário"
  int totalDays1 = 0, totalDays2 = 0;

  for (int y = 0; y < year1; y++) {
    totalDays1 += isLeapYear(y) ? 366 : 365;
  }
  for (int m = 1; m < month1; m++) {
    totalDays1 += daysInMonth(year1, m);
  }
  totalDays1 += day1;

  for (int y = 0; y < year2; y++) {
    totalDays2 += isLeapYear(y) ? 366 : 365;
  }
  for (int m = 1; m < month2; m++) {
    totalDays2 += daysInMonth(year2, m);
  }
  totalDays2 += day2;

  // Retornar a diferença absoluta de dias
  return abs(totalDays2 - totalDays1);
}

// Função para calcular os dias restantes até 9/9/2024
int calcularDiasAte_9_9_2024(char *data) {
  char *data_limite = "2024/09/09";
  return calcularDiferencaDias(data, data_limite);
}

float arredondarParaSeteCasas(float numero) {
  return roundf(numero * 10000000000) / 10000000000;
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

void removeZerosAEsquerda(char *username) {
  // Encontra o primeiro caractere não-zero e remove o 'U'
  char *primeiroNaoZero = username;
  primeiroNaoZero++;

  while (*primeiroNaoZero == '0') {
    primeiroNaoZero++;
  }

  // Se todos os caracteres eram zeros, deixa apenas um zero
  if (*primeiroNaoZero == '\0') {
    strcpy(username, "0");
  } else {
    // Copia a substring sem zeros de volta para o início da string
    strcpy(username, primeiroNaoZero);
  }
}

// Devolve o index de um elemento da string
// Devolve -1 se não o encontrar
int procuraIndexString(char **lista, char *string, int len) {
  for (int i = 0; i < len; i++) {
    if (!strcmp(lista[i], string))
      return i;
  }

  return -1;
}

// Função para converter segundos em "HH:MM:SS"
void converterParaTempo(int segundos, char *resultado) {
    int horas, minutos;

    // Garantir que os segundos sejam positivos
    segundos = abs(segundos);

    // Calcular horas, minutos e segundos
    horas = segundos / 3600;
    segundos %= 3600;
    minutos = segundos / 60;
    segundos %= 60;

    // Formatar a string no formato "HH:MM:SS"
    snprintf(resultado, 16, "%02d:%02d:%02d", horas, minutos, segundos);
}