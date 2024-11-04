#include "artists.h"


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

void setArtistId(Artists *a, char *id){
  a->id = id;
}

void setArtistName(Artists *a, char *name){
  a->name = name;
}

void setArtistDescription(Artists *a, char *description){
  a->description = description;
}

void setArtistRecipePerStream(Artists *a, int recipe_per_stream){
  a->recipe_per_stream = recipe_per_stream;
}

void setArtistIdConstituent(Artists *a, char *id_constituent){
  a->id_constituent = id_constituent;
}

void setArtistCountry(Artists *a, char *country){
  a->country = country;
}

void setArtistTipo(Artists *a, enum tipoArtista tipo){
  a->tipo = tipo;
}

void setArtistDiscografia(Artists *a, int discografia){
  a->discografia = discografia;
}

Artists *separateArtists(char *line) {
  // Separa a linha e guarda os respetivos dados na struct artistas

  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Malloc failed!");
    return NULL;
  }
  setArtistId(artist, strdup(strsep(&line, ";")));
  setArtistName(artist, strdup(strsep(&line, ";")));
  setArtistDescription(artist, strdup(strsep(&line, ";")));
  setArtistRecipePerStream(artist, atoi(strdup(strsep(&line, ";"))));
  setArtistIdConstituent(artist, strdup(strsep(&line, ";")));
  setArtistCountry(artist, strdup(strsep(&line, ";")));
  if (!strcmp(strsep(&line, "\n"), "individual"))
    setArtistTipo(artist, Individual);
  else
    setArtistTipo(artist, Grupo);
  setArtistDiscografia(artist, 0);

  return artist;
}

///////////////

bool validateArtist(Artists *artist) {
  return ((artist->tipo == Individual && strlen(artist->id_constituent) == 0) ||
          (artist->tipo == Grupo && strlen(artist->id_constituent) != 0));
}

void removeArtistId(GList **listaResposta, Artists *artist) {
  GList *node = *listaResposta;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    if (strcmp(currentArtist->id, artist->id) == 0) {
      *listaResposta = g_list_remove(*listaResposta, currentArtist);
      return;
    }
    node = node->next;
  }
}
void insertArtistArray(GList **listaResposta, Artists *artist,
                       int numeroArtistas) {
  removeArtistId(listaResposta, artist);
  GList *node = *listaResposta;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    if (currentArtist->discografia < artist->discografia) {
      *listaResposta = g_list_insert_before(*listaResposta, node, artist);
      if (g_list_length(*listaResposta) > numeroArtistas) {
        *listaResposta =
            g_list_remove(*listaResposta, g_list_last(*listaResposta)->data);
      }
      return;
    }
    node = node->next;
  }
  *listaResposta = g_list_append(*listaResposta, artist);
  if (g_list_length(*listaResposta) > numeroArtistas) {
    *listaResposta =
        g_list_remove(*listaResposta, g_list_last(*listaResposta)->data);
  }
}

void procuraArt(Artists *artist, GList **listaResposta, int numeroArtistas) {
  GList *current = *listaResposta;
  while (current != NULL) {
    Artists *currentArtist = (Artists *)current->data;
    if (strcmp(currentArtist->id, artist->id) == 0) {
      current->data = artist;
      return;
    }
    current = current->next;
  }
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
    node = node->next;
  }
  fclose(newFile);
}

void colocaZero(GHashTable *artistsTable) {
  GList *listaArtistas = g_hash_table_get_values(artistsTable);
  GList *node = listaArtistas;
  while (node != NULL) {
    Artists *currentArtist = (Artists *)node->data;
    currentArtist->discografia = 0;
    node = node->next;
  }
  g_list_free(listaArtistas);
}

int comparaStrings(char *str1, char *str2) {
  if (strlen(str1) == strlen(str2) - 1) { // -1 por causa do \n fantasma
    int len = strlen(str1);
    for (int i = 0; i < len; i++) {
      if (str1[i] != str2[i]) {
        return 1;
      }
    }
  } else
    return 1;
  return 0;
}

void increment_artist_discografia(gpointer value, int duracao,
                                  GList **listaResposta, int numeroArtistas,
                                  char *country) {
  Artists *artist = (Artists *)value;
  if (!(country != NULL && comparaStrings(artist->country, country))) {
    artist->discografia += duracao;
    procuraArt(artist, listaResposta, numeroArtistas);
    insertArtistArray(listaResposta, artist, numeroArtistas);
  }
}
///////////////

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

void destroyArtist(gpointer artist) {
  Artists *a = (Artists *)artist;

  g_free(a->name);
  g_free(a->description);
  g_free(a->id_constituent);
  g_free(a->country);
  g_free(a->id);
  g_free(a);
}