#include "gestor_artists.h"
#include "gestor_musics.h"
#include "gestor_queries.h"
#include "gestor_users.h"
#include "validation.h"
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_SIZE 1024

// Definindo a estrutura que representa a lista ligada
typedef struct nodoMusica {
  char *genero;
  GArray *likes;
  struct nodoMusica *prox;
} NodoMusica;

// Função para criar um novo nodo com um genero e inicializar o GArray de likes
NodoMusica *criar_nodo(char *genero, guint idade_max) {
  NodoMusica *nodo = (NodoMusica *)malloc(
      sizeof(struct nodoMusica)); // Alocação de memória para o nodo

  if (nodo == NULL) {
    printf("Malloc failed!\n");
    return NULL;
  }

  nodo->genero = strdup(genero);
  nodo->likes = g_array_new(FALSE, TRUE,
                            sizeof(guint)); // Inicializa o GArray para inteiros

  // Inicializa cada faixa etária com 0 likes
  for (guint i = 0; i <= idade_max; i++) {
    guint zero = 0;
    g_array_append_val(nodo->likes, zero);
  }

  nodo->prox = NULL;
  return nodo;
}

// Função para expandir todos os arrays até o novo limite de idade
void expandir_arrays(NodoMusica *lista, guint nova_idade_max) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    guint tamanho_atual = atual->likes->len;
    // Adiciona zeros até que o array atinja o novo tamanho
    for (guint i = tamanho_atual; i <= nova_idade_max; i++) {
      guint zero = 0;
      g_array_append_val(atual->likes, zero);
    }
    atual = atual->prox;
  }
}

// Função para adicionar um like a uma faixa etária específica
NodoMusica *adicionar_like(NodoMusica *lista, char *genero, guint idade,
                           guint *idade_max) {
  // Se a idade for maior que a idade máxima, expande todos os arrays
  if (idade > *idade_max) {
    expandir_arrays(lista, idade);
    *idade_max = idade; // Atualiza o novo limite de idade máxima
  }

  NodoMusica *atual = lista;
  NodoMusica *anterior = NULL;

  // Procura o nodo com o género especificado
  while (atual != NULL) {
    if (strcmp(atual->genero, genero) == 0) {
      // Adiciona um like na posição correspondente à idade
      guint *likes = &g_array_index(atual->likes, guint, idade);
      (*likes)++;
      return lista; // Retorna a lista original, pois o nodo já foi encontrado e
                    // atualizado
    }
    anterior = atual;
    atual = atual->prox;
  }

  // Se não encontrou o género, cria um novo nodo
  NodoMusica *novo_nodo = criar_nodo(genero, *idade_max);
  guint *likes = &g_array_index(novo_nodo->likes, guint, idade);
  (*likes)++;

  // Insere o novo nodo no final da lista
  if (anterior != NULL) {
    anterior->prox = novo_nodo;
  } else {
    lista = novo_nodo; // Caso a lista esteja vazia, o novo nodo é o primeiro
  }
  return lista;
}

// Função para liberar a memória da lista
void liberar_lista(NodoMusica *lista) {
  NodoMusica *atual = lista;
  while (atual != NULL) {
    NodoMusica *prox = atual->prox;
    g_array_free(atual->likes, TRUE); // Libera o GArray
    free(atual->genero);              // Libera a string do gênero
    free(atual);                      // Libera o nodo
    atual = prox;
  }
}

// Estrutura temporária para armazenar o género e a contagem de likes
typedef struct {
  char *genero;
  guint count;
} GeneroLikes;

// Função de comparação para ordenar em ordem decrescente de likes
gint comparar_likes(gconstpointer a, gconstpointer b) {
  const GeneroLikes *g1 = a;
  const GeneroLikes *g2 = b;
  return (g1->count < g2->count) - (g1->count > g2->count);
}

void query3(int minAge, int maxAge, NodoMusica *lista, int i) {
  NodoMusica *l = lista;
  GList *generos_lista = NULL;

  FILE *newFile;
  char *path = "./resultados/commandx_output.txt";
  char *new = malloc(sizeof(char) * (strlen(path) + 10));
  snprintf(new, strlen(path) + 10, "./resultados/command%d_output.txt", i);
  newFile = fopen(new, "w");

  while (l != NULL) {
    guint count = 0;
    for (guint j = minAge; j <= maxAge; j++) {
      count += g_array_index(l->likes, guint, j);
    }

    // Adiciona o género e o total de likes para essa faixa etária
    GeneroLikes *genero_likes = malloc(sizeof(GeneroLikes));
    genero_likes->genero = strdup(l->genero);
    genero_likes->count = count;

    generos_lista = g_list_prepend(generos_lista, genero_likes);
    l = l->prox;
  }

  generos_lista = g_list_sort(generos_lista, comparar_likes);

  int tudoAZero = 1;
  // Escrevendo a lista ordenada no arquivo
  for (GList *iter = generos_lista; iter != NULL; iter = iter->next) {
    GeneroLikes *genero_likes = iter->data;
    if (genero_likes->count != 0) {

      remove_quotes(genero_likes->genero);
      fprintf(newFile, "%s;%d\n", genero_likes->genero, genero_likes->count);
      tudoAZero = 0;
    }

    // Liberando memória da string de género
    free(genero_likes->genero);
    free(genero_likes);
  }

  if (tudoAZero) {
    fprintf(newFile, "\n");
  }

  g_list_free(generos_lista);

  fclose(newFile);
}

/*
IDEIA: TIPO UM HISTOGRAMA

Lista ligada em que cada nodo tem o seguinte:
Nome do género;
Array com o número de likes para cada idade (pode ser um array dinâmico)


Depois é só percorrer a hashtable dos users, e pegar no liked_musics_id
Fazer um lookup na hashtable das músicas usando o id
Pegar no genre dessa música
Ir ao nodo da lista ligada correspondente a esse genre e incrementar a
posição da idade

*/

int main(int argc, char **argv) {
  FILE *fp = NULL;

  if (argc < 3) {
    fp = stdin;
    fprintf(stderr, "Error: Missing filename\n");
    return EXIT_FAILURE;
  }

  char *path = argv[1];

  char *artistsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *musicsPath = malloc(MAX_PATH_SIZE * sizeof(char));
  char *usersPath = malloc(MAX_PATH_SIZE * sizeof(char));

  snprintf(artistsPath, MAX_PATH_SIZE, "%s/%s", path, "artists.csv");
  snprintf(musicsPath, MAX_PATH_SIZE, "%s/%s", path, "musics.csv");
  snprintf(usersPath, MAX_PATH_SIZE, "%s/%s", path, "users.csv");

  GHashTable *artistsTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyArtist);
  fp = fopen(artistsPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseArtists(fp, artistsTable);
  }
  fclose(fp);
  free(artistsPath);

  GHashTable *musicsTable = g_hash_table_new_full(
      g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyMusic);
  fp = fopen(musicsPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseMusics(fp, musicsTable, artistsTable);
  }
  fclose(fp);
  free(musicsPath);

  GHashTable *usersTable =
      g_hash_table_new_full(g_str_hash, g_str_equal, g_free, (GDestroyNotify)destroyUser);

  fp = fopen(usersPath, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  } else {
    parseUsers(fp, usersTable, musicsTable);
  }
  fclose(fp);
  free(usersPath);

  char *txt = argv[2];
  fp = fopen(txt, "r");
  if (!fp) {
    perror("Error");
    return EXIT_FAILURE;
  }
  char *line = NULL;
  size_t len = 0;
  int i = 1;
  int numeroArtist = 0;
  char *country;
  int firstOcorr, minAge, maxAge;
  int IDADE_INICIAL = 120;

  NodoMusica *lista = NULL;
  guint idade_max =
      IDADE_INICIAL; // Inicialize a idade máxima como IDADE_INICIAL

  GHashTableIter iter;
  gpointer hash_key, hash_value;
  g_hash_table_iter_init(&iter, usersTable);

  while (g_hash_table_iter_next(&iter, &hash_key, &hash_value)) {
    char *birthDate = getUserBirthDate(hash_value);
    char *age = calculate_age_str(birthDate);

    int userAge = atoi(age);
    char *liked_musics_id = getUserLikedMusicsId(hash_value);

    removeFstLast(liked_musics_id);
    char *music_id = strtok(liked_musics_id, ", ");
    while (music_id != NULL) {
      // Remove as aspas simples
      if (music_id[0] == '\'') {
        music_id++;
      }
      if (music_id[strlen(music_id) - 1] == '\'') {
        music_id[strlen(music_id) - 1] = '\0';
      }

      gpointer music_value;
      gpointer orig_music_key;

      gboolean found = g_hash_table_lookup_extended(
          musicsTable, music_id, &music_value, &orig_music_key);

      if (found) {
        char *genre = getMusicGenre(orig_music_key);
        // Atualize a lista e a idade máxima se necessário
        lista = adicionar_like(lista, genre, userAge, &idade_max);
      }

      music_id = strtok(NULL, ", ");
    }
  }

  while (getline(&line, &len, fp) != -1) {
    if (line[0] == '1') {
      query1(usersTable, line, i);
      i++;
    } else if (line[0] == '2') {
      if (!temAspas(line)) {
        query2(atoi(line + 2), NULL, artistsTable, musicsTable, line, i);
        i++;
      } else {
        firstOcorr = primeiraOcorr(line, '"');
        query2(atoi(line + 2), line + firstOcorr, artistsTable, musicsTable,
               line, i);
        i++;
      }
    } else if (line[0] == '3') {
      minAge = atoi(line + 2);
      firstOcorr = primeiraOcorr(line + 2, ' ');
      maxAge = atoi(line + 2 + firstOcorr);
      query3(minAge, maxAge, lista, i);
      i++;
    }
  }
  fclose(fp);
  free(line);
  free(country);
  g_hash_table_destroy(musicsTable);
  g_hash_table_destroy(artistsTable);
  g_hash_table_destroy(usersTable);
  liberar_lista(lista);

  return 0;
}