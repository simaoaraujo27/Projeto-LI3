#include "users.h"

struct users {
  char *age;
  char *username;          // identificador único do utilizador
  char *email;             // email de registo do utilizador
  char *first_name;        // primeiro nome do utilizador
  char *last_name;         // apelido do utilizador
  char *birth_date;        // data de nascimento
  char *country;           // país onde a conta do utilizador foi registada
  char *subscription_type; // tipo de subscrição, i.e., normal ou premium
  char *liked_musics_id;
};

struct usersQ3 {
  char *age;
  char *liked_musics_id; // lista de indentificadores únicos das
                         // músicas gostadas pelo utilizador
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

void setUserAge(Users *u, char *birth_date) {
  u->age = calculate_age_str(birth_date);
}

void setUserQ3LikedMusicsId(UsersQ3 *u, char *liked_musics_id) {
  remove_quotes(liked_musics_id);
  u->liked_musics_id = liked_musics_id;
}

void setUserQ3Age(UsersQ3 *u, char *birth_date) {
  u->age = calculate_age_str(birth_date);
}

Users *separateUsers(char *line) {
  // separa cada linha pelas suas respetivas variáveis
  Users *user = malloc(sizeof(struct users));
  if (!user) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  UsersQ3 *u = malloc(sizeof(struct usersQ3));
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
  setUserAge(user, getUserBirthDate(user));
/*   setUserQ3LikedMusicsId(u, strdup(strsep(&line, ";")));
  setUserQ3Age(u, getUserBirthDate(user)); */

  return user;
}

UsersQ3 *separateUsersQ3(char *line, char *birth_date) {

  UsersQ3 *u = malloc(sizeof(struct usersQ3));
  if (!u) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  setUserQ3LikedMusicsId(u, strdup(strsep(&line, ";")));
  setUserQ3Age(u, birth_date);

  return u;
}

char *pegarUserUsername(Users *u) { return strdup(u->username); }

char *pegarUserEmail(Users *u) { return strdup(u->email); }

char *pegarUserFirstName(Users *u) { return strdup(u->first_name); }

char *pegarUserLastName(Users *u) { return strdup(u->last_name); }

char *pegarUserBirthDate(Users *u) { return strdup(u->birth_date); }

char *pegarUserCountry(Users *u) { return strdup(u->country); }

char *pegarUserSubscriptionType(Users *u) {
  return strdup(u->subscription_type);
}

char *pegarUserQ3LikedMusicsId(UsersQ3 *u) {
  return strdup(u->liked_musics_id);
}

char *pegarUserQ3Age(UsersQ3 *u) { return strdup(u->age); }

char *getUserAge(gpointer user) {
  struct users *u = (struct users *)user;
  return strdup(u->age);
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

char *getUserQ3LikedMusicsId(gpointer user) {
  struct usersQ3 *u = (struct usersQ3 *)user;
  return strdup(u->liked_musics_id);
}

char *getUserQ3Age(gpointer user) {
  struct usersQ3 *u = (struct usersQ3 *)user;
  return strdup(u->age);
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
  // free(u->liked_musics_id);

  free(u);
}

void destroyUserQ3(gpointer user) {
  UsersQ3 *u = (UsersQ3 *)user;

  free(u->liked_musics_id);

  free(u);
}