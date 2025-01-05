/**
 * @file artists.h
 * @author Francisco, Pedro, Simão (Grupo 5)
 * @date 5 Jan 2025
 * @brief Header file do artists
 */

#ifndef _ARTISTS_H_
#define _ARTISTS_H_

#include <glib.h>
#include <stdbool.h>
#include <stdio.h>

enum tipoArtista;

typedef struct artists Artists;

Artists *separateArtists(char *line);
bool validateArtist(Artists *artist);

int incrementArtistDurationPerWeek(gpointer a, int duration, int semana);

int incrementArtistVezesNoTop10(gpointer a);

void alterarArtistNumAlbunsIndividual(gpointer a, int num_albuns_individual);
void setArtistId(Artists *a, char *id);
void setArtistName(Artists *a, char *name);
void setArtistRecipePerStream(Artists *a, float recipe_per_stream);
void setArtistIdConstituent(Artists *a, char *id_constituent);
void setArtistCountry(Artists *a, char *country);
void setArtistTipo(Artists *a, enum tipoArtista tipo);
void setArtistDiscografia(gpointer a, int discografia);
void setArtistNumAlbunsIndividual(Artists *a, int num_albuns_individual);
void setArtistReceitaTotal(gpointer artist, float receitaTotal);

char *getArtistId(gpointer artist);
char *getArtistName(gpointer artist);
char *getArtistIdConstituent(gpointer artist);
char *getArtistCountry(gpointer artist);
enum tipoArtista getArtistType(gpointer artist);
char *getArtistTypeStr(gpointer artist);
int getArtistDiscografia(gpointer artist);
int getArtistNumAlbunsIndividual(gpointer artist);
float getArtistRecipePerStream(gpointer artist);
float getArtistReceitaTotal(gpointer artist);
int getArtistTamanhoGrupo(gpointer artist);

void destroyArtist(Artists *a);

void putArtistsVezesTop10Zero(Artists *artist);

#endif