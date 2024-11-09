#include "gestor_users.h"
#include "validation.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct gestorUsers {
  FILE *errorsFile;
  GHashTable *usersTable;
};

gestorUsers *initGestorUsers(const char *errorsFilePath,
                             GHashTable *usersTable) {
  gestorUsers *gestorUser = malloc(sizeof(gestorUser));
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

  getline(&line, &len, fp);
  while (getline(&line, &len, fp) != -1) {
    if (validateUsersLine(strdup(line), gestorMusic)) {
      user = separateUsers(line);
      username = getUserUsername(user);

      // Insere na HashTable usando o user->username como key
      g_hash_table_insert(gestorUser->usersTable, username, user);
    } else {
      fprintf(gestorUser->errorsFile, "%s", line);
    
    }
  }

  free(line);
}

GHashTable *getUsersTable(gestorUsers *gestorUser) {
  return gestorUser->usersTable;
}