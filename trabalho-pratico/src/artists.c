#include "artists.h"
#include "minHeap.h"
#include "utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Definição dos tipos de artista: Individual ou Grupo
enum tipoArtista { Individual, Grupo };

// Estrutura que armazena informações sobre um artista
struct artists {
  char *id;              // Identificador único do artista
  char *name;            // Nome do artista
  char *id_constituent;  // Lista de IDs dos constituintes (para grupos)
  char *country;         // Nacionalidade do artista
  enum tipoArtista tipo; // Tipo de artista (individual ou grupo)
  int discografia;       // Número de músicas ou discos associados ao artista
  int num_albuns_individual;
  float recipePerStream;
  float receitaTotal;
  int tamanhoGrupo;
  GArray *durationPerWeek;
  int vezesNoTop10;
};

// Funções para definir campos específicos da estrutura "Artists"
void setArtistId(Artists *a, char *id) { a->id = id; }

void setArtistName(Artists *a, char *name) { a->name = name; }

void setArtistIdConstituent(Artists *a, char *id_constituent) {
  a->id_constituent = id_constituent;
}

void setArtistCountry(Artists *a, char *country) { a->country = country; }

void setArtistTipo(Artists *a, enum tipoArtista tipo) { a->tipo = tipo; }

void setArtistDiscografia(gpointer a, int discografia) {
  ((struct artists *)a)->discografia = discografia;
}

void alterarArtistNumAlbunsIndividual(gpointer a, int num_albuns_individual) {
  ((struct artists *)a)->num_albuns_individual = num_albuns_individual;
}

void setArtistNumAlbunsIndividual(Artists *a, int num_albuns_individual) {
  a->num_albuns_individual = num_albuns_individual;
}

void setArtistRecipePerStream(Artists *a, float recipePerStream) {
  a->recipePerStream = recipePerStream;
}
/*
void setArtistReceitaTotalZero(Artists *a) {
  a->receitaTotal = 0.00;
}*/

void setArtistReceitaTotal(gpointer artist, float receitaTotal) {
  ((struct artists *)artist)->receitaTotal = receitaTotal;
}

void setArtistTamanhoGrupo(Artists *a, int tamanho) {
  a->tamanhoGrupo = tamanho;
}

int incrementArtistDurationPerWeek(gpointer a, int duration, int semana) {
  struct artists *artist = (struct artists *)a;
  GArray *durationPerWeek = artist->durationPerWeek;

  // Verifica o tamanho atual da duração por semana
  int tamanho = durationPerWeek->len;

  // Ajusta o tamanho do array se necessário
  if (semana >= tamanho) {
    g_array_set_size(durationPerWeek, (guint)(semana + 1)); // Inclui "semana"

    // Inicializa as novas posições com 0
    for (int i = tamanho; i <= semana; i++) {
      g_array_index(durationPerWeek, int, i) = 0;
    }
  }

  // Incrementa a duração para a semana específica
  g_array_index(durationPerWeek, int, semana) += duration;

  // Retorna o novo valor da duração para a semana
  return g_array_index(durationPerWeek, int, semana);
}

int incrementArtistVezesNoTop10(gpointer a) {
  ((struct artists *)a)->vezesNoTop10++;
  return ((struct artists *)a)->vezesNoTop10;
}

// Função que separa os dados de um artista a partir de uma linha do CSV
Artists *separateArtists(char *line) {
  // Aloca memória para um novo artista
  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Erro: Falha ao alocar memória!");
    return NULL;
  }

  // Atribui valores aos campos do artista a partir da linha CSV
  setArtistId(artist, strdup(strsep(&line, ";")));
  setArtistName(artist, strdup(strsep(&line, ";")));

  // Ignora alguns campos não utilizados atualmente
  char *description = strdup(strsep(&line, ";"));

  char *recipePerStreamStr = strdup(strsep(&line, ";"));
  remove_quotes(recipePerStreamStr);
  char *endptr; // Ponteiro para verificar caracteres restantes
  float recipePerStream = strtof(recipePerStreamStr, &endptr);

  // Verifica se a conversão foi bem-sucedida
  if (*endptr != '\0') {
    printf("Erro: string contém caracteres inválidos: %s\n", endptr);
    recipePerStream = 0.0;
  }
  setArtistRecipePerStream(artist, recipePerStream);

  setArtistIdConstituent(artist, strdup(strsep(&line, ";")));
  setArtistCountry(artist, strdup(strsep(&line, ";")));

  // Determina se o artista é um grupo ou individual
  char *linhaTipo = strdup(strsep(&line, "\n"));
  remove_quotes(linhaTipo); // Remove aspas da string
  if (strcmp(linhaTipo, "individual") == 0)
    setArtistTipo(artist, Individual);
  else {
    setArtistTipo(artist, Grupo);
  }

  // Inicializa a discografia com zero
  artist->discografia = 0;

  setArtistNumAlbunsIndividual(artist, 0);

  setArtistReceitaTotal(artist, 0);

  char *idConstituintes = strdup(artist->id_constituent);
  remove_quotes(idConstituintes);
  removeFstLast(idConstituintes);
  int tamanho = (strlen(idConstituintes) + 2) / 12;

  setArtistTamanhoGrupo(artist, tamanho);

  GArray *durationPerWeek = g_array_new(FALSE, TRUE, sizeof(int));
  artist->durationPerWeek = durationPerWeek;

  artist->vezesNoTop10 = 0;

  // Liberta memória das variáveis temporárias
  free(description);
  free(recipePerStreamStr);
  free(linhaTipo);
  free(idConstituintes);

  return artist;
}

// Função que valida se um artista é válido
bool validateArtist(Artists *artist) {
  return ((artist->tipo == Individual && strlen(artist->id_constituent) == 0) ||
          (artist->tipo == Grupo && strlen(artist->id_constituent) != 0));
}

// Remove um artista da lista se ele já existir
void removeArtistId(GList **listaResposta, Artists *artist) {
  GList *node = *listaResposta;
  Artists *currentArtist;

  // Percorre a lista à procura do artista
  while (node != NULL) {
    currentArtist = (Artists *)node->data;
    if (strcmp(currentArtist->id, artist->id) == 0) {
      *listaResposta = g_list_remove(*listaResposta, currentArtist);
      return;
    }
    node = node->next;
  }
}

// Insere um artista em um array ordenado pela discografia
void insertArtistArray(GList **listaResposta, Artists *artist,
                       int numeroArtistas) {
  removeArtistId(listaResposta, artist);
  GList *node = *listaResposta;
  Artists *currentArtist;

  // Insere o artista na posição correta baseado na discografia
  while (node != NULL) {
    currentArtist = (Artists *)node->data;
    if (currentArtist->discografia < artist->discografia) {
      *listaResposta = g_list_insert_before(*listaResposta, node, artist);
      if (g_list_length(*listaResposta) > (guint)numeroArtistas) {
        *listaResposta =
            g_list_remove(*listaResposta, g_list_last(*listaResposta)->data);
      }
      return;
    }
    node = node->next;
  }

  *listaResposta = g_list_append(*listaResposta, artist);
  if (g_list_length(*listaResposta) > (guint)numeroArtistas) {
    *listaResposta =
        g_list_remove(*listaResposta, g_list_last(*listaResposta)->data);
  }
}

// Procura por um artista na lista e atualiza as suas informações
void procuraArt(Artists *artist, GList **listaResposta) {
  GList *current = *listaResposta;
  Artists *currentArtist;

  while (current != NULL) {
    currentArtist = (Artists *)current->data;
    if (strcmp(currentArtist->id, artist->id) == 0) {
      current->data = artist;
      return;
    }
    current = current->next;
  }
}

void putArtistsDiscografyZero(Artists *artist) { artist->discografia = 0; }

void putArtistsVezesTop10Zero(Artists *artist) { artist->vezesNoTop10 = 0; }

// Incrementa a discografia de um artista se ele corresponder ao país
// especificado
void increment_artist_discografia(gpointer value, int duracao,
                                  GList **listaResposta, int numeroArtistas,
                                  char *country) {
  Artists *artist = (Artists *)value;
  if (!(country != NULL && comparaStrings(artist->country, country))) {
    artist->discografia += duracao;
    procuraArt(artist, listaResposta);
    insertArtistArray(listaResposta, artist, numeroArtistas);
  }
}

// Funções para obter os valores dos campos de um artista
char *pegarArtistId(Artists *artist) { return strdup(artist->id); }

char *pegarArtistName(Artists *artist) { return strdup(artist->name); }

char *pegarArtistIdConstituent(Artists *artist) {
  return strdup(artist->id_constituent);
}

char *pegarArtistCountry(Artists *artist) { return strdup(artist->country); }

char *pegarArtistType(Artists *artist) {
  return strdup(artist->tipo == Grupo ? "group"
                                      : "individual"); // a funçao esta certa
}

int pegarArtistDiscografia(Artists *artist) { return artist->discografia; }

// Funções para obter os valores dos campos de um artista passando um gpointer
char *getArtistId(gpointer artist) {
  return strdup(((struct artists *)artist)->id);
}

char *getArtistName(gpointer artist) {
  struct artists *a = (struct artists *)artist;
  return strdup(a->name);
}

char *getArtistIdConstituent(gpointer artist) {
  return strdup(((struct artists *)artist)->id_constituent);
}

char *getArtistCountry(gpointer artist) {
  return strdup(((struct artists *)artist)->country);
}

enum tipoArtista getArtistType(gpointer artist) {
  return ((struct artists *)artist)->tipo;
}

char *getArtistTypeStr(gpointer artist) {
  Artists *a = (Artists *)artist;
  if (a->tipo == Grupo) {
    return "group";
  } else
    return "individual";
}

int getArtistDiscografia(gpointer artist) {
  return ((struct artists *)artist)->discografia;
}

int getArtistNumAlbunsIndividual(gpointer artist) {
  return ((struct artists *)artist)->num_albuns_individual;
}

float getArtistRecipePerStream(gpointer artist) {
  return ((struct artists *)artist)->recipePerStream;
}

float getArtistReceitaTotal(gpointer artist) {
  return ((struct artists *)artist)->receitaTotal;
}

int getArtistTamanhoGrupo(gpointer artist) {
  return ((struct artists *)artist)->tamanhoGrupo;
}

// Função para libertar a memória alocada para um artista
void destroyArtist(Artists *a) {
  if (a) {
    free(a->id);
    free(a->name);
    free(a->id_constituent);
    free(a->country);
    /*     for (guint i = 0; i < a->durationPerWeek->len; i++) {
          MinHeap *m = g_array_index(a->durationPerWeek, MinHeap *, i);
          freeMinHeap(m);
        } */
    g_array_free(a->durationPerWeek, TRUE);
    free(a);
  }
}

float ReceitaParticipacao(int numeroDeParticipacoesEmMusicaColetivas,
                          float reproducoes[], float ratePerStream[],
                          float constituintes[]) {
  float receitaParticipaçao = 0;
  for (int i = 0; i < numeroDeParticipacoesEmMusicaColetivas; i++) {
    receitaParticipaçao +=
        ((reproducoes[i] * ratePerStream[i]) / constituintes[i]);
  }
  return receitaParticipaçao;
}

float ReceitaArtista(float reproducoes, float ratePerStreamArtista) {
  return reproducoes * ratePerStreamArtista;
}

float ReceitaArtistaIndividual(float receitaArtista,
                               float receitaParticipacao) {
  return receitaArtista + receitaParticipacao;
}

Artists *cloneArtists(Artists *artist) {
  Artists *clone = g_malloc(sizeof(Artists));
  clone->id = g_strdup(artist->id);
  clone->name = g_strdup(artist->name);
  clone->id_constituent = g_strdup(artist->id_constituent);
  clone->country = g_strdup(artist->country);
  clone->receitaTotal = artist->receitaTotal;
  clone->tamanhoGrupo = artist->tamanhoGrupo;
  clone->durationPerWeek = NULL;
  return clone;
}