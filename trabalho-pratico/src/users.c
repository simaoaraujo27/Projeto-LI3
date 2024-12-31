#include "users.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artistaAudicoes {
  char *artista;    // artista
  guint tempo;      // tempo de reprodução em segundos
  guint numMusicas; // número de músicas diferentes ouvidas desta artista
};

struct categoriaTempo {
  char *categoria; // album ou género
  guint tempo;     // tempo de reprodução em segundos
};

struct resumo {
  GArray *idsMusics;
  GList *artists; // ordenar
  GList *albuns;  // ordenar
  GList *generos; // ordenar
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

GArray *initIdsMusics() {
  GArray *idsMusics = g_array_new(FALSE, FALSE, sizeof(char *));
  g_array_set_size(idsMusics, 10);
  for (int i = 0; i < (int)idsMusics->len; i++) {
    g_array_index(idsMusics, char *, i) =
        NULL; // Inicializa cada posição com NULL
  }

  return idsMusics;
}

Resumo *initResumo() {
  Resumo *res = (Resumo *)malloc(sizeof(Resumo));
  res->idsMusics = initIdsMusics();
  res->artists = NULL;
  res->albuns = NULL;
  res->generos = NULL;
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

int elemUserResumeIdsMusics(Resumo *res, char *musicId) {
  GArray *idsMusics = res->idsMusics;
  char *musicPercorrer = NULL;
  for (int i = 0; (int)idsMusics->len; i++) {
    musicPercorrer = g_array_index(idsMusics, char *, i);
    if(musicPercorrer == NULL) return 0;
    if (!strcmp(musicId, musicPercorrer))
      return 1;
  }
  return 0;
}
/*
// FAZER ESTA
void insertUserResumeIdsMusics(Resumo *res, char *musicId){
  GArray *idsMusics = res->idsMusics;
  int tamanho = idsMusics->len;
  int tamanhoMax = idsMusics->alloc;
  if (tamanho >= tamanhoMax){
    g_array_set_size(idsMusics, (guint)(tamanhoMax + 1));
  }
    g_array_index(idsMusics, char *, tamanho) = musicId;
  res->idsMusics = idsMusics;
}
*/
int updateUserResumeArtists(Resumo *res, char *artistId, int duracao,
                            char *musicId) {
  int add = 0;
  GList *a = res->artists;
  while (a != NULL) {
    ArtistaTempo *artist = (ArtistaTempo *)a->data;
    if (strcmp(artist->artista, artistId) == 0) {
      artist->tempo += duracao;
      if (!elemUserResumeIdsMusics(res, musicId)) {
        g_array_append_val(res->idsMusics, musicId);
        artist->numMusicas++;
        add = 1;
      }
      return add;
    }
    a = a->next;
  }
  ArtistaTempo *newArtist = (ArtistaTempo *)malloc(sizeof(ArtistaTempo));
  newArtist->artista = artistId;
  newArtist->tempo = duracao;
  newArtist->numMusicas = 0;
  if (!elemUserResumeIdsMusics(res, musicId)) {
    g_array_append_val(res->idsMusics, musicId);
    newArtist->numMusicas++;
    add = 1;
  }
  a = g_list_prepend(a, newArtist);
  res->artists = a;
  return add;
}

void updateUserResumeAlbuns(Resumo *res, char *albumId, int duracao) {
  GList *a = res->albuns;
  while (a != NULL) {
    AlbumTempo *album = (AlbumTempo *)a->data;
    if (strcmp(album->categoria, albumId) == 0) {
      album->tempo += duracao;
      return;
    }
    a = a->next;
  }
  AlbumTempo *newAlbum = (AlbumTempo *)malloc(sizeof(AlbumTempo));
  newAlbum->categoria = albumId;
  newAlbum->tempo = duracao;
  a = g_list_prepend(a, newAlbum);
  res->albuns = a;
}

void updateUserResumeGeneros(Resumo *res, char *gen, int duracao) {
  GList *g = res->generos;
  while (g != NULL) {
    GeneroTempo *genero = (GeneroTempo *)g->data;
    if (strcmp(genero->categoria, gen) == 0) {
      genero->tempo += duracao;
      return;
    }
    g = g->next;
  }
  GeneroTempo *newGenero = (GeneroTempo *)malloc(sizeof(GeneroTempo));
  newGenero->categoria = gen;
  newGenero->tempo = duracao;
  g = g_list_prepend(g, newGenero);
  res->generos = g;
}

void updateUserResume(gpointer u, int year, int duracao, char *musicId,
                      char *artistId, char *albumId, char *genero, int dia,
                      int hora) {
  if (u == NULL)
    return;
  Users *user = (Users *)u;
  if (user == NULL)
    return;
  GArray *resumos = user->resumos;

  // Verifica o tamanho atual da duração por semana
  if (resumos == NULL)
    return;
  int tamanho = resumos->len;
  int indice = 2024 - year;
  // printf("%d %d\n",tamanho, indice);

  // Ajusta o tamanho do array se necessário
  if (indice >= tamanho) {
    g_array_set_size(resumos, (guint)(indice + 1));

    // Inicializa as novas posições com NULL
    for (int i = tamanho; i <= indice; i++) {
      g_array_index(resumos, Resumo *, i) = NULL;
    }
    tamanho = resumos->len;
  }

  Resumo *res = g_array_index(resumos, Resumo *, indice);
  if (res == NULL) {
    res = initResumo();
  }
  res->listening_time += duracao;
  int add = updateUserResumeArtists(res, artistId, duracao, musicId);
  res->num_musicas_diferentes += add;
  updateUserResumeAlbuns(res, albumId, duracao);
  updateUserResumeGeneros(res, genero, duracao);
  res->dias[dia]++;
  res->horas[hora] += duracao;
  g_array_index(resumos, Resumo *, indice) = res;

  // Retorna o novo valor da duração para a semana
  // return g_array_index(durationPerWeek, int, semana);
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
  for (int i = 0; i < 7; i++) {
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

int existUserResume(gpointer user, int indice) {
  struct users *u = (struct users *)user;
  if (g_array_index(u->resumos, Resumo *, indice) == NULL)
    return 0;
  else
    return 1;
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

int getUserResumoListeningTime(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = u->resumos;
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  return res->listening_time;
}

int getUserResumoNumMusicasDiferentes(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = u->resumos;
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  return res->num_musicas_diferentes;
}

char *getUserResumoArtists(gpointer user, int year, int N, int temS) {
  if (N >= 0) {
    struct users *u = (struct users *)user;
    GArray *resumos = u->resumos;
    int indice = 2024 - year;
    Resumo *res = g_array_index(resumos, Resumo *, indice);
    GList *a = res->artists;
    int duracao = 0, numeroMusicas = 0;
    char *art = NULL;
    while (a != NULL) {
      ArtistaTempo *artist = (ArtistaTempo *)a->data;
      if ((int)artist->tempo > duracao ||
          ((int)artist->tempo == duracao && (strcmp(artist->artista, art) < 0))) {
        duracao = (int)artist->tempo;
        numeroMusicas = (int)artist->numMusicas;
        if (art != NULL)
          free(art);
        art = strdup(artist->artista);
      }
      a = a->next;
    }
    char *duracaoStr = malloc(sizeof(char)* 16);
    converterParaTempo(duracao, duracaoStr);
    char *numeroMusicasStr = intToString(numeroMusicas);
    int total_len = strlen(art) + strlen(numeroMusicasStr) + strlen(duracaoStr) +
                  3; // 2 para os ';' ou '=' e o '\0'
    char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    if (temS){
      snprintf(new_str, total_len + 1, "%s=%s=%s\n", art, numeroMusicasStr, duracaoStr);
    }else{
      snprintf(new_str, total_len + 1, "%s;%s;%s\n", art, numeroMusicasStr, duracaoStr);
    }
    return new_str;
  }
  return NULL;
} 

char *getUserResumoGenero(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = u->resumos;
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  GList *g = res->generos;
  int duracao = 0;
  char *gen = NULL;
  while (g != NULL) {
    GeneroTempo *genero = (GeneroTempo *)g->data;
    if ((int)genero->tempo > duracao ||
        ((int)genero->tempo == duracao && (strcmp(genero->categoria, gen) < 0))) {
      duracao = (int)genero->tempo;
      if (gen != NULL)
        free(gen);
      gen = strdup(genero->categoria);
    }
    g = g->next;
  }
  return gen;
}

char *getUserResumoAlbum(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = u->resumos;
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  GList *a = res->albuns;
  int duracao = 0;
  char *alb = NULL;
  while (a != NULL) {
    AlbumTempo *album = (AlbumTempo *)a->data;
    if ((int)album->tempo > duracao ||
        ((int)album->tempo == duracao && (strcmp(album->categoria, alb) < 0))) {
      duracao = (int)album->tempo;
      if (alb != NULL)
        free(alb);
      alb = strdup(album->categoria);
    }
    a = a->next;
  }
  return alb;
}

int getUserResumoDay(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = u->resumos;
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  int max = res->dias[0], maxInd = 0;
  for (int i = 1; i < 366; i++) {
    if (res->dias[i] > max) {
      max = res->dias[i];
      maxInd = i;
    }
  }
  return maxInd;
}

int getUserResumoHora(gpointer user, int year) {
  struct users *u = (struct users *)user;
  GArray *resumos = u->resumos;
  int indice = 2024 - year;
  Resumo *res = g_array_index(resumos, Resumo *, indice);
  int max = res->horas[0], maxInd = 0;
  for (int i = 1; i < 24; i++) {
    if (res->horas[i] > max) {
      max = res->horas[i];
      maxInd = i;
    }
  }
  return maxInd;
}

void free_resumo(Resumo *r) {
  if (r == NULL)
    return;

  // Liberar idsMusics
  if (r->idsMusics) {
    for (int i = 0; i < (int)r->idsMusics->len; i++) {
      char *musicId = g_array_index(r->idsMusics, char *, i);
      g_free(musicId); // Liberar cada string individual
    }
    g_array_free(r->idsMusics, TRUE);
  }

  // Liberar a lista de artists (GList de ArtistaAudicoes)
  if (r->artists) {
    g_list_free_full(r->artists, (GDestroyNotify)g_free);
  }

  // Liberar a lista de albuns (GList de CategoriaTempo)
  if (r->albuns) {
    g_list_free_full(r->albuns, (GDestroyNotify)g_free);
  }

  // Liberar a lista de generos (GList de CategoriaTempo)
  if (r->generos) {
    g_list_free_full(r->generos, (GDestroyNotify)g_free);
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
        if (res != NULL)
          free_resumo(res);
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