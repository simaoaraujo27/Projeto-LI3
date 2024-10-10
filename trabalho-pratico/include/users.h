#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct users {
  char *username;          // identificador único do utilizador
  char *email;             // email de registo do utilizador
  char *first_name;        // primeiro nome do utilizador
  char *last_name;         // apelido do utilizador
  char *birth_date;        // data de nascimento
  char *country;           // país onde a conta do utilizador foi registada
  char *subscription_type; // tipo de subscrição, i.e., normal ou premium (FAZER
                           // UM ENUM)
  char **liked_musics_id; // lista de indentificadores únicos das músicas
                          // gostadas pelo utilizador
} Users;
