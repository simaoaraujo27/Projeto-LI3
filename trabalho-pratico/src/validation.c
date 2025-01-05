#include "validation.h"
#include "artists.h"
#include "gestor_albuns.h"
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

bool validatePlataformHistory(char *plataform) {
  colocaTudoMinusculo(plataform);
  return (strcmp(plataform, "mobile") == 0 ||
          strcmp(plataform, "desktop") == 0);
}

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

  if (year > 2024 || (year == 2024 && (month > 9 || (month == 9 && day > 9))))
    return false;

  return true;
}

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
  int l = (int)strlen(musics_id);

  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  while (l > 0) {
    if (l == (int)strlen(musics_id)) {
      musics_id = musics_id + 1;
    } else
      musics_id = musics_id + 3;
    key = strdup(strsep(&musics_id, "'"));
    key[8] = '\0';
    gboolean found =
        lookUpMusicsHashTable(gestorMusics, key, &orig_key, &value);
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
  colocaTudoMinusculo(type);
  return (((strcmp(type, "individual") == 0) && strlen(idConstituent) == 0) ||
          ((strcmp(type, "group") == 0) && (strlen(idConstituent) != 0)));
}

bool validateMusicsArtistsAndAlbuns(char *albuns_id, char *artists_id,
                                    gestorArtists *gestorArtists,
                                    gestorAlbuns *gestorAlbuns) {
  remove_quotes(artists_id);
  removeFstLast(artists_id);
  int lentghArtistsId = (int)strlen(artists_id);
  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  while (lentghArtistsId > 0) {
    if (lentghArtistsId == (int)strlen(artists_id)) {
      artists_id = artists_id + 1;
    } else
      artists_id = artists_id + 3;

    if (key != NULL) {
      free(key);
      key = NULL;
    }
    key = strdup(strsep(&artists_id, "'"));
    key[8] = '\0';
    gboolean found =
        lookUpArtistsHashTable(gestorArtists, key, &value, &orig_key);
    if (!found) {
      free(key);
      return false;
    }
    lentghArtistsId -= 12;
  }

  removeFstLast(albuns_id);
  gboolean found =
      lookUpAlbunsHashTable(gestorAlbuns, albuns_id, &value, &orig_key);
  if (!found) {
    free(key);
    return false;
  }
  if (key != NULL) {
    free(key);
    key = NULL;
  }

  return true;
}

bool validateMusicsLine(char *line, gestorArtists *gestorArtists,
                        gestorAlbuns *gestorAlbuns) {
  char *id = strdup(strsep(&line, ";"));
  char *title = strdup(strsep(&line, ";"));
  char *artists_id = strdup(strsep(&line, ";"));
  char *albuns_id = strdup(strsep(&line, ";"));
  char *durationSeconds = strdup(strsep(&line, ";"));
  char *genre = strdup(strsep(&line, ";"));
  char *year = strdup(strsep(&line, "\n"));
  char *artist_id_copia = strdup(artists_id);
  char *albuns_id_copia = strdup(albuns_id);

  bool isValid =
      validateDuration(durationSeconds) && atoi(year) <= 2024 &&
      validateCSVList(artists_id) &&
      validateMusicsArtistsAndAlbuns(albuns_id_copia, artist_id_copia,
                                     gestorArtists, gestorAlbuns);

  free(id);
  free(title);
  free(artists_id);
  free(albuns_id);
  free(durationSeconds);
  free(genre);
  free(year);
  free(artist_id_copia);
  free(albuns_id_copia);

  return isValid;
}

bool validateUsersLine(char *line, gestorMusics *gestorMusics) {
  char *username = strdup(strsep(&line, ";"));
  char *email = strdup(strsep(&line, ";"));
  remove_quotes(email);
  if (!validateEmail(email)) {
    free(username);
    free(email);
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
    return false;
  }

  char *liked_musics_id = strdup(line);
  removeLast(liked_musics_id);
  if (!validateCSVList(liked_musics_id)) {
    free(first_name);
    free(country);
    free(subscription_type);
    free(last_name);
    free(birth_date);
    free(username);
    free(email);
    free(liked_musics_id);
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

  return true;
}

bool validateArtistsIdAlbums(char *artists_id, gestorArtists *gestorArtists) {
  remove_quotes(artists_id);
  removeFstLast(artists_id);
  int lentghArtistsId = (int)strlen(artists_id);
  char *key = NULL;
  gpointer orig_key;
  gpointer value;

  while (lentghArtistsId > 0) {
    if (lentghArtistsId == (int)strlen(artists_id)) {
      artists_id = artists_id + 1;
    } else
      artists_id = artists_id + 3;

    if (key != NULL) {
      free(key);
      key = NULL;
    }

    key = strdup(strsep(&artists_id, "'"));
    key[8] = '\0';
    gboolean found =
        lookUpArtistsHashTable(gestorArtists, key, &value, &orig_key);
    if (!found) {
      free(key);
      return false;
    }
    lentghArtistsId -= 12;
  }

  if (key != NULL) {
    free(key);
    key = NULL;
  }
  return true;
}

bool validateAlbumsLine(char *line, gestorArtists *gestorArtists) {
  char *id = strdup(strsep(&line, ";"));
  char *title = strdup(strsep(&line, ";"));
  char *artists_id = strdup(strsep(&line, ";"));
  char *year = strdup(strsep(&line, ";"));

  bool validate = (atoi(year) <= 2024 &&
                   validateArtistsIdAlbums(artists_id, gestorArtists));

  free(id);
  free(title);
  free(artists_id);
  free(year);

  return validate;
}

bool validateHistoryLine(char *line) {
  char *id = strdup(strsep(&line, ";"));
  char *user_id = strdup(strsep(&line, ";"));
  char *music_id = strdup(strsep(&line, ";"));
  char *timestamp = strdup(strsep(&line, ";"));
  char *duration = strdup(strsep(&line, ";"));
  char *plataform = strdup(strsep(&line, "\n"));
  remove_quotes(plataform);
  bool validate = validatePlataformHistory(plataform);
  free(id);
  free(user_id);
  free(music_id);
  free(timestamp);
  free(duration);
  free(plataform);

  return validate;
}

bool validateAge(char *age) {
  if (age == NULL) {
    return false;
  }

  for (int i = 0; age[i] != '\0'; i++) {
    if (!isdigit(age[i])) {
      return false;
    }
  }

  int idade = atoi(age);

  if (idade >= 0 && idade <= 150) {
    return true;
  }
  return false;
}

// Verifica se o id de um User ou Artist é válido (sintaticamente)
bool validateId(char *id) {
  if (strlen(id) != 8)
    return false;
  if (id[0] != 'A' && id[0] != 'U')
    return false;
  for (int i = 1; i <= 7; i++) {
    if (!isdigit(id[i]))
      return false;
  }

  return true;
}

// Função para verificar se a data 'end' é posterior ou igual a 'begin'
bool isAfter(const char *end, const char *begin) {
  int endYear, endMonth, endDay;
  int beginYear, beginMonth, beginDay;

  sscanf(end, "%d/%d/%d", &endYear, &endMonth, &endDay);
  sscanf(begin, "%d/%d/%d", &beginYear, &beginMonth, &beginDay);

  if (endYear > beginYear)
    return true;
  else if (endYear == beginYear) {
    if (endMonth > beginMonth)
      return true;
    else if (endMonth == beginMonth) {
      if (endDay >= beginDay)
        return true;
    }
  }

  return false;
}

bool allDigit(char *num) {
  for (int i = 0; num[i] != '\0'; i++) {
    if (!isdigit(num[i]))
      return false;
  }

  return true;
}

bool validateYear(char *year) {
  int num = atoi(year);
  return (num > 0);
}