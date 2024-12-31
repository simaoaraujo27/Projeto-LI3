#ifndef _UTILS_H_
#define _UTILS_H_

#include <glib.h>

int somaHoras(char *hora1, char *hora2, int *dif);

int converterParaSegundos(char *tempo);

int calcularDiasAte_9_9_2024(char *data);

float arredondarParaSeteCasas(float numero);

void colocaTudoMinusculo(char *word);

void remove_quotes(char *str);

int primeiraOcorr(char *line, char carac);

int temAspas(char *line);

void removeFstLast(char *str);

void removeLast(char *str);

char *calculate_age_str(char *birth_date);

int calculateAge(char *birth_date);

void removeForLikedMusics(char *str);

int comparaStrings(char *str1, char *str2);

char *intToString(int number);

char *intToHour(int number);

void removeZerosAEsquerda(char *username);

int procuraIndexString(char **lista, char *string, int len);

void converterParaTempo(int segundos, char *resultado);

int calculateDiaAno(char *diaStr);

int isLeapYear(int year);

//char* calculateData(int diaAno);

char* calculateData(int diaAno, int year);

#endif