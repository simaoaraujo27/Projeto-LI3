#include "gestor_users.h"
#include "utils.h"
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
gestorUsers *initGestorUsers(const char *errorsFilePath) {

  // Inicializa a hashtable para users
  GHashTable *usersTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyUser);
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
    g_hash_table_destroy(gestorUser->usersTable);
    free(gestorUser); // Liberta a memória da estrutura
  }
}

void parserUser(char *line, gestorMusics *gestorMusic, FILE *errorsFile,
                GHashTable *usersTable) {
  char *copia = strdup(line); // Faz uma cópia segura da linha
  Users *user;
  char *username;
  // Valida a linha com base nas regras definidas
  if (validateUsersLine(copia, gestorMusic)) {
    user =
        separateUsers(line); // Se a linha for válida, separa os dados do user

    username = getUserUsername(user); // Obtém o nome do user

    // Insere o user na hashtable usando o username como chave
    g_hash_table_insert(usersTable, username, user);
  } else {
    // Se a linha for inválida, escreve no arquivo de erros
    fprintf(errorsFile, "%s", line);
  }
  free(copia); // Liberta a memória da cópia da linha
}

// Função para processar o arquivo de users e inserir os dados na hashtable
int GestorUsers(gestorUsers *gestorUser, gestorMusics *gestorMusic,
                char *usersPath) {
  // Abre o arquivo de users e carrega os dados
  FILE *fp = fopen(usersPath, "r");
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

gboolean lookUpUsersHashTable(gestorUsers *gestorUser, char *line,
                              gpointer *value, gpointer *orig_key) {
  // Procura o user na hashtable usando a chave fornecida (line)
  gboolean found = g_hash_table_lookup_extended(gestorUser->usersTable, line,
                                                value, orig_key);
  return found;
}

void processAllUsers(Gestores *gestor, NodoMusica **lista) {
  int IDADE_INICIAL = 120;
  guint idade_max = IDADE_INICIAL; // Inicializa a idade máxima

  // Itera sobre a tabela de users para processar as músicas que eles gostam
  GHashTableIter iter;
  gpointer hash_key, hash_value;
  g_hash_table_iter_init(&iter, getUsersTable(pegarGestorUser(gestor)));

  while (g_hash_table_iter_next(&iter, &hash_key, &hash_value)) {
    char *birthDate = getUserBirthDate(hash_value);
    char *age = calculate_age_str(birthDate); // Calcula a idade do user

    int userAge = atoi(age);
    char *liked_musics_id = getUserLikedMusicsId(hash_value);

    free(birthDate);
    free(age);

    removeFstLast(liked_musics_id); // Remove o primeiro e último caracteres

    // Percorre a lista de liked_musics_id
    char *music_id = strtok(liked_musics_id, ", ");
    while (music_id != NULL) {
      if (music_id[0] == '\'')
        music_id++;
      if (music_id[strlen(music_id) - 1] == '\'')
        music_id[strlen(music_id) - 1] = '\0';

      // Procura pela música na tabela
      gpointer music_value;
      gpointer orig_music_key;
      gboolean found = lookUpMusicsHashTable(pegarGestorMusic(gestor), music_id,
                                             &music_value, &orig_music_key);

      if (found) {
        char *genre = getMusicGenre(orig_music_key);
        *lista = adicionar_like(*lista, genre, userAge,
                                &idade_max); // Adiciona à lista
        free(genre);
      }
      music_id = strtok(NULL, ", ");
    }
    free(liked_musics_id);
  }
}
