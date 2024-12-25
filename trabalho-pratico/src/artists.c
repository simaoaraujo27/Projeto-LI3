#include "artists.h"
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
};

// Funções para definir campos específicos da estrutura "Artists"
void setArtistId(Artists *a, char *id) { a->id = id; }

void setArtistName(Artists *a, char *name) { a->name = name; }

void setArtistIdConstituent(Artists *a, char *id_constituent) {
  a->id_constituent = id_constituent;
}

void setArtistCountry(Artists *a, char *country) { a->country = country; }

void setArtistTipo(Artists *a, enum tipoArtista tipo) { a->tipo = tipo; }

void setArtistDiscografia(Artists *a, int discografia) {
  a->discografia = discografia;
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
  setArtistDiscografia(artist, 0);

  setArtistNumAlbunsIndividual(artist, 0);

  setArtistReceitaTotal(artist, 0);

  char *idConstituintes = strdup(artist->id_constituent);
  remove_quotes(idConstituintes);
  removeFstLast(idConstituintes);
  int tamanho = (strlen(idConstituintes) + 2) / 12;

  setArtistTamanhoGrupo(artist, tamanho);

  // Liberta memória das variáveis temporárias
  free(description);
  free(recipePerStreamStr);
  free(linhaTipo);

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
