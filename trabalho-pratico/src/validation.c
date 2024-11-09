#include "validation.h"
#include "artists.h"
#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_users.h"
#include "musics.h"
#include "users.h"
#include "utils.h"

#include <assert.h>
#include <ctype.h>
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
  if (!at) {
    return false;
  }
  char *dot = strrchr(at, '.');
  if (!dot || dot - at < 2 || strlen(dot + 1) < 2 || strlen(dot + 1) > 3) {

    return false;
  }
  for (char *p = email; p < at; p++) {
    if (!isalnum(*p)) {
      return false;
    }
  }

  for (char *p = at + 1; p < dot; p++) {
    if (!isalpha(*p)) {
      return false;
    }
  }

  for (char *p = dot + 1; *p; p++) {
    if (!islower(*p) && !isalpha(*p)) {
      return false;
    }
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

bool validateMusicsIdUsers(char *musics_id, gestorMusics *gestorMusics) {
  remove_quotes(musics_id);
  removeFstLast(musics_id);
  int l = strlen(musics_id);

  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  while (l > 0) {
    if (l == strlen(musics_id)) {
      musics_id = musics_id + 1;
    } else
      musics_id = musics_id + 3;
    key = strdup(strsep(&musics_id, "'"));
    key[8] = '\0';
    gboolean found = g_hash_table_lookup_extended(getMusicsTable(gestorMusics),
                                                  key, &orig_key, &value);
    if (!found) {
      free(key);
      return false;
    }
    free(key);
    l -= 12;
  }

  return true;
}

bool validateArtistLine(char *idConstituent, char *type) {
  removeFstLast(idConstituent);
  removeFstLast(idConstituent);
  /* printf("Tipo: %s Tamanho Const: %ld\n", type, strlen(idConstituent)); */
  return (((strcmp(type, "individual") == 0) && strlen(idConstituent) == 0) ||
          ((strcmp(type, "group")) == 0 && (strlen(idConstituent) != 0)));
}

// validar artistas da musica
bool validateMusicsArtists(char *artists_id, gestorArtists *gestorArtists) {
  remove_quotes(artists_id);
  removeFstLast(artists_id);
  int l = strlen(artists_id);
  // printf("Artists ID original : %s\n", artists_id);
  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  while (l > 0) {
    if (l == strlen(artists_id)) {
      artists_id = artists_id + 1;
    } else
      artists_id = artists_id + 3;
    // printf("Artists ID dentro do whlie : %s\n", artists_id);
    key = strdup(strsep(&artists_id, "'"));
    key[8] = '\0';
    gboolean found = g_hash_table_lookup_extended(getArtistTable(gestorArtists),
                                                  key, &orig_key, &value);
    // printf("Key : %s\n", key);
    // printf("Found : %d\n", found);
    if (!found) {
      free(key);
      return false;
    }
    free(key);
    l -= 12;
  }

  return true;
}

bool validateMusicsLine(char *line, gestorArtists *gestorArtists) {
  char *a = strdup(strsep(&line, ";"));
  char *b = strdup(strsep(&line, ";"));
  char *artists_id = strdup(strsep(&line, ";"));
  char *durationSeconds = strdup(strsep(&line, ";"));
  char *c = strdup(strsep(&line, ";"));
  char *year = strdup(strsep(&line, "\n"));

  bool isValid = validateDuration(durationSeconds) && atoi(year) <= 2024 &&
                 validateCSVList(artists_id) &&
                 validateMusicsArtists(strdup(artists_id), gestorArtists);

  free(a);
  free(b);
  free(artists_id);
  free(durationSeconds);
  free(c);
  free(year);

  return isValid;
}

bool validateUsersLine(char *line, gestorMusics *gestorMusics) {
  char *username = strdup(strsep(&line, ";"));
  char *email = strdup(strsep(&line, ";"));
  remove_quotes(email);

  if (!validateEmail(email)) {
    free(username);
    free(email);
    // printf("ERRO 0\n");
    return false;
  }

  char *first_name = strdup(strsep(&line, ";"));
  char *last_name = strdup(strsep(&line, ";"));
  char *birth_date = strdup(strsep(&line, ";"));
  remove_quotes(birth_date);

  if (!validateDate(birth_date)) {
    free(first_name);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    // printf("ERRO 1\n");
    return false;
  }

  char *country = strdup(strsep(&line, ";"));
  char *subscription_type = strdup(strsep(&line, ";"));
  remove_quotes(subscription_type);

  if (!validateSubscriptionType(subscription_type)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    // printf("ERRO 2\n");
    return false;
  }

  char *liked_musics_id = strdup(line);
  removeLast(liked_musics_id);
  // printf("%s\n", liked_musics_id);
  if (!validateCSVList(liked_musics_id)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    free(liked_musics_id);
    // printf("ERRO 3\n");
    return false;
  }
  if (!validateMusicsIdUsers(liked_musics_id, gestorMusics)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    free(liked_musics_id);
    // printf("ERRO 4\n");
    return false;
  }

  free(first_name);
  free(country);
  free(subscription_type);
  free(last_name);
  free(birth_date);
  free(username);
  free(email);
  free(liked_musics_id);
  // printf("ERRO 5");
  return true;
}
