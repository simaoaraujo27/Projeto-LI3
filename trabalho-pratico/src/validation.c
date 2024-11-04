#include "validation.h"
#include "artists.h"
#include "musics.h"
#include "users.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// (formato: aaaa/mm/dd)
bool validateDate(char *date) {
  if (strlen(date) != 10)
    return false;

  if (date[4] != '/' || date[7] != '/')
    return false;

  for (int i = 0; i < 10; i++) {
    if (i == 4 || i == 7)
      continue;
    if (!isdigit(date[i]))
      return false;
  }

  int year = atoi(date);
  int month = atoi(date + 5);
  int day = atoi(date + 8);

  if (month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  // Verifica se a data não é futura (limite: 2024/09/09)
  if (year > 2024 || (year == 2024 && (month > 9 || (month == 9 && day > 9))))
    return false;

  return true;
}

// (formato: hh:mm:ss)
bool validateDuration(char *duration) {
  remove_quotes(duration);
  if (strlen(duration) != 8)
    return false;
  if (duration[2] != ':' || duration[5] != ':')
    return false;

  for (int i = 0; i < 8; i++) {
    if (i == 2 || i == 5)
      continue;
    if (!isdigit(duration[i]))
      return false;
  }

  int hours = atoi(duration);
  int minutes = atoi(duration + 3);
  int seconds = atoi(duration + 6);

  if (hours < 0 || hours > 99 || minutes < 0 || minutes > 59 || seconds < 0 ||
      seconds > 59)
    return false;

  return true;
}

// (formato: username@domain.com)
bool validateEmail(char *email) {
  char *at = strchr(email, '@');
  if (!at)
    return false;

  char *dot = strrchr(at, '.');
  if (!dot || dot - at < 2 || strlen(dot + 1) < 2 || strlen(dot + 1) > 3)
    return false;

  for (char *p = email; p < at; p++) {
    if (!isalnum(*p))
      return false;
  }

  for (char *p = at + 1; p < dot; p++) {
    if (!isalpha(*p))
      return false;
  }

  for (char *p = dot + 1; *p; p++) {
    if (!islower(*p) && !isalpha(*p))
      return false;
  }

  return true;
}

bool validateSubscriptionType(char *type) {
  return (strcmp(type, "normal") == 0 || strcmp(type, "premium") == 0);
}

bool validateCSVList(char *list) {
  int lastIndex = strlen(list) - 1;
  return (list[0] == '"' && list[1] == '[' && list[lastIndex - 1] == ']' &&
          list[lastIndex] == '"');
}

bool validateUsersLine(char *line) {
  
  // VALIDAÇÃO SINTÁTICA
  char *username = strdup(strsep(&line, ";"));

  char *email = strdup(strsep(&line, ";"));
  remove_quotes(email);
  if (!validateEmail(email))
    return false;

  char *first_name = strdup(strsep(&line, ";"));
  char *last_name = strdup(strsep(&line, ";"));
  char *birth_date = strdup(strsep(&line, ";"));
  remove_quotes(birth_date);
  if (!validateDate(birth_date))
    return false;

  char *country = strdup(strsep(&line, ";"));
  char *subscription_type = strdup(strsep(&line, ";"));
  remove_quotes(subscription_type);

  if (!validateSubscriptionType(subscription_type))
    return false;

  char *liked_musics_id = strdup(line);

  if (!validateCSVList(liked_musics_id))
    return false;

  // VALIDAÇÃO LÓGICA

  /*   char *musica = strdup(strsep(&line + 1, ","));
    while (strcmp(musica, "]") != 0) {
      musica = strdup(strsep(&line + 1, ","));
      printf("%s\n", musica);
    } */

  return true;
}
