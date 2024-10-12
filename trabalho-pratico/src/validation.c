#include "validation.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Validação de data (formato: aaaa/mm/dd)
bool validate_date(char *date) {
  if (strlen(date) != 10)
    return false;

  // Verifica se os separadores estão nas posições corretas
  if (date[4] != '/' || date[7] != '/')
    return false;

  // Verifica se os outros caracteres são números
  for (int i = 0; i < 10; i++) {
    if (i == 4 || i == 7)
      continue;
    if (!isdigit(date[i]))
      return false;
  }

  // Extração do ano, mês e dia
  int year = atoi(date);
  int month = atoi(date + 5);
  int day = atoi(date + 8);

  // Verifica intervalos de mês e dia
  if (month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  // Verifica se a data não é futura (limite: 2024/09/09)
  if (year > 2024 || (year == 2024 && (month > 9 || (month == 9 && day > 9))))
    return false;

  return true;
}

// Validação de duração (formato: hh:mm:ss)
bool validate_duration(char *duration) {
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

// Validação de email (formato: username@domain.com)
bool validate_email(char *email) {
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
    if (!isalnum(*p))
      return false;
  }

  for (char *p = dot + 1; *p; p++) {
    if (!islower(*p))
      return false;
  }

  return true;
}

// Validação do tipo de subscrição (normal ou premium)
bool validate_subscription_type(char *type) {
  return (strcmp(type, "normal") == 0 || strcmp(type, "premium") == 0);
}

bool validate_year(char *year) {
  if (strlen(year) != 4)
    return false;
  int yearDig = atoi(year);
  if (yearDig > 2024)
    return false;
  return true;
}

bool validate_Music(Musics *musica) {
  if (validate_duration(musica->duration) && validate_year(musica->year))
    return true;
  else
    return false;
}

bool validate_User(Users *user) {
  if (validate_email(user->email) &&
      validate_subscription_type(user->subscription_type))
    return true;
}
