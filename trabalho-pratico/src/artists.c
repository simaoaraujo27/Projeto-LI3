#include "artists.h"
#include "top10Query4.h"
#include "utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

enum tipoArtista { Individual, Grupo };

struct artists {
  char *id;
  char *name;
  char *id_constituent;
  char *country;
  enum tipoArtista tipo;
  int discografia;
  int num_albuns_individual;
  float recipePerStream;
  float receitaTotal;
  int tamanhoGrupo;
  GArray *durationPerWeek;
  int vezesNoTop10;
};

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

void setArtistReceitaTotal(gpointer artist, float receitaTotal) {
  ((struct artists *)artist)->receitaTotal = receitaTotal;
}

void setArtistTamanhoGrupo(Artists *a, int tamanho) {
  a->tamanhoGrupo = tamanho;
}

int incrementArtistDurationPerWeek(gpointer a, int duration, int semana) {
  struct artists *artist = (struct artists *)a;
  GArray *durationPerWeek = artist->durationPerWeek;

  int tamanho = durationPerWeek->len;

  if (semana >= tamanho) {
    g_array_set_size(durationPerWeek, (guint)(semana + 1));

    for (int i = tamanho; i <= semana; i++) {
      g_array_index(durationPerWeek, int, i) = 0;
    }
  }

  g_array_index(durationPerWeek, int, semana) += duration;

  return g_array_index(durationPerWeek, int, semana);
}

int incrementArtistVezesNoTop10(gpointer a) {
  ((struct artists *)a)->vezesNoTop10++;
  return ((struct artists *)a)->vezesNoTop10;
}

Artists *separateArtists(char *line) {

  Artists *artist = malloc(sizeof(struct artists));
  if (!artist) {
    fprintf(stderr, "Erro: Falha ao alocar memória!");
    return NULL;
  }

  setArtistId(artist, strdup(strsep(&line, ";")));
  setArtistName(artist, strdup(strsep(&line, ";")));

  char *description = strdup(strsep(&line, ";"));

  char *recipePerStreamStr = strdup(strsep(&line, ";"));
  remove_quotes(recipePerStreamStr);
  char *endptr;
  float recipePerStream = strtof(recipePerStreamStr, &endptr);

  if (*endptr != '\0') {
    printf("Erro: string contém caracteres inválidos: %s\n", endptr);
    recipePerStream = 0.0;
  }
  setArtistRecipePerStream(artist, recipePerStream);

  setArtistIdConstituent(artist, strdup(strsep(&line, ";")));
  setArtistCountry(artist, strdup(strsep(&line, ";")));

  char *linhaTipo = strdup(strsep(&line, "\n"));
  remove_quotes(linhaTipo);
  if (strcmp(linhaTipo, "individual") == 0)
    setArtistTipo(artist, Individual);
  else {
    setArtistTipo(artist, Grupo);
  }

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

  free(description);
  free(recipePerStreamStr);
  free(linhaTipo);
  free(idConstituintes);

  return artist;
}

bool validateArtist(Artists *artist) {
  return ((artist->tipo == Individual && strlen(artist->id_constituent) == 0) ||
          (artist->tipo == Grupo && strlen(artist->id_constituent) != 0));
}

void putArtistsVezesTop10Zero(Artists *artist) { artist->vezesNoTop10 = 0; }

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
  return strdup(a->tipo == Grupo ? "group" : "individual");
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

void destroyArtist(Artists *a) {
  if (a) {
    free(a->id);
    free(a->name);
    free(a->id_constituent);
    free(a->country);
    g_array_free(a->durationPerWeek, TRUE);
    free(a);
  }
}
