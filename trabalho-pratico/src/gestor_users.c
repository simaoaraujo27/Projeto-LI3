#include "gestor_users.h"

void parseUsers(FILE *fp, GHashTable *usersTable, GHashTable *usersQ3Table) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  Users *user = NULL;
  UsersQ3 *userQ3 = NULL;
  char *idade;
  while (getline(&line, &len, fp) != -1) {
    user = separateUsers(line);
    userQ3 = separateUsersQ3(line, pegarUserBirthDate(user));
    username = getUserUsername(user);
    idade = getUserQ3Age(userQ3);

    // Insere na HashTable usando o user->username como key
    g_hash_table_insert(usersTable, username, user);
    g_hash_table_insert(usersQ3Table, idade, userQ3);
  }
  //destroyUser(user);
  free(username);
  free(line);
}
