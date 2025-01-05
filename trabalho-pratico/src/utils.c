#include "utils.h"
#include "artists.h"
#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_SIZE 1024
#define MAX_INPUT_SIZE 512

int converterParaSegundos(char *tempo) {
  int horas, minutos, segundos;

  if (sscanf(tempo, "%d:%d:%d", &horas, &minutos, &segundos) != 3) {
    fprintf(stderr, "Erro: Formato de tempo inválido.\n");
    return -1;
  }

  return horas * 3600 + minutos * 60 + segundos;
}

int isLeapYear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int year, int month) {
  int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month == 2 && isLeapYear(year)) {
    return 29;
  }
  return daysPerMonth[month - 1];
}

int calcularDiferencaDias(char *data1, char *data2) {
  int year1, month1, day1;
  int year2, month2, day2;

  if (sscanf(data1, "%d/%d/%d", &year1, &month1, &day1) != 3 ||
      sscanf(data2, "%d/%d/%d", &year2, &month2, &day2) != 3) {
    fprintf(stderr, "Erro ao analisar as datas.\n");
    return -1;
  }

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

  return abs(totalDays2 - totalDays1);
}

int calcularDiasAte_9_9_2024(char *data) {
  char *data_limite = "2024/09/09";
  return calcularDiferencaDias(data, data_limite);
}

void colocaTudoMinusculo(char *word) {
  for (int i = 0; i < (int)strlen(word); i++) {
    word[i] = tolower(word[i]);
  }
}

void remove_quotes(char *str) {
  int len = strlen(str);

  if (len > 1 && str[0] == '"' && str[len - 1] == '"') {
    for (int i = 0; i < len - 1; i++) {
      str[i] = str[i + 1];
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

void removeLast(char *str) {
  int len = strlen(str);
  str[len - 1] = '\0';
}

char *calculate_age_str(char *birth_date) {
  int birth_year, birth_month, birth_day;

  sscanf(birth_date, "%d/%d/%d", &birth_year, &birth_month, &birth_day);

  int current_year = 2024;
  int current_month = 9;
  int current_day = 9;

  int age = current_year - birth_year;

  if (current_month < birth_month ||
      (current_month == birth_month && current_day < birth_day)) {
    age--;
  }

  char *age_str = malloc(12 * sizeof(char));

  if (age_str == NULL) {
    return NULL;
  }

  snprintf(age_str, 12, "%d", age);

  return age_str;
}

char *intToString(int number) {
  char *result = (char *)malloc(12 * sizeof(char));
  if (result == NULL) {
    return NULL;
  }
  sprintf(result, "%d", number);
  return result;
}

char *intToHour(int number) {
  char *result = (char *)malloc(3 * sizeof(char));
  if (result == NULL) {
    return NULL;
  }
  sprintf(result, "%02d", number);
  return result;
}

void converterParaTempo(int segundos, char *resultado) {
  int horas, minutos;

  segundos = abs(segundos);

  horas = segundos / 3600;
  segundos %= 3600;
  minutos = segundos / 60;
  segundos %= 60;

  snprintf(resultado, 16, "%02d:%02d:%02d", horas, minutos, segundos);
}

int calculateDiaAno(char *diaStr) {
  int diasPorMes[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int mes, dia;

  if (sscanf(diaStr, "%d/%d", &mes, &dia) != 2) {
    return -1;
  }

  if (mes < 1 || mes > 12 || dia < 1 || dia > diasPorMes[mes]) {
    return -1;
  }

  int diaAno = 0;
  for (int i = 1; i < mes; i++) {
    diaAno += diasPorMes[i];
  }
  diaAno += dia;

  return diaAno;
}

char *calculateData(int diaAno, int year) {
  static char data[20];
  int diasPorMes[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  int isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
  diasPorMes[2] = isLeapYear ? 29 : 28;

  int maxDias = isLeapYear ? 366 : 365;
  if (diaAno < 1 || diaAno > maxDias) {
    return NULL;
  }

  int mes = 1, diaRestante = diaAno;

  while (diaRestante > diasPorMes[mes]) {
    diaRestante -= diasPorMes[mes];
    mes++;
  }

  snprintf(data, sizeof(data), "%04d/%02d/%02d", year, mes, diaRestante);

  return data;
}

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Valida o caminho inserido pelo utilizador
bool validaPath(const char *path) {
  struct stat info;
  return stat(path, &info) == 0;
}

// Remove o caracter '\n' no fim de uma string
void removerNovaLinha(char *str) {
  char *pos = strchr(str, '\n');
  if (pos != NULL) {
    *pos = '\0';
  }
}

// Função para imprimir uma linha ajustada à largura do terminal
void printFullLine(char ch, const char *color) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int largura_terminal = w.ws_col;

  printf("%s", color);
  for (int i = 0; i < largura_terminal; i++) {
    putchar(ch);
  }
  printf("\033[0m\n");
}

// Função para imprimir texto centralizado
void printCentered(const char *text, const char *color) {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int largura_terminal = w.ws_col;

  int len_text = strlen(text);
  int padding_esquerda = (largura_terminal - len_text) / 2;

  printf("%s%*s%s\033[0m\n", color, padding_esquerda + len_text, text, "");
}

void printRGB(const char *text) {
  int r, g, b;
  size_t len = strlen(text);

  for (size_t i = 0; i < len; i++) {
    // Calcular cores vibrantes usando senos para suavidade
    r = (int)(sin(0.1 * i + 0) * 127 + 128); // Variando entre 0-255
    g = (int)(sin(0.1 * i + 2) * 127 + 128); // Fase deslocada
    b = (int)(sin(0.1 * i + 4) * 127 + 128); // Fase deslocada

    // Imprimir o caractere com a cor RGB
    printf("\033[38;2;%d;%d;%dm%c", r, g, b, text[i]);
    fflush(stdout); // Forçar saída no terminal
    usleep(50000);  // Pequeno atraso para efeito visual
  }

  printf("\033[0m\n"); // Resetar cor
}

void escolheSeparador(char *separador) {
  *separador = ' ';
  printf("Escolha o separador (; ou =): ");
  assert(scanf("%c", separador) != -1);
  limparBufferEntrada();

  while (1) {
    if (*separador != ';' && *separador != '=') {
      printf("\033[1;31mERRO: O separador inserido (%c) é inválido!\033[0m\n",
             *separador);

      printf("Por favor, insira um separador válido: ");
      assert(scanf("%c", separador) != -1);
      limparBufferEntrada();
    } else {
      break;
    }
  }
}

// Função para printar resultados das queries
void printResults(int nQueries) {
  for (int i = 1; i <= nQueries; i++) {
    char title[64];
    snprintf(title, 64, "Resultado do input %d:", i);
    printRGB(title);
    char path[MAX_PATH_SIZE];
    snprintf(path, MAX_PATH_SIZE, "./resultados/command%d_output.txt", i);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
      fprintf(stderr, "Erro ao abrir o arquivo: %s\n", path);
      continue;
    }

    char line[MAX_INPUT_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {
      printf("%s", line);
    }
    printf("\n");

    fclose(file);
  }
}

// Função para printar uma string em vermelho
void printRed(const char *text) {
  const char *redColorCode = "\033[1;31m";
  const char *resetColorCode = "\033[0m";
  printf("%s%s%s\n", redColorCode, text, resetColorCode);
}

int lerNumeroValido() {
  int num;
  while (1) {
    printf("Que query deseja executar (Opções de 1 a 6) | 0 para parar o "
           "programa: ");
    if (scanf("%d", &num) == 1) {
      // Se a leitura foi bem-sucedida, retornamos o número
      if (num >= 0 && num <= 6) {
        return num;
      }
      printRed("ERRO: Query inválida! Por favor, insira um número "
               "válido\n");

    } else {
      // Se não foi um número, descartamos o que foi inserido e pedimos
      // novamente
      printf("\033[31mERRO: Entrada inválida. Por favor, insira um número "
             "válido.\033[0m\n");
      limparBufferEntrada();
    }
    printf("\n");
  }
}