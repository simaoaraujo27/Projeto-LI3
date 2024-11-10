#include "gestor_users.h"
#include "validation.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct gestorUsers {
  FILE *errorsFile;
  GHashTable *usersTable;
};

gestorUsers *initGestorUsers(const char *errorsFilePath,
                             GHashTable *usersTable) {
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
  return gestorUser;
}

// Função para liberar a estrutura gestorMusics e seus recursos
void freeGestorUsers(gestorUsers *gestorUser) {
  if (gestorUser) {
    if (gestorUser->errorsFile)
      fclose(gestorUser->errorsFile);
    free(gestorUser);
  }
}

void parseUsers(FILE *fp, gestorUsers *gestorUser, gestorMusics *gestorMusic) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  Users *user = NULL;

  assert(getline(&line, &len, fp) != -1);
  while (getline(&line, &len, fp) != -1) {
    char *copia = strdup(line);
    if (validateUsersLine(copia, gestorMusic)) {
      user = separateUsers(line);
      username = getUserUsername(user);

      // Insere na HashTable usando o user->username como key
      g_hash_table_insert(gestorUser->usersTable, username, user);
    } else {
      fprintf(gestorUser->errorsFile, "%s", line);
    }

    free(copia);
  }

  free(line);
}

GHashTable *getUsersTable(gestorUsers *gestorUser) {
  return gestorUser->usersTable;
}