#include "gestor_users.h"
#include "validation.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura gestorUsers
struct gestorUsers {
  FILE *errorsFile;       // Arquivo onde erros serão registrados
  GHashTable *usersTable; // Hashtable para armazenar os users
};

// Função para inicializar a estrutura gestorUsers
gestorUsers *initGestorUsers(const char *errorsFilePath,
                             GHashTable *usersTable) {
  gestorUsers *gestorUser = malloc(sizeof(struct gestorUsers));
  if (!gestorUser)
    return NULL;

  // Abre o arquivo de erros em modo de escrita
  gestorUser->errorsFile = fopen(errorsFilePath, "w");
  if (!gestorUser->errorsFile) {
    perror("Erro ao abrir o ficheiro de erros");
    free(gestorUser);
    return NULL;
  }

  // Inicializa a hashtable de users
  gestorUser->usersTable = usersTable;
  return gestorUser;
}

// Função para libertar a estrutura gestorUsers e os seus recursos
void freeGestorUsers(gestorUsers *gestorUser) {
  if (gestorUser) {
    if (gestorUser->errorsFile)
      fclose(gestorUser->errorsFile); // Fecha o arquivo de erros
    free(gestorUser);                 // Liberta a memória da estrutura
  }
}

// Função para processar o arquivo de users e inserir os dados na hashtable
void parseUsers(FILE *fp, gestorUsers *gestorUser, gestorMusics *gestorMusic) {
  char *line = NULL;
  size_t len = 0;
  char *username;
  Users *user = NULL;

  // Ignora a primeira linha do arquivo (cabeçalho)
  assert(getline(&line, &len, fp) != -1);

  // Lê o arquivo linha por linha
  while (getline(&line, &len, fp) != -1) {
    char *copia = strdup(line); // Faz uma cópia segura da linha

    // Valida a linha com base nas regras definidas
    if (validateUsersLine(copia, gestorMusic)) {
      user = separateUsers(
          line); // Se a linha for válida, separa os dados do user

      username = getUserUsername(user); // Obtém o nome do user

      // Insere o user na hashtable usando o username como chave
      g_hash_table_insert(gestorUser->usersTable, username, user);
    } else {
      // Se a linha for inválida, escreve no arquivo de erros
      fprintf(gestorUser->errorsFile, "%s", line);
    }
    free(copia); // Liberta a memória da cópia da linha
  }
  free(line); // Liberta a memória da linha lida
}

// Função para obter a hashtable dos users
GHashTable *getUsersTable(gestorUsers *gestorUser) {
  return gestorUser->usersTable;
}
