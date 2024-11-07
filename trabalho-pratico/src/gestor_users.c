#include "gestor_users.h"


// todas as funções que são referentes a varios users ficam aqui
// no users.c 
// nas funções passar esta struct em vez da estrutura de dados
struct gestorUsers{
  GHashTable *usersTable;
};

void parseUsers(FILE *fp, GHashTable *usersTable) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  Users *user = NULL;
  while (getline(&line, &len, fp) != -1) {
    user = separateUsers(line);
    username = getUserUsername(user);

    // Insere na HashTable usando o user->username como key
    g_hash_table_insert(usersTable, username, user);
  }
  free(line);
}
