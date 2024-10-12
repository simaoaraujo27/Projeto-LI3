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
  char *subscription_type; // tipo de subscrição, i.e., normal ou premium (FAZER
                           // UM ENUM)
  int *liked_musics_id; // lista de indentificadores únicos das músicas
                          // gostadas pelo utilizador
};

Users *newUser(char *username, char *email, char *first_name, char *last_name,
               char *birth_date, char *country, char *subscription_type,
               int *liked_musics_id) {
  Users *user = malloc(sizeof(struct users));
  if (!user) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }
  user->username = strdup(username);
  user->email = strdup(email);
  user->first_name = strdup(first_name);
  user->last_name = strdup(last_name);
  user->birth_date = strdup(birth_date);
  user->country = strdup(country);
  user->subscription_type = strdup(subscription_type);
  user->liked_musics_id = liked_musics_id;
  return user;
}