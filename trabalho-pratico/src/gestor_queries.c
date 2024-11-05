#include "gestor_queries.h"
#include "artists.h"
#include "gestor_artists.h"
#include "gestor_prints.h"
#include "musics.h"
#include "users.h"
#include "utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void query1(GHashTable *usersTable, char *line, int i) {
  line = line + 2;
  line[strlen(line) - 1] = '\0';

  // Cria o ficheiro e guarda-o na pasta resultados
  FILE *newFile;
  char *path = "./resultados/commandx-output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d-output.txt", i);
  newFile = fopen(new, "w");
  gpointer value;
  gpointer orig_key;

  gboolean found =
      g_hash_table_lookup_extended(usersTable, line, &value, &orig_key);

  if (found) {
    char *email = getUserEmail(orig_key);
    char *firstName = getUserFirstName(orig_key);
    char *lastName = getUserLastName(orig_key);
    char *age = calculate_age(getUserBirthDate(orig_key));
    char *country = getUserCountry(orig_key);

    int total_len = strlen(email) + strlen(firstName) + strlen(lastName) +
                    strlen(age) + strlen(country) + 5; // 5 para os ';' e o '\0'
    char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    // Concatenar as strings, separando-as por ;
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s;%s\n", email, firstName,
             lastName, age, country);

    fprintf(newFile, "%s", new_str);
    fclose(newFile);

    free(email);
    free(firstName);
    free(lastName);
    free(age);
    free(country);
  }
}

void query2(int numeroArtistas, char *country, GHashTable *artistsTable,
            GHashTable *musicsTable, char *line, int i) {
  FILE *newFile;
  char *path = "./resultados/commandx-output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d-output.txt", i);
  newFile = fopen(new, "w");

  GHashTableIter iter;
  g_hash_table_iter_init(&iter, musicsTable);
  gpointer key1, value1;
  GList *listaResposta = NULL;
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Musics *music = (Musics *)value1;
    char *artistId = getMusicArtistId(music);
    remove_quotes(artistId);
    removeFstLast(artistId);
    int duracao = getMusicDuration(music);
    char *key;
    gpointer value;
    gpointer orig_key;
    int l = strlen(artistId);
    for (int j = 0; j < l; j += 12) {
      if (j == 0)
        artistId = artistId + 1;
      else
        artistId = artistId + 3;
      key = strdup(strsep(&artistId, "'"));
      if (g_hash_table_lookup_extended(artistsTable, key, &orig_key, &value)) {
        increment_artist_discografia(value, duracao, &listaResposta,
                                     numeroArtistas, country);
      }
    }
  }
  print(&listaResposta, numeroArtistas, newFile);
  colocaZero(artistsTable);
  g_list_free(listaResposta);
}

typedef struct GenreList {
  char *genre;
  int likes;
} GenreList;

GenreList *createNode(char *genre) {
  GenreList *newNode = (GenreList *)malloc(sizeof(GenreList));
  if (newNode == NULL) {
    return NULL;
  }
  newNode->genre = (char *)malloc(strlen(genre) + 1);
  if (newNode->genre == NULL) {
    return NULL;
  }
  strcpy(newNode->genre, genre);
  newNode->likes = 1;
  return newNode;
}

void printQuerie3(GList **listaResposta, FILE *newFile) {
  GList *node = *listaResposta;
  char *genero;
  int likes;
  char *new_str;

  while (node != NULL) {
    GenreList *currentGenre = (GenreList *)node->data;
    genero = currentGenre->genre;
    likes = currentGenre->likes;
    int total_len = strlen(genero) + 4 + 1;           // 4 para os ';' e o '\0'
    new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    snprintf(new_str, total_len + 1, "%s;%d\n", genero, likes);

    if (node->next == NULL)
      fprintf(newFile, "%s", new_str);
    else
      fprintf(newFile, "%s\n", new_str);
    node = node->next;
  }
  fclose(newFile);
}

int compare_likes(gconstpointer a, gconstpointer b) {
  const GenreList *genre1 = a;
  const GenreList *genre2 = b;

  return genre2->likes - genre1->likes;
}

void query3(int minAge, int maxAge, GHashTable *usersTable,
            GHashTable *musicsTable, int i) {

  FILE *newFile;
  char *path = "./resultados/commandx-output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  -snprintf(new, strlen(path) + 10, "./resultados/command%d-output.txt", i);
  newFile = fopen(new, "w");

  GHashTableIter iter;
  g_hash_table_iter_init(&iter, usersTable);
  gpointer key1, value1;
  GList *listaResposta = NULL;
  Musics *music;
  char *username;
  char *birthdate;
  char *likedMusics;
  int age = 0;
  int continua = 1;
  char *key;
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Users *user = (Users *)value1;
    username = getUserUsername(user);
    birthdate = getUserBirthDate(user);
    age = atoi(calculate_age(birthdate));
    gpointer value;
    gpointer orig_key;
    if (age >= minAge && age <= maxAge) {
      likedMusics = getUserLikedMusicsId(user);
      removeLast(likedMusics);
      removeFstLast(likedMusics);
      removeFstLast(likedMusics);
      int l = strlen(likedMusics);
      char *genero;
      for (int j = 0; j < l; j += 12) {
        if (j == 0)
          likedMusics = likedMusics + 1;
        else
          likedMusics = likedMusics + 3;
        key = strdup(strsep(&likedMusics, "'"));
        if (g_hash_table_lookup_extended(musicsTable, key, &orig_key, &value)) {
          music = (Musics *)value;       // pega na musica encontrada
          genero = getMusicGenre(music); // pega no genero
          remove_quotes(genero);

          for (GList *node = listaResposta; node != NULL; node = node->next) {
            GenreList *currentGenre = (GenreList *)node->data;
            if (!strcmp(genero, currentGenre->genre)) {
              currentGenre->likes++;
              continua = 0;
            }
          }
          if (continua) {
            GenreList *newNode = createNode(genero);
            listaResposta = g_list_prepend(listaResposta, newNode);
          }
        }
      }
    }
  }
  listaResposta = g_list_sort(listaResposta, compare_likes);
  printQuerie3(&listaResposta, newFile);
  g_list_free(listaResposta);
  free(username);
  free(birthdate);
  free(likedMusics);
  free(key);
  free(orig_key1);
  free(value1);
  destroyMusic(music);
}
