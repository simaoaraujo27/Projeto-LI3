#include "gestor_users.h"
#include "parsers.h"
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
int GestorUsers(FILE *fp, gestorUsers *gestorUser, gestorMusics *gestorMusic,
               char *usersPath) {
  // Abre o arquivo de users e carrega os dados
  fp = fopen(usersPath, "r");
  if (fp) {
    char *line = NULL;
    size_t len = 0;
 

    // Ignora a primeira linha do arquivo (cabeçalho)
    assert(getline(&line, &len, fp) != -1);

    // Lê o arquivo linha por linha
    while (getline(&line, &len, fp) != -1) {
      parserUser(line, gestorMusic, gestorUser->errorsFile,
                 gestorUser->usersTable);
    }
    free(line); // Liberta a memória da linha lida

    fclose(fp);
  } else {
    perror("Error opening users file");
    return 0;
  }
  free(usersPath); // Liberta a memória do path dos users
  return 1;
}

// Função para obter a hashtable dos users
GHashTable *getUsersTable(gestorUsers *gestorUser) {
  return gestorUser->usersTable;
}
