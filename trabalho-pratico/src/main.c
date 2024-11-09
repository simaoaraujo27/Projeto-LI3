#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
#include "gestor_users.h"
#include "validation.h"
#include "utils.h"
#include "query3.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_SIZE 1024


/*
IDEIA: TIPO UM HISTOGRAMA

Lista ligada em que cada nodo tem o seguinte:
Nome do género;
Array com o número de likes para cada idade (pode ser um array dinâmico)


Depois é só percorrer a hashtable dos users, e pegar no liked_musics_id
Fazer um lookup na hashtable das músicas usando o id
Pegar no genre dessa música
Ir ao nodo da lista ligada correspondente a esse genre e incrementar a
posição da idade

*/

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

  GHashTable *artistsTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyArtist);

  gestorArtists *gestor = initGestorArtists("./resultados/artists_errors.csv", artistsTable);
    if (!gestor) {
        fprintf(stderr, "Failed to initialize gestorArtists\n");
        return EXIT_FAILURE;
    }
  

  fp = fopen(artistsPath, "r");
  if (fp) {
        parseArtists(fp, gestor);
        fclose(fp);
    } else {
        perror("Error opening artists file");
        freeGestorArtists(gestor);
        return EXIT_FAILURE;
    }
    free(artistsPath);

  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);
  fp = fopen(musicsPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseMusics(fp, musicsTable, artistsTable);
  }
  fclose(fp);
  free(musicsPath);

  GHashTable *usersTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyUser);

  fp = fopen(usersPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseUsers(fp, usersTable, musicsTable);
  }
  fclose(fp);
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
      query1(usersTable, line, i);
      i++;
    } else if (line[0] == '2') {
      if (!temAspas(line)) {
        query2(atoi(line + 2), NULL, artistsTable, musicsTable, line, i);
        i++;
      } else {
        firstOcorr = primeiraOcorr(line, '"');
        query2(atoi(line + 2), line + firstOcorr, artistsTable, musicsTable,
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
  freeGestorArtists(gestor);

  return 0;
}