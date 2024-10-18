#include "users.h"
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
  user->email = strdup(strsep(&line, ";"));
  user->first_name = strdup(strsep(&line, ";"));
  user->last_name = strdup(strsep(&line, ";"));
  user->birth_date = strdup(strsep(&line, ";"));
  user->country = strdup(strsep(&line, ";"));
  user->subscription_type = strdup(strsep(&line, ";"));
  user->liked_musics_id = strdup(strsep(&line, ";"));

  return user;
}

bool validateUser(Users *user) {
  return (validateEmail(user->email) &&
          validateSubscriptionType(user->subscription_type) &&
          validateDate(user->birth_date));
}

void parseUsers(FILE *fp) {
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, fp) != -1) {
    Users *user = separateUsers(line);
  }

  free(line);
}

void destroyUsers(gpointer user) { return; }