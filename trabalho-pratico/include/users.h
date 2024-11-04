#ifndef _USERS_H_
#define _USERS_H_

#include "validation.h"
#include "utils.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct users Users;

void setUserUsername(Users *u, char *username);
void setUserEmail(Users *u, char *email);
void setUserFirstName(Users *u, char *first_name);
void setUserLastName(Users *u, char *last_name);
void setUserBirthDate(Users *u, char *birth_date);
void setUserCountry(Users *u, char *country);
void setUserSubscriptionType(Users *u, char *subscription_type);
void setUserLikedMusicsId(Users *u, char *liked_musics_id);

Users *separateUsers(char *line);
bool validateUser(Users *user);

char *getUserUsername(gpointer user);
char *getUserEmail(gpointer user);
char *getUserFirstName(gpointer user);
char *getUserLastName(gpointer user);
char *getUserBirthDate(gpointer user);
char *getUserCountry(gpointer user);
char *getUserSubscriptionType(gpointer user);
char *getUserLikedMusicsId(gpointer user);

void destroyUser(gpointer user);

#endif
