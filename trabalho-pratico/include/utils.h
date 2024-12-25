#ifndef _UTILS_H_
#define _UTILS_H_

#include <glib.h>

float arredondarParaSeisCasas(float numero);

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

#endif