#include "gestor_users.h"
#include "validation.h"

void parseUsers(FILE *fp, GHashTable *usersTable, GHashTable *musicsTable) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  Users *user = NULL;

  FILE *newFile = fopen("./resultados/users_erros.csv", "w");
  if (newFile == NULL) {
    perror("Erro ao abrir o ficheiro de erros");
    return;
  }

  getline(&line, &len, fp);
  while (getline(&line, &len, fp) != -1) {
    if (validateUsersLine(strdup(line), musicsTable)) {
      user = separateUsers(line);

      username = getUserUsername(user);

      // Insere na HashTable usando o user->username como key
      g_hash_table_insert(usersTable, username, user);

    } else {
      // Escreve a linha inválida no ficheiro de erros
      fprintf(newFile, "%s", line);
    }
    // printf("a\n");
  }

  fclose(newFile);
  free(line);
}