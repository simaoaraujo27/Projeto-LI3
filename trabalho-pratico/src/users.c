#include "users.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura de dados que representa um user
struct users {
  char *username;          // Nome de user (identificador único)
  char *email;             // Email de registro
  char *first_name;        // Primeiro nome
  char *last_name;         // Sobrenome
  char *birth_date;        // Data de nascimento
  char *country;           // País onde a conta foi registrada
  char *subscription_type; // Tipo de assinatura (normal ou premium)
  char *liked_musics_id;   // IDs das músicas curtidas
  GHashTable *musicsListening;
};

// Função para definir o username de um user
void setUserUsername(Users *u, char *username) {
  remove_quotes(username); // Remove aspas, se houver
  u->username = username;
}

// Função para definir o email de um user
void setUserEmail(Users *u, char *email) {
  remove_quotes(email); // Remove aspas, se houver
  u->email = email;
}

// Função para definir o primeiro nome de um user
void setUserFirstName(Users *u, char *first_name) {
  remove_quotes(first_name); // Remove aspas, se houver
  u->first_name = first_name;
}

// Função para definir o sobrenome de um user
void setUserLastName(Users *u, char *last_name) {
  remove_quotes(last_name); // Remove aspas, se houver
  u->last_name = last_name;
}

// Função para definir a data de nascimento de um user
void setUserBirthDate(Users *u, char *birth_date) {
  remove_quotes(birth_date); // Remove aspas, se houver
  u->birth_date = birth_date;
}

// Função para definir o país de um user
void setUserCountry(Users *u, char *country) {
  remove_quotes(country); // Remove aspas, se houver
  u->country = country;
}

// Função para definir o tipo de assinatura de um user
void setUserSubscriptionType(Users *u, char *subscription_type) {
  remove_quotes(subscription_type); // Remove aspas, se houver
  u->subscription_type = subscription_type;
}

// Função para definir o ID das músicas com like de um user
void setUserLikedMusicsId(Users *u, char *liked_musics_id) {
  remove_quotes(liked_musics_id); // Remove aspas, se houver
  u->liked_musics_id = liked_musics_id;
}

// Função para separar os dados de um user a partir de uma linha de texto
Users *separateUsers(char *line) {
  // Aloca memória para um novo user
  Users *user = malloc(sizeof(struct users));
  if (!user) {
    fprintf(
        stderr,
        "Malloc failed!"); // Se a alocação falhar, mostra uma mensagem de erro
    return NULL;
  }

  // Separa a linha pelos delimitadores ';' e preenche os campos do user
  setUserUsername(user, strdup(strsep(&line, ";")));
  setUserEmail(user, strdup(strsep(&line, ";")));
  setUserFirstName(user, strdup(strsep(&line, ";")));
  setUserLastName(user, strdup(strsep(&line, ";")));
  setUserBirthDate(user, strdup(strsep(&line, ";")));
  setUserCountry(user, strdup(strsep(&line, ";")));
  setUserSubscriptionType(user, strdup(strsep(&line, ";")));
  setUserLikedMusicsId(
      user, strdup(strsep(
                &line, "\n"))); // A última parte da linha é o liked_musics_id

  GHashTable *musicsListening =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  user->musicsListening = musicsListening;

  return user;
}

// Funções para pegar os valores de cada campo de um user
char *pegarUserUsername(Users *u) { return strdup(u->username); }
char *pegarUserEmail(Users *u) { return strdup(u->email); }
char *pegarUserFirstName(Users *u) { return strdup(u->first_name); }
char *pegarUserLastName(Users *u) { return strdup(u->last_name); }
char *pegarUserBirthDate(Users *u) { return strdup(u->birth_date); }
char *pegarUserCountry(Users *u) { return strdup(u->country); }
char *pegarUserSubscriptionType(Users *u) {
  return strdup(u->subscription_type);
}
char *pegarUserLikedMusicsId(Users *u) { return strdup(u->liked_musics_id); }

// Funções para pegar os valores de cada campo de um user, usando gpointer
// (útil para GList)
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

// Função para libertar a memória associada a um user
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
    // Cria um novo contador inicializado com 1
    int *new_count = g_malloc(sizeof(int));
    *new_count = 1;
    g_hash_table_insert(u->musicsListening, g_strdup(genre), new_count);
  }
}

int retornaIndiceGenero(char **nomesGeneros, char *genero, int numGeneros) {
  for (int i = 0; i < numGeneros; i++) {
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