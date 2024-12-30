#ifndef _USERS_H_
#define _USERS_H_

#include <glib.h>

typedef struct artistaAudicoes ArtistaTempo;
typedef struct categoriaTempo AlbumTempo;
typedef struct categoriaTempo GeneroTempo;
typedef struct resumo Resumo;

typedef struct users Users;

void setUserUsername(Users *u, char *username);
void setUserEmail(Users *u, char *email);
void setUserFirstName(Users *u, char *first_name);
void setUserLastName(Users *u, char *last_name);
void setUserBirthDate(Users *u, char *birth_date);
void setUserCountry(Users *u, char *country);
void setUserSubscriptionType(Users *u, char *subscription_type);
void setUserLikedMusicsId(Users *u, char *liked_musics_id);
void setUserAge(Users *u, char *birth_date);
void setUserLikedMusicsId(Users *u, char *liked_musics_id);
void updateUserResume(gpointer u, int year);

Users *separateUsers(char *line);

void incrementMusicsListening(gpointer user, char *genre);

char *pegarUserUsername(Users *u);
char *pegarUserEmail(Users *u);
char *pegarUserFirstName(Users *u);
char *pegarUserLastName(Users *u);
char *pegarUserBirthDate(Users *u);
char *pegarUserCountry(Users *u);
char *pegarUserSubscriptionType(Users *u);
char *pegarUserLikedMusicsId(Users *u);

int existUserResume(gpointer user, int indice);
char *getUserAge(gpointer user);
char *getUserUsername(gpointer user);
char *getUserEmail(gpointer user);
char *getUserFirstName(gpointer user);
char *getUserLastName(gpointer user);
char *getUserBirthDate(gpointer user);
char *getUserCountry(gpointer user);
char *getUserSubscriptionType(gpointer user);
char *getUserLikedMusicsId(gpointer user);
char *getUserLikedMusicsId(gpointer user);

void destroyUser(Users *u);

void preencheLinhaMatriz(int **matrizClassificaoMusicas, int linha, Users *User,
                         int numGeneros, char **nomesGeneros);

#endif
