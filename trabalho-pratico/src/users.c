#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct users {
  char *username;          // identificador único do utilizador
  char *email;             // email de registo do utilizador
  char *first_name;        // primeiro nome do utilizador
  char *last_name;         // apelido do utilizador
  char *birth_date;        // data de nascimento
  char *country;           // país onde a conta do utilizador foi registada
  char *subscription_type; // tipo de subscrição, i.e., normal ou premium
  char *liked_musics_id;   // lista de indentificadores únicos das
                           // músicas gostadas pelo utilizador
};


Users *separateUsers(char *line) {
  // separa cada linha pelas suas respetivas variáveis
  Users *user = malloc(sizeof(struct users));
  if (!user) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  user->username = strdup(strsep(&line, ";"));
  remove_quotes(user->username);
  user->email = strdup(strsep(&line, ";"));
  remove_quotes(user->email);
  user->first_name = strdup(strsep(&line, ";"));
  remove_quotes(user->first_name);
  user->last_name = strdup(strsep(&line, ";"));
  remove_quotes(user->last_name);
  user->birth_date = strdup(strsep(&line, ";"));
  remove_quotes(user->birth_date);
  user->country = strdup(strsep(&line, ";"));
  remove_quotes(user->country);
  user->subscription_type = strdup(strsep(&line, ";"));
  remove_quotes(user->subscription_type);
  user->liked_musics_id = strdup(strsep(&line, ";"));
  remove_quotes(user->liked_musics_id);

  return user;
}

bool validateUser(Users *user) {
  return (validateEmail(user->email) &&
          validateSubscriptionType(user->subscription_type) &&
          validateDate(user->birth_date));
}

void parseUsers(FILE *fp, GHashTable *usersTable) {
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    Users *user = separateUsers(line);
    // Insere na HashTable usando o user->username como key
    g_hash_table_insert(usersTable, g_strdup(user->username), user);
  }
  free(line);
}

void destroyUser(gpointer user) {
  Users *u = (Users *)user;

  free(u->username);
  free(u->email);
  free(u->first_name);
  free(u->last_name);
  free(u->birth_date);
  free(u->country);
  free(u->subscription_type);
  free(u->liked_musics_id);

  free(u);
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

char *getUserSubscriptionType(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->subscription_type);
}

char *getUserLikedMusicsId(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->liked_musics_id);
}

