#ifndef _ARTISTS_H_
#define _ARTISTS_H_

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>


enum tipoArtista;

typedef struct artists Artists;

Artists *separateArtists(char *line);
bool validateArtist(Artists *artist);

void setArtistId(Artists *a, char *id);
void setArtistName(Artists *a, char *name);
void setArtistDescription(Artists *a, char *description);
void setArtistRecipePerStream(Artists *a, int recipe_per_stream);
void setArtistIdConstituent(Artists *a, char *id_constituent);
void setArtistCountry(Artists *a, char *country);
void setArtistTipo(Artists *a, enum tipoArtista tipo);
void setArtistDiscografia(Artists *a, int discografia);

char *getArtistId(gpointer artist);
char *getArtistName(gpointer artist);
char *getArtistDescription(gpointer artist);
int getArtistRecipePerStream(gpointer artist);
char *getArtistIdConstituent(gpointer artist);
char *getArtistCountry(gpointer artist);
enum tipoArtista getArtistType(gpointer artist);
int getArtistDiscografia(gpointer artist);

void increment_artist_discografia(gpointer value, int duracao,
                                  GList **listaResposta, int numeroArtistas,
                                  char *country);
void procuraArt(Artists *artist, GList **listaResposta, int numeroArtistas);

void colocaZero(GHashTable *artistsTable);

void destroyArtist(Artists *a);

void print(GList **listaResposta, int numeroArtistas, FILE *newFile);

char *pegarArtistId(Artists *artist);

char *pegarArtistName(Artists *artist);

char *pegarArtistDescription(Artists *artist);

int pegarArtistRecipePerStream(Artists *artist);

char *pegarArtistIdConstituent(Artists *artist);

char *pegarArtistCountry(Artists *artist);

char *pegarArtistType(Artists *artist);

int pegarArtistDiscografia(Artists *artist);

#endif