#include "artists.h"
#include "musics.h"
#include "users.h"
#include "validation.h"
#include <artists.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_SIZE 1024

int main(int argc, char **argv) {
  FILE *fp = NULL;

  if (argc < 2) {
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

  g_hash_table_destroy(artistsTable);
  return 0;
}
