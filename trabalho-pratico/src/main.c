#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
#include "gestor_users.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

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

  GHashTable *artistsTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroyArtist);
  fp = fopen(artistsPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseArtists(fp, artistsTable);
  }
  fclose(fp);
  free(artistsPath);

  GHashTable *musicsTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroyMusic);
  fp = fopen(musicsPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseMusics(fp, musicsTable);
  }
  fclose(fp);
  free(musicsPath);

  GHashTable *usersTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, destroyUser);
  fp = fopen(usersPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseUsers(fp, usersTable);
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
      query3(minAge, maxAge, usersTable, musicsTable, i);
      i++;
    }
  }
  fclose(fp);
  free(line);
  free(country);
  g_hash_table_destroy(musicsTable);
  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);

  struct rusage r_usage;
  getrusage(RUSAGE_SELF, &r_usage);
  printf("Memory usage : %ld KB\n", r_usage.ru_maxrss);

  return 0;
}
