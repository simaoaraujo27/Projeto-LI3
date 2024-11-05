#ifndef _UTILS_H_
#define _UTILS_H_

#include <glib.h>

void remove_quotes(char *str);

int primeiraOcorr(char *line, char carac);

int temAspas(char *line);

void removeFstLast(char *str);

void removeLast(char *str);

char *calculate_age(char *birth_date);

void removeForLikedMusics(char *str);

int comparaStrings(char *str1, char *str2);

#endif