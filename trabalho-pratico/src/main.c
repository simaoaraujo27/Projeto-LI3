#include "command_parser.c"
#include "gestor_users.c"
#include "gestor_artists.c"
#include "gestor_musics.c"
#include "validation.h"
#include <ctype.h>
#include <dirent.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *fp = NULL;

  if (argc < 2) {
    fp = stdin;
    fprintf(stderr, "Missing filename.\n");
    return 1;
  }
  char *dataset = argv[1];
  DIR *dir;
  struct dirent *ent;
  char *line = NULL;

  // Abre o diretório
  if ((dir = opendir(dataset)) != NULL) {
    // Percorre todos os arquivos no diretório
    while ((ent = readdir(dir)) != NULL) {
      // Ignora "." e ".."
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
        char destStr[50];
        strcpy(destStr, dataset);
        strcat(destStr,
               ent->d_name); // SÓ FUNCIONA SE METER A BARRA DEPOIS DA PASTA
        // ALTERNATIVA: char destStr[50] = "dataset/";
        fp = fopen(destStr, "r");
        if (!fp) {
          perror("Error");
          return EXIT_FAILURE;
        }

        size_t len = 0;

        if (!strcmp(ent->d_name, "artists.csv")) {
          Artists *artista = separateArtists(line);
          GHashTable *htArtistsValid = g_hash_table_new_full(
              g_str_hash, g_str_equal, free, (GDestroyNotify)destroyArtist);
          GHashTable *htArtistsInvalid = g_hash_table_new_full(
              g_str_hash, g_str_equal, free, (GDestroyNotify)destroyArtist);
          if (validateArtist(artista)) {
            // guardar na valid
          } else {
            // guardar na invalida
          }
        } else if (!strcmp(ent->d_name, "musics.csv")) {
          Musics *musica = separateMusics(line);
          GHashTable *htMusicsValid = g_hash_table_new_full(
              g_str_hash, g_str_equal, free, (GDestroyNotify)destroyMusic);
          GHashTable *htMusicsInvalid = g_hash_table_new_full(
              g_str_hash, g_str_equal, free, (GDestroyNotify)destroyMusic);
          if (validateMusic(musica)) {
            // guardar na valid
          } else {
            // guardar na invalida
          }

        } else if (!strcmp(ent->d_name, "users.csv")) {
          Users *user = separateUsers(line);
          GHashTable *htUsersValid = g_hash_table_new_full(
              g_str_hash, g_str_equal, free, (GDestroyNotify)destroyUser);
          GHashTable *htUsersInvalid = g_hash_table_new_full(
              g_str_hash, g_str_equal, free, (GDestroyNotify)destroyUser);
          if (validateUser(user)) {
            // guardar na valid
          } else {
            // guardar na invalida
          }
        }
      }
    }
    closedir(dir);
  } else {
    perror("Não foi possível abrir o diretório");
    return EXIT_FAILURE;
  }

  /* char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1) {
    if (strcmp(argv[1], "artists.csv") == 0) {
      Artists *artista;
      artista = separateArtists(line);
      if (!validateArtist(artista)) {

        continue;
      } else {
        continue;
      }
    } else if (strcmp(argv[1], "musics.csv") == 0) {
      Musics *musica;
      musica = separateMusics(line);
      if (!validateMusic(musica)) {

        continue;
      } else {
        continue;
      }
    } else if (strcmp(argv[1], "users.csv") == 0) {
      Users *user;
      user = separateUsers(line);
      GHashTable *hashTable = g_hash_table_new_full(
          g_str_hash, g_str_equal, free, (GDestroyNotify)destroyUser);
      g_hash_table_insert(hashTable, user->username, user);
      Users *userTable = g_hash_table_lookup(hashTable, user->username);
      printf("%s", userTable->username);

      if (!validateUser(user)) {
        continue;
      } else {
        continue;
      }

      g_hash_table_destroy(hashTable);
    }
  }
*/
  free(line);
  return 0;
}
