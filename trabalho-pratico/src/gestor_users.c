#include "gestor_users.h"
#include "validation.h"

void parseUsers(FILE *fp, GHashTable *usersTable, GHashTable *usersQ3Table,
                GHashTable *musicsTable) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  Users *user = NULL;
  UsersQ3 *userQ3 = NULL;
  char *idade;

  FILE *newFile = fopen("./resultados/users_erros.csv", "w");
  if (newFile == NULL) {
    perror("Erro ao abrir o ficheiro de erros");
    return;
  }

  getline(&line, &len, fp);
  while (getline(&line, &len, fp) != -1) {
    if (validateUsersLine(strdup(line), musicsTable)) {
      user = separateUsers(line);
      userQ3 = separateUsersQ3(line, pegarUserBirthDate(user));
      username = getUserUsername(user);
      idade = getUserQ3Age(userQ3);

      // Insere na HashTable usando o user->username como key
      g_hash_table_insert(usersTable, username, user);
      g_hash_table_insert(usersQ3Table, idade, userQ3);
    } else {
      // Escreve a linha inválida no ficheiro de erros
      fprintf(newFile, "%s", line);
    }
    // printf("a\n");
  }

  fclose(newFile);
  free(line);
}