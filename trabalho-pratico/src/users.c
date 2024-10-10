#include "users.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Users *newUser(char *username, char *email, char *first_name, char *last_name,
               char *birth_date, char *country, char *subscription_type,
               char **liked_musics_id) {
  Users *user;
  user = malloc(sizeof(Users));
  if (!user) {
    fprintf(stderr, "Malloc failed!");
    return -1;
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