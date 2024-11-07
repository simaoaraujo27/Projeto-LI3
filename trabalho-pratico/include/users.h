#ifndef _USERS_H_
#define _USERS_H_

//#include "validation.h"
#include "utils.h"
#include <glib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct users Users;

typedef struct usersQ3 UsersQ3;

void setUserUsername(Users *u, char *username);
void setUserEmail(Users *u, char *email);
void setUserFirstName(Users *u, char *first_name);
void setUserLastName(Users *u, char *last_name);
void setUserBirthDate(Users *u, char *birth_date);
void setUserCountry(Users *u, char *country);
void setUserSubscriptionType(Users *u, char *subscription_type);
void setUserLikedMusicsId(Users *u, char *liked_musics_id);
void setUserAge(Users *u, char *birth_date);
void setUserQ3LikedMusicsId(UsersQ3 *u, char *liked_musics_id);
void setUserQ3Age(UsersQ3 *u, char *birth_date);

Users *separateUsers(char *line);
UsersQ3 *separateUsersQ3(char *line, char *birth_date);

char *pegarUserUsername(Users *u);
char *pegarUserEmail(Users *u);
char *pegarUserFirstName(Users *u);
char *pegarUserLastName(Users *u);
char *pegarUserBirthDate(Users *u);
char *pegarUserCountry(Users *u);
char *pegarUserSubscriptionType(Users *u);
char *pegarUserQ3LikedMusicsId(UsersQ3 *u);
char * pegarUserQ3Age(UsersQ3 *u);

char *getUserAge(gpointer user);
char *getUserUsername(gpointer user);
char *getUserEmail(gpointer user);
char *getUserFirstName(gpointer user);
char *getUserLastName(gpointer user);
char *getUserBirthDate(gpointer user);
char *getUserCountry(gpointer user);
char *getUserSubscriptionType(gpointer user);
char *getUserLikedMusicsId(gpointer user);
char *getUserQ3LikedMusicsId(gpointer user);
char *getUserQ3Age(gpointer user);

void destroyUser(gpointer user);
void destroyUserQ3(gpointer user);

#endif
