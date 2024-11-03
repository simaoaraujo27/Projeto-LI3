#include "artists.h"
#include "users.h"
#include <ctype.h>
#include <glib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum tipoArtista { Individual, Grupo };

struct artists {
  char *id;              // identificador único do artista
  char *name;            // nome do artista
  char *description;     // descrição do artista
  int recipe_per_stream; // dinheiro auferido de cada vez que uma das músicas
                         // do artista é reproduzida
  char *id_constituent;  // lista de identificadores únicos dos seus
                         // constituintes, no caso de se tratar de um artista
                         // coletivo. Este campo pode ser uma lista vazia.
  char *country;         // nacionalidade do artista.
  enum tipoArtista tipo; // tipo de artista, i.e., individual ou grupo musical,
  int discografia;       // discografia do artista
};

Artists *separateArtists(char *line) {
  // Separa a linha e guarda os respetivos dados na struct artistas

  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }

  artist->id = strdup(strsep(&line, ";"));
  artist->name = strdup(strsep(&line, ";"));
  artist->description = strdup(strsep(&line, ";"));
  artist->recipe_per_stream = atoi(strsep(&line, ";"));
  artist->id_constituent = strdup(strsep(&line, ";"));
  artist->country = strdup(strsep(&line, ";"));
  if (!strcmp(strsep(&line, "\n"), "individual"))
    artist->tipo = Individual;
  else
    artist->tipo = Grupo;
  artist->discografia = 0;

  return artist;
}

bool validateArtist(Artists *artist) {
  return ((artist->tipo == Individual && strlen(artist->id_constituent) == 0) ||
          (artist->tipo == Grupo && strlen(artist->id_constituent) != 0));
}

void parseArtists(FILE *fp, GHashTable *artistsTable) {
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != -1) {
    Artists *artist = separateArtists(line);
    remove_quotes(artist->id);
    // Insere na HashTable usando o artist->name como key
    g_hash_table_insert(artistsTable, g_strdup(artist->id), artist);
  }

  free(line);
}

void puxaDireita(Artists *arrayResposta[], int numeroArtistas, int i) {
  for (int j = numeroArtistas; j < i; j--) {
    arrayResposta[j] = arrayResposta[j - 1];
  }
}

void puxaEsquerda(Artists *arrayResposta[], int numeroArtistas, int i) {
  for (int j = i; j < numeroArtistas; j++) {
    arrayResposta[j] = arrayResposta[j + 1];
  }
  arrayResposta[numeroArtistas - 1] = NULL;
}

// Função auxiliar para encontrar e remover o artista com o mesmo ID, se existir
void removeArtistById(GList **listaResposta, Artists *artist) {
  GList *node = *listaResposta;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    // Verifica se o ID do artista atual é igual ao do novo artista
    if (strcmp(currentArtist->id, artist->id) == 0) {
      *listaResposta = g_list_remove(*listaResposta, currentArtist);
      return;
    }
    node = node->next;
  }
}
void insertArtistArray(GList **listaResposta, Artists *artist,
                       int numeroArtistas) {
  // Remove o artista existente com o mesmo ID, se estiver na lista
  removeArtistById(listaResposta, artist);

  // Insere o artista na posição correta para manter a lista ordenada
  GList *node = *listaResposta;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    // Insere antes do primeiro artista com discografia menor
    if (currentArtist->discografia < artist->discografia) {
      *listaResposta = g_list_insert_before(*listaResposta, node, artist);

      // Limita o tamanho da lista removendo o último artista se exceder o
      // limite
      if (g_list_length(*listaResposta) > numeroArtistas) {
        *listaResposta =
            g_list_remove(*listaResposta, g_list_last(*listaResposta)->data);
      }
      return;
    }
    node = node->next;
  }

  // Se o artista tiver a menor discografia ou a lista estiver vazia, adiciona
  // ao final
  *listaResposta = g_list_append(*listaResposta, artist);

  // Verifica se a lista excede o número máximo de artistas e remove o último,
  // se necessário
  if (g_list_length(*listaResposta) > numeroArtistas) {
    *listaResposta =
        g_list_remove(*listaResposta, g_list_last(*listaResposta)->data);
  }
}

// Função para procurar e substituir um artista por ID na lista de artistas
void procuraArt(Artists *artist, GList **listaResposta, int numeroArtistas) {
  GList *current = *listaResposta;
  while (current != NULL) {
    Artists *currentArtist = (Artists *)current->data;
    // Verifica se o ID do artista atual corresponde ao do artista passado
    if (strcmp(currentArtist->id, artist->id) == 0) {
      // Substitui o artista encontrado pelo novo artista
      current->data = artist;
      return;
    }
    current = current->next;
  }
  // Se o artista não for encontrado, não altera a lista
}

void print(GList **listaResposta, int numeroArtistas, FILE *newFile) {
  GList *node = *listaResposta;
  char *name;
  char *type;
  char discografia[10];
  char *country;
  char *new_str;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    name = currentArtist->name;
    if (currentArtist->tipo == Grupo)
      type = "Grupo";
    else
      type = "Individual";
    snprintf(discografia, sizeof(discografia), "%d",
             currentArtist->discografia);
    country = currentArtist->country;

    int total_len = strlen(name) + strlen(type) + strlen(discografia) +
                    strlen(country) + 4;              // 4 para os ';' e o '\0'
    new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type, discografia,
             country);

    if (node->next == NULL)
      fprintf(newFile, "%s", new_str);
    else
      fprintf(newFile, "%s", new_str);

    printf("ID: %s, Nome: %s, Discografia: %d, País: %s\n", currentArtist->id,
           currentArtist->name, currentArtist->discografia,
           currentArtist->country);
    node = node->next;
  }

  fclose(newFile);

  printf("\n");
}

/* void print(GList **listaResposta, int numeroArtistas, FILE *newFile) {
  GList *node = *listaResposta;
  char *name;
  char *type;
  char *discografia;
  char *country;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    name = currentArtist->name;
    if (currentArtist->tipo == Grupo)
      type = "Grupo";
    else
      type = "Individual";
    sprintf(discografia, "%d", currentArtist->discografia);
    country = currentArtist->country;

    int total_len = strlen(name) + strlen(type) + strlen(discografia) +
                    strlen(country) + 4; // 4 para os ';' e o '\0'
    char *new_str = malloc((total_len + 1) * sizeof(char)); // +1 para o '\0'
    snprintf(new_str, total_len + 1, "%s;%s;%s;%s\n", name, type, discografia,
             country);

    if (node->next == NULL)
      fprintf(newFile, "%s", new_str);
    else
      fprintf(newFile, "%s\n", new_str);

    printf("ID: %s, Nome: %s, Discografia: %d, País: %s\n", currentArtist->id,
           currentArtist->name, currentArtist->discografia,
           currentArtist->country);
    node = node->next;
  }

  free(discografia);
  free(name);
  free(type);
  free(country);
  fclose(newFile);
} */

void increment_artist_discografia(gpointer value, int duracao,
                                  GList **listaResposta, int numeroArtistas,
                                  char *country) {
  Artists *artist = (Artists *)value;
  artist->country[strlen(artist->country)] = '\0';
  // printf("%s\n", artist->country);
  if (country != NULL && artist->country != country)
    return;
  artist->discografia += duracao;
  procuraArt(artist, listaResposta, numeroArtistas);
  insertArtistArray(listaResposta, artist, numeroArtistas);
}

void destroyArtist(gpointer artist) {
  Artists *a = (Artists *)artist;

  g_free(a->name);
  g_free(a->description);
  g_free(a->id_constituent);
  g_free(a->country);
  g_free(a->id);
  g_free(a);
}

char *getArtistId(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->id);
}

char *getArtistName(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->name);
}

char *getArtistDescription(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->description);
}

int getArtistRecipePerStream(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return (a->recipe_per_stream);
}

char *getArtistIdConstituent(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->id_constituent);
}

char *getArtistCountry(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->country);
}

enum tipoArtista getArtistType(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return (a->tipo);
}

int getArtistDiscografia(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return (a->discografia);
}