#include "artists.h"
#include "musics.h"
#include "queries.h"
#include "users.h"
#include "validation.h"
#include <artists.h>
#include <glib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_SIZE 1024

int primeiraAspa(char *line) {
  int i;
  for (i = 0; line[i]; i++) {
    if (line[i] == '"')
      return i;
  }
  return -1;
}

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

  GList *listMusics = NULL;
  fp = fopen(musicsPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseMusics(fp, &listMusics);
  }
  fclose(fp);

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
  while (getline(&line, &len, fp) != -1) {
    if (line[0] == '1') {
      query1(usersTable, line, i);
      i++;
    } else if (line[0] == '2') {
      if (!temAspas(line)) {
        query2(atoi(line + 2), NULL, artistsTable, listMusics, line, i);
        i++;
      } else {
        int primAspa = primeiraAspa(line);
        query2(atoi(line + 2), line + primAspa, artistsTable, listMusics, line,
               i);
        i++;
      }
    } else if (line[0] == '3') {
      // query3();
    }
  }
  fclose(fp);
  free(line);

  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);
  return 0;
}
