#include "gestor_users.h"
#include "utils.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct gestorUsers {
  FILE *errorsFile;
  GHashTable *usersTable;
  int *nUsers;
  GHashTable *query6Table;
};

gestorUsers *initGestorUsers(const char *errorsFilePath) {
  GHashTable *usersTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyUser);
  gestorUsers *gestorUser = malloc(sizeof(struct gestorUsers));
  if (!gestorUser)
    return NULL;

  gestorUser->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorUser->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorUser);
    return NULL;
  }

  gestorUser->usersTable = usersTable;
  gestorUser->nUsers = malloc(sizeof(int *));
  *(gestorUser->nUsers) = 0;

  GHashTable *query6Table =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  gestorUser->query6Table = query6Table;

  return gestorUser;
}

void freeGestorUsers(gestorUsers *gestorUser) {
  if (gestorUser) {
    if (gestorUser->errorsFile)
      fclose(gestorUser->errorsFile);
    g_hash_table_destroy(gestorUser->usersTable);
    free(gestorUser->nUsers);
    g_hash_table_destroy(gestorUser->query6Table);
    free(gestorUser);
  }
}

void parserUser(char *line, gestorMusics *gestorMusic, FILE *errorsFile,
                GHashTable *usersTable, int *nUsers) {
  char *copia = strdup(line);
  Users *user;
  char *username = NULL;
  if (validateUsersLine(copia, gestorMusic)) {
    (*nUsers)++;
    user = separateUsers(line);
    username = getUserUsername(user);
    g_hash_table_insert(usersTable, strdup(username), user);
  } else {
    fprintf(errorsFile, "%s", line);
  }
  free(copia);
  if (username != NULL)
    free(username);
}

int GestorUsers(gestorUsers *gestorUser, gestorMusics *gestorMusic,
                char *usersPath) {
  FILE *fp = fopen(usersPath, "r");
  if (fp) {
    char *line = NULL;
    size_t len = 0;
    assert(getline(&line, &len, fp) != -1);

    while (getline(&line, &len, fp) != -1) {
      parserUser(line, gestorMusic, gestorUser->errorsFile,
                 gestorUser->usersTable, gestorUser->nUsers);
    }
    free(line);
    fclose(fp);
  } else {
    perror("Error opening users file");
    return 0;
  }
  return 1;
}

gboolean lookUpUsersHashTable(gestorUsers *gestorUser, char *line,
                              gpointer *value, gpointer *orig_key) {
  gboolean found = g_hash_table_lookup_extended(gestorUser->usersTable, line,
                                                value, orig_key);
  return found;
}

void processAllUsers(Gestores *gestor, NodoMusica **lista) {
  int IDADE_INICIAL = 150;
  guint idade_max = IDADE_INICIAL;
  GHashTableIter iter;
  gpointer hash_key, hash_value;
  g_hash_table_iter_init(&iter, pegarGestorUser(gestor)->usersTable);
  while (g_hash_table_iter_next(&iter, &hash_key, &hash_value)) {
    char *birthDate = getUserBirthDate(hash_value);
    char *age = calculate_age_str(birthDate);
    int userAge = atoi(age);
    char *liked_musics_id = getUserLikedMusicsId(hash_value);
    free(birthDate);
    free(age);
    removeFstLast(liked_musics_id);
    char *music_id = strtok(liked_musics_id, ", ");
    while (music_id != NULL) {
      if (music_id[0] == '\'')
        music_id++;
      if (music_id[strlen(music_id) - 1] == '\'')
        music_id[strlen(music_id) - 1] = '\0';
      gpointer music_value;
      gpointer orig_music_key;
      gboolean found = lookUpMusicsHashTable(pegarGestorMusic(gestor), music_id,
                                             &music_value, &orig_music_key);
      if (found) {
        char *genre = getMusicGenre(orig_music_key);
        *lista = adicionar_like(*lista, genre, userAge, &idade_max);
        free(genre);
      }
      music_id = strtok(NULL, ", ");
    }
    free(liked_musics_id);
  }
}

int getNUsers(gestorUsers *gestorUser) {
  int *i = gestorUser->nUsers;
  return *i;
}

void preencheMatriz(int **matrizClassificaoMusicas, int numGeneros,
                    char **nomesGeneros, gestorUsers *gestorUsers,
                    char **idsUtilizadores) {
  GHashTableIter iter;
  gpointer key1, value1;
  g_hash_table_iter_init(&iter, gestorUsers->usersTable);
  int i = 0;
  while (g_hash_table_iter_next(&iter, &key1, &value1)) {
    Users *user = (Users *)value1;
    char *username = getUserUsername(value1);
    idsUtilizadores[i] = strdup(username);
    preencheLinhaMatriz(matrizClassificaoMusicas, i, user, numGeneros,
                        nomesGeneros);
    free(username);
    i++;
  }
}

gboolean lookUpQuery6Table(gestorUsers *gestorUser, char *line, gpointer *value,
                           gpointer *orig_key) {
  gboolean found = g_hash_table_lookup_extended(gestorUser->query6Table, line,
                                                value, orig_key);
  return found;
}

void setQuery6Table(char *line, gestorUsers *gestorUsers) {
  if (line[0] == '6') {
    char *key;
    char *value;
    if (line[1] == 'S') {
      line++;
    }
    line += 2;
    key = strndup(line, 8);
    value = strndup(line + 9, 4);
    gpointer value1 = NULL;
    gpointer orig_key1 = NULL;
    gboolean found = lookUpQuery6Table(gestorUsers, key, &value1, &orig_key1);

    if (found) {
      char *anoAntigo = (char *)value1;
      char *anoNovo = malloc(strlen(anoAntigo) + strlen(value) + 1);

      strcpy(anoNovo, anoAntigo);
      strcat(anoNovo, value);
      g_hash_table_replace(gestorUsers->query6Table, key, anoNovo);
      free(value);
    } else {
      g_hash_table_insert(gestorUsers->query6Table, key, value);
    }
  }
}
