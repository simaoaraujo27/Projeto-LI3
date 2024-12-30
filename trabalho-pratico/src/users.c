#include "users.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artistaAudicoes {
  char *artista; // artista
  guint tempo;  // tempo de reprodução em segundos
  guint numMusicas; // número de músicas diferentes ouvidas desta artista
};

struct categoriaTempo {
  char *categoria; // album ou género
  guint tempo;  // tempo de reprodução em segundos
};

struct resumo{
  char **idsMusics;
  ArtistaTempo *artists;   // ordenar
  AlbumTempo *albuns;      // ordenar
  GeneroTempo *generos;    // ordenar
  int dias[366];
  int horas[24];
  int listening_time;
  int num_musicas_diferentes;
};

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
  GArray *resumos;
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

ArtistaTempo *initResumoArtists(){
  ArtistaTempo *a = (ArtistaTempo *)malloc(sizeof(ArtistaTempo));
  a->artista = NULL;
  a->tempo = 0;
  a->numMusicas = 0;
  return a;
}

struct categoriaTempo *initAlbunsEGeneros(){
  struct categoriaTempo *c = (struct categoriaTempo *)malloc(sizeof(struct categoriaTempo));
  c->categoria = NULL;
  c->tempo = 0;
  return c;
}

Resumo *initResumo() {
  Resumo *res = (Resumo *)malloc(sizeof(Resumo));
  res->idsMusics = NULL;
  res->artists = initResumoArtists();
  res->albuns = initAlbunsEGeneros();
  res->generos = initAlbunsEGeneros();
  for (int i = 0; i < 366; i++) {
      res->dias[i] = 0;
  }
  for (int i = 0; i < 24; i++) {
      res->horas[i] = 0;
  }
  res->listening_time = 0;
  res->num_musicas_diferentes = 0;

  return res;
}

// CONTINUAR ISTO (VER GESTOR ARTISTS/QUERY4/GESTOR HISTORY/ ARTISTS)
void updateUserResume(gpointer u, int year) {
  struct users *user = (struct users *)u;
  GArray *resumos = user->resumos;

  // Verifica o tamanho atual da duração por semana
  int tamanho = resumos->len;

  int indice = 2024 - year;
  // Ajusta o tamanho do array se necessário
  if (indice >= tamanho) {
    g_array_set_size(resumos, (guint)(indice + 1)); 

    // Inicializa as novas posições com 0
    for (int i = tamanho; i <= indice; i++) {
      g_array_index(resumos, Resumo *, i) = NULL;
    }
    tamanho = resumos->len;
  }

  Resumo *res = g_array_index(resumos, Resumo*, indice);
  if(res == NULL){
    res = initResumo();
  }

  g_array_index(resumos, Resumo *, indice) = res;

  // Retorna o novo valor da duração para a semana
  //return g_array_index(durationPerWeek, int, semana);
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

  GArray *resumos = g_array_new(FALSE, FALSE, sizeof(Resumo *));
  g_array_set_size(resumos, 7);
  for (int i = 0; i < (int)resumos->len; i++) {
    g_array_index(resumos, Resumo *, i) =
        NULL; // Inicializa cada posição com NULL
  }

  user->resumos = resumos;

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

int existUserResume(gpointer user, int indice){
  struct users *u = (struct users *)user;
  if (g_array_index(u->resumos, Resumo *, indice) ==
        NULL) return 0;
  else return 1;
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

void free_resumo(Resumo *r) {
    if (r == NULL) return;
    if (r->idsMusics) {
        for (int i = 0; r->idsMusics[i] != NULL; i++) {
            g_free(r->idsMusics[i]);
        }
        g_free(r->idsMusics);
    }
    if (r->artists) {
        for (int i = 0; i < r->num_musicas_diferentes; i++) {
            g_free(r->artists[i].artista);
        }
        g_free(r->artists);
    }

    if (r->albuns) {
        for (int i = 0; i < r->num_musicas_diferentes; i++) {
            g_free(r->albuns[i].categoria);
        }
        g_free(r->albuns);
    }

    if (r->generos) {
        for (int i = 0; i < r->num_musicas_diferentes; i++) {
            g_free(r->generos[i].categoria);
        }
        g_free(r->generos);
    }
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
    g_hash_table_destroy(u->musicsListening);
    if (u->resumos != NULL) {
        for (int i = 0; i < (int)u->resumos->len; i++) {
            Resumo *res = g_array_index(u->resumos, Resumo *, i);
            if (res != NULL) free_resumo(res);
        }
        g_array_free(u->resumos, FALSE);
    }
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
    remove_quotes(nomesGeneros[i]);
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