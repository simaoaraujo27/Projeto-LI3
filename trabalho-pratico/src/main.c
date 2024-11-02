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
  int numeroQuerie = 0;
  int numeroArtist = 0;
  while (getline(&line, &len, fp) != -1) {
    numeroQuerie = atoi(strsep(&line, " "));
    if (numeroQuerie == 1) {
      query1(usersTable, line, i);
      i++;
    } else if (numeroQuerie == 2) {
      if (!temAspas(line)) {
        //query2(atoi(line), NULL, artistsTable, listMusics, line);
      } else {
        numeroArtist = atoi(strsep(&line, " "));
        printf("%d\n", numeroArtist);
        query2(numeroArtist, line, artistsTable, listMusics, line);
      }
    } else if (numeroQuerie == 3) {
      // query3();
      printf("a");
    }
  }
  fclose(fp);
  free(line);

  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);
  return 0;
}
