#include "gestor_users.h"

void parseUsers(FILE *fp, GHashTable *usersTable) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  while (getline(&line, &len, fp) != -1) {
    Users *user = separateUsers(line);
    username = getUserUsername(user);
    // Insere na HashTable usando o user->username como key
    g_hash_table_insert(usersTable, username, user);
  }
  free(username);
  free(line);
}
