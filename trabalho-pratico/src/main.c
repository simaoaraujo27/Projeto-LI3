#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
#include "gestor_users.h"
#include "query1.h"
#include "query2.h"
#include "query3.h"
#include "utils.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_SIZE 1024

int main(int argc, char **argv) {
  FILE *fp = NULL;

  if (argc < 3) {
    fp = stdin;
    fprintf(stderr, "Error: Missing filename\n");
    return EXIT_FAILURE;
  }

  char *path = argv[1];

  char *artistsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *musicsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *usersPath = malloc(MAX_PATH_SIZE * sizeof(char));

  snprintf(artistsPath, MAX_PATH_SIZE, "%s/%s", path, "artists.csv");
  snprintf(musicsPath, MAX_PATH_SIZE, "%s/%s", path, "musics.csv");
  snprintf(usersPath, MAX_PATH_SIZE, "%s/%s", path, "users.csv");

  // Inicializar gestorArtists and GHashTableArtist
  GHashTable *artistsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyArtist);

  gestorArtists *gestorArtists =
      initGestorArtists("./resultados/artists_errors.csv", artistsTable);
  if (!gestorArtists) {
    fprintf(stderr, "Failed to initialize gestorArtists\n");
    return EXIT_FAILURE;
  }

  fp = fopen(artistsPath, "r");
  if (fp) {
    parseArtists(fp, gestorArtists);
    fclose(fp);
  } else {
    perror("Error opening artists file");
    freeGestorArtists(gestorArtists);
    return EXIT_FAILURE;
  }
  free(artistsPath);

  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);

  // Inicializar gestorMusics and GHashTableMusic
  gestorMusics *gestorMusics =
      initGestorMusics("./resultados/musics_errors.csv", musicsTable);
  if (!gestorMusics) {
    fprintf(stderr, "Failed to initialize gestorMusics\n");
    return EXIT_FAILURE;
  }

  fp = fopen(musicsPath, "r");
  if (fp) {
    parseMusics(fp, gestorMusics, gestorArtists);
    fclose(fp);
  } else {
    perror("Error opening musics file");
    freeGestorMusics(gestorMusics);
    return EXIT_FAILURE;
  }
  free(musicsPath);

  // Inicializar gestorUsers and GHashTableUser
  GHashTable *usersTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyUser);

  gestorUsers *gestorUsers =
      initGestorUsers("./resultados/musics_errors.csv", usersTable);
  if (!gestorUsers) {
    fprintf(stderr, "Failed to initialize gestorUsers\n");
    return EXIT_FAILURE;
  }

  fp = fopen(usersPath, "r");
  if (fp) {
    parseUsers(fp, gestorUsers, gestorMusics);
    fclose(fp);
  } else {
    perror("Error opening users file");
    freeGestorUsers(gestorUsers);
    return EXIT_FAILURE;
  }
  free(usersPath);

  char *txt = argv[2];
  fp = fopen(txt, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  }

  char *line = NULL;
  size_t len = 0;
  int i = 1;
  int numeroArtist = 0;
  char *country;
  int firstOcorr, minAge, maxAge;
  int IDADE_INICIAL = 120;

  NodoMusica *lista = NULL;
  guint idade_max =
      IDADE_INICIAL; // Inicialize a idade máxima como IDADE_INICIAL

  GHashTableIter iter;
  gpointer hash_key, hash_value;
  g_hash_table_iter_init(&iter, usersTable);

  while (g_hash_table_iter_next(&iter, &hash_key, &hash_value)) {
    char *birthDate = getUserBirthDate(hash_value);
    char *age = calculate_age_str(birthDate);

    int userAge = atoi(age);
    char *liked_musics_id = getUserLikedMusicsId(hash_value);

    removeFstLast(liked_musics_id);
    char *music_id = strtok(liked_musics_id, ", ");
    while (music_id != NULL) {
      // Remove as aspas simples
      if (music_id[0] == '\'') {
        music_id++;
      }
      if (music_id[strlen(music_id) - 1] == '\'') {
        music_id[strlen(music_id) - 1] = '\0';
      }

      gpointer music_value;
      gpointer orig_music_key;

      gboolean found = g_hash_table_lookup_extended(
          musicsTable, music_id, &music_value, &orig_music_key);

      if (found) {
        char *genre = getMusicGenre(orig_music_key);
        // Atualize a lista e a idade máxima se necessário
        lista = adicionar_like(lista, genre, userAge, &idade_max);
      }

      music_id = strtok(NULL, ", ");
    }
  }

  while (getline(&line, &len, fp) != -1) {
    if (line[0] == '1') {
      query1(gestorUsers, line, i);
      i++;
    } else if (line[0] == '2') {
      if (!temAspas(line)) {
        query2(atoi(line + 2), NULL, gestorArtists, gestorMusics, line, i);
        i++;
      } else {
        firstOcorr = primeiraOcorr(line, '"');
        query2(atoi(line + 2), line + firstOcorr, gestorArtists, gestorMusics,
               line, i);
        i++;
      }
    } else if (line[0] == '3') {
      minAge = atoi(line + 2);
      firstOcorr = primeiraOcorr(line + 2, ' ');
      maxAge = atoi(line + 2 + firstOcorr);
      query3(minAge, maxAge, lista, i);
      i++;
    }
  }
  fclose(fp);
  free(line);
  free(country);
  g_hash_table_destroy(musicsTable);
  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);
  liberar_lista(lista);
  freeGestorArtists(gestorArtists);
  freeGestorMusics(gestorMusics);

  return 0;
}