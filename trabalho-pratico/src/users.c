#include "users.h"
#include "resumo_users.h"
#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct users {
  char *username;
  char *email;
  char *first_name;
  char *last_name;
  char *birth_date;
  char *country;
  char *subscription_type;
  char *liked_musics_id;
  GHashTable *musicsListening;
  GArray *resumos;
};

void setUserUsername(Users *u, char *username) {
  remove_quotes(username);
  u->username = username;
}

void setUserEmail(Users *u, char *email) {
  remove_quotes(email);
  u->email = email;
}

void setUserFirstName(Users *u, char *first_name) {
  remove_quotes(first_name);
  u->first_name = first_name;
}

void setUserLastName(Users *u, char *last_name) {
  remove_quotes(last_name);
  u->last_name = last_name;
}

void setUserBirthDate(Users *u, char *birth_date) {
  remove_quotes(birth_date);
  u->birth_date = birth_date;
}

void setUserCountry(Users *u, char *country) {
  remove_quotes(country);
  u->country = country;
}

void setUserSubscriptionType(Users *u, char *subscription_type) {
  remove_quotes(subscription_type);
  u->subscription_type = subscription_type;
}

void setUserLikedMusicsId(Users *u, char *liked_musics_id) {
  remove_quotes(liked_musics_id);
  u->liked_musics_id = liked_musics_id;
}

Users *separateUsers(char *line) {
  Users *user = malloc(sizeof(struct users));
  if (!user) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  setUserUsername(user, strdup(strsep(&line, ";")));
  setUserEmail(user, strdup(strsep(&line, ";")));
  setUserFirstName(user, strdup(strsep(&line, ";")));
  setUserLastName(user, strdup(strsep(&line, ";")));
  setUserBirthDate(user, strdup(strsep(&line, ";")));
  setUserCountry(user, strdup(strsep(&line, ";")));
  setUserSubscriptionType(user, strdup(strsep(&line, ";")));
  setUserLikedMusicsId(user, strdup(strsep(&line, "\n")));

  GHashTable *musicsListening =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  user->musicsListening = musicsListening;

  GArray *resumos = g_array_new(FALSE, FALSE, sizeof(Resumo *));
  g_array_set_size(resumos, 7);
  for (int i = 0; i < 7; i++) {
    g_array_index(resumos, Resumo *, i) = NULL;
  }

  user->resumos = resumos;

  return user;
}

int existUserResume(gpointer user, int indice) {
  struct users *u = (struct users *)user;
  if (g_array_index(u->resumos, Resumo *, indice) == NULL)
    return 0;
  else
    return 1;
}

char *getUserUsername(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->username);
}

char *getUserEmail(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->email);
}

char *getUserFirstName(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->first_name);
}

char *getUserLastName(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->last_name);
}

char *getUserBirthDate(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->birth_date);
}

char *getUserCountry(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->country);
}

char *getUserLikedMusicsId(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->liked_musics_id);
}

GArray *getUserResumo(gpointer user) {
  struct users *u = (struct users *)user;
  return u->resumos;
}

void destroyUser(Users *u) {
  if (u) {
    free(u->username);
    free(u->email);
    free(u->first_name);
    free(u->last_name);
    free(u->birth_date);
    free(u->country);
    free(u->subscription_type);
    free(u->liked_musics_id);
    g_hash_table_destroy(u->musicsListening);
    destroyUserResumo(u->resumos);
    g_array_free(u->resumos, TRUE);
    free(u);
  }
}

void incrementMusicsListening(gpointer user, char *genre) {
  struct users *u = (struct users *)user;
  gpointer orig_key = NULL;
  gpointer value = NULL;
  remove_quotes(genre);
  gboolean found = g_hash_table_lookup_extended(u->musicsListening, genre,
                                                &orig_key, &value);
  if (found) {
    int *count = (int *)value;
    (*count)++;
  } else {
    int *new_count = malloc(sizeof(int));
    *new_count = 1;
    g_hash_table_insert(u->musicsListening, g_strdup(genre), new_count);
  }
}

int retornaIndiceGenero(char **nomesGeneros, char *genero, int numGeneros) {
  for (int i = 0; i < numGeneros; i++) {
    remove_quotes(nomesGeneros[i]);
    if (strcmp(nomesGeneros[i], genero) == 0)
      return i;
  }
  return -1;
}

void preencheLinhaMatriz(int **matrizClassificaoMusicas, int linha, Users *User,
                         int numGeneros, char **nomesGeneros) {
  GHashTableIter iter;
  gpointer key1, value1;
  g_hash_table_iter_init(&iter, User->musicsListening);
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    char *genre = (char *)key1;
    int *count = (int *)value1;
    int coluna = retornaIndiceGenero(nomesGeneros, genre, numGeneros);
    matrizClassificaoMusicas[linha][coluna] = *count;
  }
}
