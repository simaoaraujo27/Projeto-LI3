#include "utils.h"
#include "artists.h"
#include <ctype.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int comparaStrings(char *str1, char *str2) {
  if (strlen(str1) == strlen(str2) - 1) {
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